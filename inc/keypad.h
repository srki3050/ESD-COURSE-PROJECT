/*
 * @Name: Abijith
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: keypad.h
 * @Description: Keypad driver code
 * @Brief: This file has functions that can
 *          1) Initialize the Keypad
 *          2) Return character value of key pressed
 * @Pinouts
 *      5 - P6.0
 *      6 - P6.1
 *      7 - P6.2
 *      8 - P6.3
 *      1 - P6.4
 *      2 - P6.5
 *      3 - P6.6
 *      4 - P6.7
 * @References:
 *          1) http://www.microdigitaled.com/ARM/MSP432_ARM/Code/Ver1/red/Chapter3/P3_5.txt
 *          2) https://components101.com/sites/default/files/component_datasheet/4x4%20Keypad%20Module%20Datasheet.pdf?msclkid=26003149c26411ecaa9060c0276b3b25
 *
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_



/*
 * Header files
 */
#include "msp432p401r.h"



/*
 * All pins are initially set to input
 * The column pins have pull up resistor enabled
 *
 * @params:
 *      None
 * @returns:
 *      None
 */
void keypad_init(void);



/*
 * This is a non-blocking function to read the keypad.
 * If a key is pressed, it returns a unique code for the key. Otherwise,
 * a zero is returned.
 * The upper nibble of Port 6 is used as input and connected to the columns.
 * Pull-up resistors are enabled so when the keys are not pressed, these pins
 * are pulled high.
 * The lower nibble of Port 6 is used as output that drives the keypad rows.
 * First all rows are driven low and the input pins are read. If no key is pressed,
 * they will read as all one because of the pull up resistors. If they are not
 * all one, some key is pressed.
 * If some key is pressed, the program proceeds to drive one row low at a time and
 * leave the rest of the rows inactive (float) then read the input pins.
 * Knowing which row is active and which column is active, the program
 * can decide which key is pressed.
 *
 * Only one row is driven so that if multiple keys are pressed and row pins are shorted,
 * the microcontroller will not be damaged. When the row is being deactivated,
 * it is driven high first otherwise the stray capacitance may keep the inactive
 * row low for some time.)
 */
char keypad_getkey(void) ;



#endif /* INC_KEYPAD_H_ */
