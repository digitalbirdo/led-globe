/*
 * timer.h
 *
 *  Created on: 11.04.2014
 *      Author: netzwerg
 */

#ifndef TIMER_H_
#define TIMER_H_


#include <stdint.h>

/**
 *  @defgroup timer Hardware-Timer
 *  @brief This module can be used to start a timer and set a flag, when 600us have passed.
 *
 *  @author Tobias Finke tofiit00@hs-esslingen.de
 *  @{
 */

/**
 * @todo check if neeeded
 */
typedef void (*timer_overflow_fktn)(void);

/**
 * @brief this flag indicate if 600us are over and we can start to send again
 */
extern volatile uint8_t ready_to_send;

/**
 * @brief init the hardware-timer
 */
void timer_init();

/**
 * @brief restart the timer with a value of 600us
 */
void timer_start_600us();

/**@}*/

#endif /* TIMER_H_ */
