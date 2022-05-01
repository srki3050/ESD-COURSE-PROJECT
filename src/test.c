/*
 * test.c
 *
 *  Created on: Apr 22, 2022
 *      Author: unnia
 */


#include "test.h"
#include "buzzer.h"
#include <stdbool.h>
#include <inc/delay.h>
#include <lcd.h>
#include <servo_motor.h>
#include "inc/keypad.h"
#define MOTOR_START 40
#define MOTOR_END 170
#define BUZZER_DELAY 8
#define DELAY_BETWEEN_EVENTS 10
void test(){
    //Detect whether Key press signal is detected by the microprocessor
    lcd_set_text("Enter Any Key: ");
    while(keypad_getkey() == 0);
    //Test whether LCD is working according to keypad changes
    lcd_clear();
    lcd_set_text("Keypad Tested");
    delay_ms(DELAY_BETWEEN_EVENTS);
    //Test whether motor and buzzer functionality is working using PWM software module
    int b = MOTOR_START;
    play_buzzer(BUZZER_DELAY);
    start_motor(&b);
    delay_ms(DELAY_BETWEEN_EVENTS);
    b = MOTOR_END;
    stop_motor(&b);
    lcd_clear();
    lcd_set_text("Motor Tested");
    delay_ms(DELAY_BETWEEN_EVENTS);
    //Write appropriate text messages to the LCD to test whether the functionality is coherent with other hardware components
    lcd_clear();
    lcd_set_text("Testing buzzer ");

    play_buzzer(BUZZER_DELAY);
    //clear the display to get ready for the production code messages.
    lcd_clear();
    lcd_set_text("Testing complete");
    delay_ms(DELAY_BETWEEN_EVENTS);
    lcd_clear();
}
