/*
 * pwm.c
 *
 *  Created on: Apr 15, 2022
 *      Author: unnia
 */

#include <inc/pwm.h>
#include <inc/port.h>
#include <inc/delay.h>
#include <ti\devices\msp432p4xx\driverlib\cs.h>
#include <ti\devices\msp432p4xx\driverlib\rom_map.h>
#include <ti\devices\msp432p4xx\driverlib\pcm.h>
#include <ti\devices\msp432p4xx\driverlib\gpio.h>

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
void get_motor_functioning(){
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);
}


void generate_motor(int *b){
    pwmConfig.dutyCycle = *b;
    *b = *b + 10;
    if(*b == 170)
        *b = 40;
    delay_ms(4); // change delay
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);
}
void degenerate_motor(int *b){
    pwmConfig.dutyCycle = *b;
    *b = *b - 10;
    if(*b == 40)
        *b = 170;
    delay_ms(4); // change delay
    MAP_Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfig);
}
void new_pwm_init(void){
    /* Setting MCLK to REFO at 128Khz for LF mode setting SMCLK to 64Khz */
    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    MAP_CS_initClockSignal(CS_MCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_2);
    MAP_PCM_setPowerState(PCM_AM_LF_VCORE0);
    // Configuring GPIO2.4 as peripheral output for PWM
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
    // Configuring Timer_A to have a period of approximately 20ms
    get_motor_functioning();
}
