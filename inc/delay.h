/*
 * delay.h
 *
 *  Created on: Apr 15, 2022
 *      Author: unnia
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "delay.h"

// Delay Functions
// Delay in terms of ms
#define delay_ms(x)     __delay_cycles((long) x* 1000)
#endif /* DELAY_H_ */
