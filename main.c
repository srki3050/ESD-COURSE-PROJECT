/*
 * @Name: Abijith
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: main.c
 * @Description: Entry point of application
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
#include <inc/keypad.h>
#include <inc/test.h>
#include <inc/lcd.h>
#include <inc/mfrc522.h>
#include <inc/sd_card.h>
#include <servo_motor.h>


unsigned char key;
char result[5];
int b;
FRESULT r;
char* startup_buff;

void init(void);
void open_servo(void);
void close_servo(void);



FIL accepted_fil, rejected_fil;

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
    uint8_t cardID[5];
    char buffer[5];
    int i;

    init();
    test();

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
            if((strncmp(result,"569B2",5)==0)||(strncmp(result,"A9B64",5)==0))
                open_servo();
            else
                close_servo();
        }
        else{
            sprintf(buffer, "%02x %02x %02x %02x %02x", cardID[0], cardID[1], cardID[2],cardID[3],cardID[4] );
            if(MFRC522_Compare(buffer, "01 02 03 04 05") == MI_OK)
                open_servo();
            else
                close_servo();
        }
    }
}


void init(void){
    WDTCTL = WDTPW + WDTHOLD;// Stop Watchdog
    keypad_init();

    lcd_init();
    //a typedef keyword for unsigned long


    startup_buff = RTC_init();

    /*Initialize all hardware required for the SD Card*/

    MFRC522_Init();

    sd_card_init(startup_buff);
    buzzer_init();
}


void open_servo(void){
    b = 40;
    start_motor(&b);
    delay_ms(25);
    b = 170;
    stop_motor(&b);
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

void close_servo(void){
    lcd_clear();
    lcd_set_text("Rejected");
    delay_ms(5);
    play_buzzer(20);
    r = f_open(&rejected_fil, "rejected.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    r = f_lseek(&rejected_fil, rejected_fil.fptr);
    f_puts(&result[0],&rejected_fil);
    f_puts(" ", &rejected_fil);
    f_puts(&startup_buff[0], &rejected_fil);
    f_puts("\n", &rejected_fil);
    f_close(&rejected_fil);
}
