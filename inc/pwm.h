/*
 * pwm.h
 *
 *  Created on: Apr 15, 2022
 *      Author: unnia
 */

#ifndef PWM_H_
#define PWM_H_

#include "ti/devices/msp432p4xx/driverlib/timer_a.h"

void get_motor_functioning();
void generate_motor(int *b);
void degenerate_motor(int *b);
void new_pwm_init(void);
#endif /* PWM_H_ */
