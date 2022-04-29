/*
 * @Name: Abijith
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: main.c
 * @Description: Entry point of application
 * @Brief: This file has functions that can
 *
 * @References:
 *
 */



/* Standard header files */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>



/* DriverLib header files*/
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>
#include <Hardware/SPI_Driver.h>
#include <Hardware/GPIO_Driver.h>
#include <Hardware/CS_Driver.h>
#include <Hardware/TIMERA_Driver.h>
#include <fatfs/ff.h>
#include <fatfs/diskio.h>
#include <Devices/MSPIO.h>


#include <inc/rtc.h>
#include <inc/buzzer.h>
#include <msp.h>
#include <inc/delay.h>
#include <inc/pwm.h>
#include <inc/keypad.h>
#include <inc/test.h>
#include <inc/lcd.h>
#include <inc/mfrc522.h>

//#define SLAVE_ADDRESS       0x68
/* Variables */
const uint8_t TXData[] = {0x04};
static volatile uint32_t xferIndex;
static volatile bool stopSent;
volatile bool read_done = false;
unsigned char key;
char result[5];

eUSCI_SPI_MasterConfig SPI0MasterConfig =
{
     EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
     3000000,
     500000,
     EUSCI_B_SPI_MSB_FIRST,
     EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
     EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH,
     EUSCI_B_SPI_3PIN
};
/* Timer_A UpMode Configuration Parameters */
Timer_A_UpModeConfig upConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_64,          // SMCLK/1 = 3MHz
        30000,                                  // 1 ms tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
};
Timer_A_PWMConfig pwmConfig =
{
        //uint_fast16_t clockSource;
        TIMER_A_CLOCKSOURCE_SMCLK,
        //uint_fast16_t clockSourceDivider;
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        //uint_fast16_t timerPeriod;
        1300,
        //uint_fast16_t compareRegister;
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        //uint_fast16_t compareOutputMode;
        TIMER_A_OUTPUTMODE_RESET_SET,
        //uint_fast16_t dutyCycle;
        10
};
Timer_A_PWMConfig buzzer_config =
{
        //uint_fast16_t clockSource;
        TIMER_A_CLOCKSOURCE_SMCLK,
        //uint_fast16_t clockSourceDivider;
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        //uint_fast16_t timerPeriod;
        1300,
        //uint_fast16_t compareRegister;
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        //uint_fast16_t compareOutputMode;
        TIMER_A_OUTPUTMODE_RESET_SET,
        //uint_fast16_t dutyCycle;
        10
};
FATFS fs;
FIL fil, accepted_fil, rejected_fil;
void get_motor_functioning(){
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);
}

void buzzer_generate(int *buzzer){
    buzzer_config.dutyCycle = *buzzer;
        *buzzer = *buzzer + 10;
        if(*buzzer == 170)
            *buzzer = 40;
    delay_ms(4); // change delay
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &buzzer_config);
}
void generate_motor(int *b){
    pwmConfig.dutyCycle = *b;
    *b = *b + 10;
    if(*b == 170)
        *b = 40;
    delay_ms(4); // change delay
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);
}
void degenerate_motor(int *b){
    pwmConfig.dutyCycle = *b;
    *b = *b - 10;
    if(*b == 40)
        *b = 170;
    delay_ms(4); // change delay
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);
}
/*********************************************************************************
 * @function:   main
 *
 * @brief   :   Main entry point to the application
 *
 * @param   :   none
 *
 * @return  :   void
 *
**********************************************************************************/
void main(void)
{
    int b;
    WDTCTL = WDTPW + WDTHOLD;// Stop Watchdog
    keypad_init();

    lcd_init();
    //a typedef keyword for unsigned long
    DWORD str=0;
    str = get_fattime();
    RTC_C_Calendar start_time =
    {
         (str & 0x0000001F)*2,
         (str & 0x000007E0)>>5,
         (str & 0x0000F800)>>11,
         3,
         (str & 0x001F0000)>>16,
         (str & 0x01E00000)>>21,
         ((str & 0xFE000000)>>21)/16 + 1980 // epoch has been set as 1980
         //>>25 was not allowed for year field. hence >>21 and divide by 16
    };

    CS_Init();
    RTC_init(start_time);

    /*Initialize all hardware required for the SD Card*/
    SPI_Init(EUSCI_B0_BASE, SPI0MasterConfig);
    GPIO_Init(GPIO_PORT_P5, GPIO_PIN0);
    TIMERA_Init(TIMER_A1_BASE,UP_MODE,&upConfig,disk_timerproc);
    MFRC522_Init();

    Interrupt_enableMaster();

    char startup_buff[100];
    sprintf(startup_buff, " Date-> %02d-%02d-%04d, Time-> %02d:%02d:%02d",   start_time.month, start_time.dayOfmonth, start_time.year,
                                                                    start_time.hours+1, start_time.minutes, start_time.seconds);
    MSPrintf(EUSCI_A0_BASE, startup_buff);

    FRESULT r;

    r = f_mount(&fs, "",0);
    r = f_open(&fil, "write.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    r = f_lseek(&fil, fil.fptr);
    f_puts("Program initiated ", &fil);
    f_puts(&startup_buff[0], &fil);
    f_puts("\n", &fil);
    f_close(&fil);
    new_pwm_init();
    get_motor_functioning();
    b = 40;

    uint8_t cardID[5];
    char buffer[5];

    test();

    int i;
    while(1) {
        lcd_clear();
        lcd_set_text("Enter or scan RFID: ");
        if (MFRC522_Check(cardID) != MI_OK) {
            for(i = 0;i < 5;){
                key = keypad_getkey();
                if(key != 0){
                    result[i] = key;
                    lcd_write_data(key);
                    i++;
                }
            }
            if((strncmp(result,"569B2",5)==0)||(strncmp(result,"A9B64",5)==0)){
                b = 40;
                generate_motor(&b);
                delay_ms(25);
                b = 170;
                degenerate_motor(&b);
                lcd_clear();
                lcd_set_text("Accepted");
                delay_ms(5);
                r = f_open(&accepted_fil, "accepted.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
                r = f_lseek(&accepted_fil, accepted_fil.fptr);
                f_puts(&result[0],&accepted_fil);
                f_puts(" ", &accepted_fil);
                f_puts(&startup_buff[0], &accepted_fil);
                f_puts("\n", &accepted_fil);
                f_close(&accepted_fil);
            }
            else{
                lcd_clear();
                lcd_set_text("Rejected");
                delay_ms(5);
                buzzer_state_change(true);
                play_buzzer(20);
                r = f_open(&rejected_fil, "rejected.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
                r = f_lseek(&rejected_fil, rejected_fil.fptr);
                f_puts(&result[0],&rejected_fil);
                f_puts(" ", &rejected_fil);
                f_puts(&startup_buff[0], &rejected_fil);
                f_puts("\n", &rejected_fil);
                f_close(&rejected_fil);
            }
        }
        else{
            sprintf(buffer, "%02x %02x %02x %02x %02x", cardID[0], cardID[1], cardID[2],cardID[3],cardID[4] );
            if(MFRC522_Compare(buffer, "01 02 03 04 05") == MI_OK){
                b = 40;
                generate_motor(&b);
                delay_ms(25);
                b = 170;
                degenerate_motor(&b);
                lcd_clear();
                lcd_set_text("Accepted");
                delay_ms(5);
                r = f_open(&accepted_fil, "accepted.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
                r = f_lseek(&accepted_fil, accepted_fil.fptr);
                f_puts(&result[0],&accepted_fil);
                f_puts(" ", &accepted_fil);
                f_puts(&startup_buff[0], &accepted_fil);
                f_puts("\n", &accepted_fil);
                f_close(&accepted_fil);
            }
            else{
                lcd_clear();
                lcd_set_text("Rejected");
                delay_ms(5);
                buzzer_state_change(true);
                play_buzzer(20);
                r = f_open(&rejected_fil, "rejected.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
                r = f_lseek(&rejected_fil, rejected_fil.fptr);
                f_puts(&result[0],&rejected_fil);
                f_puts(" ", &rejected_fil);
                f_puts(&startup_buff[0], &rejected_fil);
                f_puts("\n", &rejected_fil);
                f_close(&rejected_fil);
            }
        }
    }
}
