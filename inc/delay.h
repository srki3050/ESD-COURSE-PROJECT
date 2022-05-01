/*
 * @Name: Sricharan
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: delay.h
 * @Description: Buzzer driver code
 * @Brief: This file has functions that can
 *          1) produce delay in x milliseconds - delay_ms(x)
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "delay.h"

// Delay Functions
// Delay in terms of ms
#define delay_ms(x)     __delay_cycles((long) x* 1000)
#endif /* DELAY_H_ */
