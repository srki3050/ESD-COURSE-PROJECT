/**
 * @file    :   buzzer.c
 * @brief   :   An abstraction for buzzer functions
 *
 *              This source file provides buzzer functions
 *              which are used to initialize and play the buzzer
 *
 * @author  :
 * @date    :
 * @version :   1.0
 *
 * @tools   :   Code Composer Studio
 *
 * @link    :   MSP432 Reference Manual
*/

/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <inc/delay.h>

/* Standard Includes */
#include <stdint.h>

#include <inc/buzzer.h>

bool enable_buzzer = false;
Timer_A_PWMConfig buzzer_config =
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

void buzzer_generate(int *buzzer){
    buzzer_config.dutyCycle = *buzzer;
        *buzzer = *buzzer + 10;
        if(*buzzer == 170)
            *buzzer = 40;
    delay_ms(4); // change delay
    MAP_Timer_A_generatePWM(TIMER_A0_BASE, &buzzer_config);
}

void play_buzzer(int buzz_count)
{
    if(enable_buzzer ==  true)
    {
        volatile int i,j;

        /* Configure P2.4 as output */
        MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN4);

        /* Turn on the buzzer */
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);

        for(i = 0; i < buzz_count ; i++)
        {
            /* ON Time */
            for(j = 0; j < ON_TIME; j++);

            /* Turn off the buzzer */
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);

            /* OFF Time */
            for(j = 0; j < OFF_TIME; j++);

            /* Turn on the buzzer */
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
        }

        /* Turn off the buzzer */
        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
    }
}

void buzzer_state_change(bool state)
{
    enable_buzzer = state;
}

