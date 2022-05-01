/*
 * @Name: Sricharan Kidambi
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: rtc.c
 * @Description: Real time clock driver code
 * @Brief: This file has functions that can
 *          1) Intializes real time clock returns start of program date and time - RTC_init()
 *
 * @References:
 *          1) Asked for help from Sanish Kharade(TA)
 */



/*
 * Header files
 */
#include <inc/rtc.h>



/*
 * global variables
 */
static volatile RTC_C_Calendar current_time;
static volatile bool one_second_tracker;


/*
 * Check header file for documentation
 */
char* RTC_init()
{
    DWORD str=0;
    str = get_fattime();
    RTC_C_Calendar start_time =
    {
         (str & 0x0000001F)*2,
         (str & 0x000007E0)>>5,
         (str & 0x0000F800)>>11,
         3,
         (str & 0x001F0000)>>16,
         (str & 0x01E00000)>>21,
         ((str & 0xFE000000)>>21)/16 + 1980 // epoch has been set as 1980
         //>>25 was not allowed for year field. hence >>21 and divide by 16
    };

    /* Initialize the RTC, some functions are done for debugging purposes */

    /* Initializing RTC with current time */
    MAP_RTC_C_initCalendar(&start_time, RTC_C_FORMAT_BINARY);

    /* Setup Calendar Alarm for 10:04pm (for the flux capacitor) */
    MAP_RTC_C_setCalendarAlarm(0x04, 0x22, RTC_C_ALARMCONDITION_OFF,
            RTC_C_ALARMCONDITION_OFF);

    /* Specify an interrupt to assert every minute */
    MAP_RTC_C_setCalendarEvent(RTC_C_CALENDAREVENT_MINUTECHANGE);

    /* Enable interrupt for RTC Ready Status, which asserts when the RTC
     * Calendar registers are ready to read.
     * Also, enable interrupts for the Calendar alarm and Calendar event. */
    MAP_RTC_C_clearInterruptFlag(
            RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT
                    | RTC_C_CLOCK_ALARM_INTERRUPT);
    MAP_RTC_C_enableInterrupt(
            RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT
                    | RTC_C_CLOCK_ALARM_INTERRUPT);

    /* Start RTC Clock */
    MAP_RTC_C_startClock();

    /* Enable interrupts and go to sleep. */
    MAP_Interrupt_enableInterrupt(INT_RTC_C);

    MAP_Interrupt_enableMaster();


    char startup_buff[100];
    sprintf(startup_buff, " Date-> %02d-%02d-%04d, Time-> %02d:%02d:%02d",   start_time.month, start_time.dayOfmonth, start_time.year,
                                                                        start_time.hours+1, start_time.minutes, start_time.seconds);

    return startup_buff;
}


/*
 * ISR for RTC
 *
 * @params:
 *      None
 * @returns:
 *      None
 */
void RTC_C_IRQHandler(void)
{
    uint32_t status;
    one_second_tracker = true;

    /*Update current time */
    current_time = MAP_RTC_C_getCalendarTime();

    status = MAP_RTC_C_getEnabledInterruptStatus();
    MAP_RTC_C_clearInterruptFlag(status);

    if (status & RTC_C_CLOCK_READ_READY_INTERRUPT)
    {
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }

    if (status & RTC_C_TIME_EVENT_INTERRUPT)
    {
        /* Interrupts every minute - Set breakpoint here */
        __no_operation();
        current_time = MAP_RTC_C_getCalendarTime();
    }

    if (status & RTC_C_CLOCK_ALARM_INTERRUPT)
    {
        /* Interrupts at 10:04pm */
        __no_operation();
    }

}





