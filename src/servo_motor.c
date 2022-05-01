/*
 * @Name: Sricharan Kidambi
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: servo motor.c
 * @Description: servo motor driver code
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
#include <inc/servo_motor.h>



// configure Timer_A_PWMConfig for servo motor
Timer_A_PWMConfig pwmConfig =
{
        //uint_fast16_t clockSource;
        TIMER_A_CLOCKSOURCE_SMCLK,
        //uint_fast16_t clockSourceDivider;
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        //uint_fast16_t timerPeriod;
        1300,
        //uint_fast16_t compareRegister;
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        //uint_fast16_t compareOutputMode;
        TIMER_A_OUTPUTMODE_RESET_SET,
        //uint_fast16_t dutyCycle;
        10
};



/*
 * Check header file for documentation
 */
void get_motor_functioning(){
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);
}



/*
 * Check header file for documentation
 */
void start_motor(int *b){
    pwmConfig.dutyCycle = *b;
    *b = *b + 10;
    if(*b == 170)
        *b = 40;
    delay_ms(4); // change delay
    // Configuring Timer_A to have a period of approximately 20ms
    get_motor_functioning();
}



/*
 * Check header file for documentation
 */
void stop_motor(int *b){
    pwmConfig.dutyCycle = *b;
    *b = *b - 10;
    if(*b == 40)
        *b = 170;
    delay_ms(4); // change delay
    // Configuring Timer_A to have a period of approximately 20ms
    get_motor_functioning();
}

