/*
 * @Name: Sricharan Kidambi
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: servo motor.h
 * @Description: Keypad driver code
 * @Brief: This file has functions that can
 *          1) Initialize the Keypad
 *          2) Return character value of key pressed
 * @References:
 *          1) http://www.microdigitaled.com/ARM/MSP432_ARM/Code/Ver1/red/Chapter3/P3_5.txt
 *          2) https://components101.com/sites/default/files/component_datasheet/4x4%20Keypad%20Module%20Datasheet.pdf?msclkid=26003149c26411ecaa9060c0276b3b25
 */




#ifndef PWM_H_
#define PWM_H_




/*
 * Header files
 */
#include "ti/devices/msp432p4xx/driverlib/timer_a.h"
#include <ti\devices\msp432p4xx\driverlib\cs.h>
#include <ti\devices\msp432p4xx\driverlib\rom_map.h>
#include <ti\devices\msp432p4xx\driverlib\pcm.h>
#include <ti\devices\msp432p4xx\driverlib\gpio.h>
#include <inc/delay.h>



/*
 * Start timer for motor functioning
 *
 * @params:
 *      None
 * @returns:
 *      None
 */
void get_motor_functioning();



/*
 * Set duty cycle of 40 and run till 170 for 180 degree rotation (clockwise)
 *
 * @params:
 *  - int *b
 *          duty cycle value
 * @returns:
 *      None
 */
void start_motor(int *b);



/*
 * Set duty cycle of 170 and run till 40 for 180 degree rotation (anti-clockwise)
 *
 * @params:
 *  - int *b
 *          duty cycle value
 * @returns:
 *      None
 */
void stop_motor(int *b);

#endif /* PWM_H_ */
