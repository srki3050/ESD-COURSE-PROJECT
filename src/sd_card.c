/*
 * @Name: Sricharan Kidambi
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: sd_card.c
 * @Description: SD card driver code
 * @Brief: This file has functions that can
 *          1) Intialise sd card adapter functionality - sd_card_init
 *
 * @References:
 *           http://elm-chan.org/fsw/ff/00index_e.html
 *           GitHub - howlanjo/test: Working SD card software for MSP432
 *           GitHub - amartinezacosta/MSP432-SD_Card: MSP432 interface to a SD Card
 */



/*
 * Header file
 */
#include "inc/sd_card.h"



/*
 * global variables
 */
FATFS fs;
FIL fil;



/*
 * Timer configuration for SD card
 */
Timer_A_UpModeConfig upConfig =
{
        // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_SMCLK,
        // SMCLK/1 = 3MHz
        TIMER_A_CLOCKSOURCE_DIVIDER_64,
        // 1 ms tick period
        30000,
        // Disable Timer interrupt
        TIMER_A_TAIE_INTERRUPT_DISABLE,
        // Enable CCR0 interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,
        // Clear value
        TIMER_A_DO_CLEAR
};



/*
 * Check header file for documentation
 */
void sd_card_init(char* startup_buff){
    // initialize timerA
    TIMERA_Init(TIMER_A1_BASE,UP_MODE,&upConfig,disk_timerproc);
    f_mount(&fs, "",0);
    f_open(&fil, "start.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    // declare file pointer
    f_lseek(&fil, fil.fptr);
    f_puts("Program initiated ", &fil);
    f_puts(&startup_buff[0], &fil);
    f_puts("\n", &fil);
    f_close(&fil);
}

