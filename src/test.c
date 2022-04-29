/*
 * test.c
 *
 *  Created on: Apr 22, 2022
 *      Author: unnia
 */


#include "test.h"
#include "pwm.h"
#include "buzzer.h"
#include <stdbool.h>
#include <inc/delay.h>
#include <lcd.h>
#include "inc/keypad.h"
void test(){
    lcd_set_text("Enter Any Key: ");
    //char key = keypad_getkey();
    while(keypad_getkey() == 0);
    lcd_clear();
    lcd_set_text("Keypad Tested");
    delay_ms(10);

    int b = 40;
    buzzer_state_change(true);
    play_buzzer(8);
    generate_motor(&b);
    delay_ms(25);
    b = 170;
    degenerate_motor(&b);
    lcd_clear();
    lcd_set_text("Motor Tested");
    delay_ms(10);

    lcd_clear();
    lcd_set_text("Testing buzzer ");

    buzzer_state_change(true);
    play_buzzer(4);

    lcd_clear();
    lcd_set_text("Testing complete");
    delay_ms(10);
    lcd_clear();
}
