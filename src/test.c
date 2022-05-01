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
void test(){
    lcd_set_text("Enter Any Key: ");
    while(keypad_getkey() == 0);
    lcd_clear();
    lcd_set_text("Keypad Tested");
    delay_ms(10);

    int b = 40;
    play_buzzer(8);
    start_motor(&b);
    delay_ms(25);
    b = 170;
    stop_motor(&b);
    lcd_clear();
    lcd_set_text("Motor Tested");
    delay_ms(10);

    lcd_clear();
    lcd_set_text("Testing buzzer ");

    play_buzzer(4);

    lcd_clear();
    lcd_set_text("Testing complete");
    delay_ms(10);
    lcd_clear();
}
