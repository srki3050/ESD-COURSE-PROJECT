/*
 * @Name: Sricharan Kidambi
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: rtc.h
 * @Description: Real time clock driver code
 * @Brief: This file has functions that can
 *          1) Intializes real time clock returns start of program date and time - RTC_init()
 *
 * @References:
 *          1) Asked for help from Sanish Kharade(TA)
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_



/*
 * Header files
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>
#include <fatfs/integer.h>
#include <fatfs/ff.h>
#include <stdbool.h>



/*
 * With the help of RTC_C_Calendar startTime, time is intialized.
 * The mode is chosen. Every minute, time gets updated.
 * Interrupt is set to hit every minute.
 *
 * MAP_RTC_C_startClock starts the clock.
 *
 * @params:
 *  - uint8_t addr
 *      register address
 *  - uint8_t
 *      one byte value
 * @returns:
 *      None
 */
char* RTC_init();

#endif /* INC_RTC_H_ */
