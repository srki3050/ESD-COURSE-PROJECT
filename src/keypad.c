/*
 * @Name: Abijith
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: keypad.c
 * @Description: Keypad driver code
 * @Brief: This file has functions that can
 *          1) Initialize the Keypad
 *          2) Return character value of key pressed
 * @References:
 *          1) http://www.microdigitaled.com/ARM/MSP432_ARM/Code/Ver1/red/Chapter3/P3_5.txt
 *          2) https://components101.com/sites/default/files/component_datasheet/4x4%20Keypad%20Module%20Datasheet.pdf?msclkid=26003149c26411ecaa9060c0276b3b25
 */



/*
 * Header files
 */
#include "inc/keypad.h"



/*
 * Check header file for documentation
 */
void keypad_init(void) {
    P6->DIR = 0;
    // enable pull resistor for column pins
    P6->REN = 0xF0;
    // make column pins pull-ups
    P6->OUT = 0xF0;
}



/*
 * Check header file for documentation
 */
char keypad_getkey(void) {
    int row, col, retval;
    // one row is active
    const char row_select[] = {0x01, 0x02, 0x04, 0x08};

    // check to see any key pressed
    // make all row pins output
    P6->DIR |= 0x0F;
    // drive all row pins low
    P6->OUT &= ~0x0F;
    // wait for signals to settle
    delay_ms(4);
    // read all column pins
    col = P6->IN & 0xF0;
    // drive all rows high before disable them
    P6->OUT |= 0x0F;
    // disable all row pins drive
    P6->DIR &= ~0x0F;
    // if all columns are high
    if (col == 0xF0){
        // no key pressed
        return 0;
    }

    /* If a key is pressed, it gets here to find out which key.
     * It activates one row at a time and read the input to see
     * which column is active. */
    for (row = 0; row < 4; row++) {
        // disable all rows
        P6->DIR &= 0x0F;
        // enable one row at a time
        P6->DIR |= row_select[row];
        // drive the active row low
        P6->OUT &= ~row_select[row];
        // wait for signal to settle
        delay_ms(4);
        // read all columns
        col = P6->IN & 0xF0;
        // drive the active row high
        P6->OUT |= row_select[row];
        // if one of the input is low, some key is pressed.
        if (col != 0xF0) break;
    }
    // drive all rows high before disable them
    P6->OUT |= 0x0F;
    // disable all rows
    P6->DIR &= 0x0F;
    if (row == 4){
        // if we get here, no key is pressed
        return 0;
    }

    // gets here when one of the rows has key pressed, check which column it is
    if (col == 0xE0){
        // key in column 0
        retval = row*4+1;
    }
    if (col == 0xD0){
        // key in column 1
        retval = row*4+2;
    }
    if (col == 0xB0){
        // key in column 2
        retval = row*4+3;
    }
    if (col == 0x70){
        // key in column 3
        retval = row*4+4;
    }

    // return corresponding character
    // if 16(0x10) - '1', if 15(0x0F) - '2',....., if 1(0x01) - 'D'
    if(retval == 0x10)
        return '1';
    else if(retval == 0x0F)
        return '2';
    else if(retval == 0x0E)
        return '3';
    else if(retval == 0x0D)
        return 'A';
    else if(retval == 0x0C)
        return '4';
    else if(retval == 0x0B)
        return '5';
    else if(retval == 0x0A)
        return '6';
    else if(retval == 0x09)
        return 'B';
    else if(retval == 0x08)
        return '7';
    else if(retval == 0x07)
        return '8';
    else if(retval == 0x06)
        return '9';
    else if(retval == 0x05)
        return 'C';
   else if(retval == 0x04)
        return '*';
    else if(retval == 0x03)
        return '0';
    else if(retval == 0x02)
        return '#';
    else if(retval == 0x01)
        return 'D';

    return 0;
}
