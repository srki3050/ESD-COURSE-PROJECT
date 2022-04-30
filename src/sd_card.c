/*
 * sd_card.c
 *
 *  Created on: Apr 29, 2022
 *      Author: unnia
 */


#include "inc/sd_card.h"

FATFS fs;
FIL fil;

Timer_A_UpModeConfig upConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_64,          // SMCLK/1 = 3MHz
        30000,                                  // 1 ms tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
};


void sd_card_init(char* startup_buff){
    TIMERA_Init(TIMER_A1_BASE,UP_MODE,&upConfig,disk_timerproc);
    FRESULT r;
    r = f_mount(&fs, "",0);
    r = f_open(&fil, "write.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    r = f_lseek(&fil, fil.fptr);
    f_puts("Program initiated ", &fil);
    f_puts(&startup_buff[0], &fil);
    f_puts("\n", &fil);
    f_close(&fil);
}

