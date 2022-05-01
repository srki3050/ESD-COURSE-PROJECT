/*
 * @Name: Sricharan
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: buzzer.c
 * @Description: Buzzer driver code
 * @Brief: This file has functions that can
 *          1) to operate the buzzer based on number of counts - play_buzzer(int buzz_count)
 *
 * @Pinouts
 *      P5.6 - (+)
 *      gnd  - (-)
 * @References:
 *          1) https://e2e.ti.com/support/tools/code-composer-studio-group/ccs/f/code-composer-studio-forum/857542/ccs-msp432p401r-producing-a-single-tone-using-buzzer-in-edumkii-booster-pack
 */

#ifndef BUZZER_H_
#define BUZZER_H_
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <inc/delay.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* Define MACROS for buzzer timings */
#define ON_TIME         (1500)
#define OFF_TIME        (1000)
#define BUZZ_CNT        (2)





/*
 * Set MCLK to REFO at 128Khz for LF mode setting SMCLK to 64Khz
 * set clock for PWM operation
 * Configuring GPIO5.6 as peripheral output for buzzer
 *
 * @params:
 *  - int *b
 *          duty cycle value
 * @returns:
 *      None
 */
void buzzer_init(void);




/*
 * Set pin 5.6 as output. Using PWM, create high pulse for a set period of time followed by low pulse.
 *
 * @params:
 *  - int buzzer_count
 * @returns:
 *      None
 */
void play_buzzer(int buzz_count);


#endif /* BUZZER_H_ */
