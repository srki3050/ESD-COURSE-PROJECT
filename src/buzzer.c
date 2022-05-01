/*
 * @Name: Sricharan
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: buzzer.c
 * @Description: Buzzer driver code
 * @Brief: This file has functions that can
 *          1) to operate the buzzer based on number of counts - play_buzzer(int buzz_count)
 * @References:
 *          1) https://e2e.ti.com/support/tools/code-composer-studio-group/ccs/f/code-composer-studio-forum/857542/ccs-msp432p401r-producing-a-single-tone-using-buzzer-in-edumkii-booster-pack
 */



/*
 * Header files
 */
#include <inc/buzzer.h>


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



/*
 * Check header file for documentation
 */
void buzzer_init(void){
    /* Setting MCLK to REFO at 128Khz for LF mode setting SMCLK to 64Khz */
    MAP_CS_setReferenceOscillatorFrequency(CS_REFO_128KHZ);
    MAP_CS_initClockSignal(CS_MCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    MAP_CS_initClockSignal(CS_SMCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_2);
    MAP_PCM_setPowerState(PCM_AM_LF_VCORE0);
    // Configuring GPIO5.6 as peripheral output for PWM
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);

}



/*
 * Check header file for documentation
 */
void play_buzzer(int buzz_count)
{
        volatile int i,j;

        /* Configure P5.6 as output */
        MAP_GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN6);

        /* Turn on the buzzer */
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);

        for(i = 0; i < buzz_count ; i++)
        {
            /* ON Time */
            for(j = 0; j < ON_TIME; j++);

            /* Turn off the buzzer */
            MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6);

            /* OFF Time */
            for(j = 0; j < OFF_TIME; j++);

            /* Turn on the buzzer */
            MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
        }

        /* Turn off the buzzer */
        MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6);
}

