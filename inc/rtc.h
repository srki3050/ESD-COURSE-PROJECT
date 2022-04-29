/**
 * @file    :   rtc.h
 * @brief   :   An abstraction for RTC functions
 *
 *              This header file provides abstraction of RTC functions which are
 *              used to initialize and keep track of time
 *
 * @author  :
 * @date    :
 * @version :   1.0
 *
 * @tools   :   Code Composer Studio
 *
 * @link    :   MSP432 Reference Manual
*/

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdio.h>

void RTC_init(RTC_C_Calendar start_time);

#endif /* INC_RTC_H_ */
