/*
 * @Name: Abijith
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: lcd.h
 * @Description: LCD driver code
 * @Brief: This file has functions that can
 *          1) Initialize the LCD - lcd_init()
 *          2) Pull enable pin high or low - lcd_trigger_en()
 *          3) Write data to LCD - lcd_write_data(unsigned char data)
 *          4) Write a string of data on LCD - lcdSetText(char* text)
 *          5) Clear the LCD screen - lcdClear()
 * @Pinouts
 *          Vss - gnd
 *          Vcc - 5V
 *          Vee - potentiometer
 *          RS - P4.5
 *          RW - gnd
 *          E - P4.4
 *          D0 - NC
 *          D1 - NC
 *          D2 - NC
 *          D3 - NC
 *          D4 - P4.0
 *          D5 - P4.1
 *          D6 - P4.2
 *          D7 - P4.3
 * @References:
 *          1) https://microdigisoft.com/ti-launchpad-interfacing-lcd-16x2-with-msp432-microcontroller/
 *          2) https://github.com/agaelema/LCD16x2_MSP43x/blob/master/lcd16x2_msp43x.c
 *          3) http://www.ece.utep.edu/courses/web3376/Lab_5_-_LCD_files/lcdLib.c
 *          4) http://www.ece.utep.edu/courses/web3376/Lab_5_-_LCD_files/lcdLib.h
 */

#ifndef LCDLIB_H_
#define LCDLIB_H_



/*
 * Header files
 */
#include <msp432.h>
#include <string.h>
#include <stdio.h>
#include "inc/delay.h"


/*
 * Preprocessor defines
 */
// Pins
#define EN		BIT4
#define RS		BIT5
#define DATA	0x0F
// Commands
#define CLEAR	0x01



/*
 * Function prototypes
 */
/*
 * Initializes the LCD
 * The command 0x03 is repeated 3 times with enough delay
 * The command 0x02 is used to switch to 4 bit mode
 * The command 0x28 is used to 4-bit, 2 line, 5x8 setting
 * The command 0x08 is for instruction flow
 * The command 0x01 is for clear screen
 * The command 0x06 is for auto increment
 * The command 0x0F is for displaying cursor and blinking it
 *
 * @params:
 *      None
 * @returns:
 *      None
 */
void lcd_init();


/*
 * To trigger the enable pin
 * First enabe is high
 * Next enable pin is made low
 *
 * @params:
 *      None
 * @returns:
 *      None
 */
void lcd_trigger_en();



/*
 * Writes 8 bit data to LCD
 * RS is high when data needs to be written
 * Enable pin is triggered whenever a nibble of data is sent
 * Enough delay to make sure write operation is successful
 *
 * @params:
 *      8 bit data
 * @returns:
 *      None
 */
void lcd_write_data(unsigned char data);



/*
 * Writes 8 bit command to LCD
 * RS is low when command needs to be written
 * Enable pin is triggered whenever a nibble of command is sent
 * Enough delay to make sure write operation is successful
 *
 * @params:
 *      8 bit command
 * @returns:
 *      None
 */
void lcd_write_cmd(unsigned char cmd);



/*
 * Clear LCD screen
 * Command 0x01 is written to LCD controller
 *
 * @params:
 *      None
 * @returns:
 *      None
 */
void lcd_clear();



/*
 * Writes character by character of string to LCD
 * Uses lcd_write_data to write each character
 *
 * @params:
 *      string pointer
 * @returns:
 *      None
 */
void lcd_set_text(char * text);

#endif /* LCDLIB_H_ */
