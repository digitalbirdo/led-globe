/*
 * reed_switch.h
 *
 *  Created on: 02.04.2014
 *      Author: netzwerg
 */

#ifndef REED_SWITCH_H_
#define REED_SWITCH_H_

#include <avr/io.h>
#include <inttypes.h>

/**
 *  @defgroup reed_switch Reed-Switch
 *  @brief Generate an Interrupt when the Reed-Switch produces a Signal
 *
 *  @author Tobias Finke tofiit00@hs-esslingen.de
 *  @{
 */

#if defined(__AVR_ATTmega128__)
	#define REED_SWITCH_PIN   PINB4
	#define REED_SWITCH_PORT  PINB
	#define REED_SWITCH_DDR   DDRB
#elif defined(__AVR_ATmega88P__)|defined(__AVR_ATmega328P__)
	#define REED_SWITCH_PIN   PINB1
	#define REED_SWITCH_PORT  PINB
	#define REED_SWITCH_DDR   DDRB
#endif

/**
 * @brief init the pin which is connected to the reed-switch an initialize the corresponding interrupt
 */
void reed_switch_init();

/**
 * @brief check the state of the reed-switch
 * @return active=1 / inactive=0
 */
uint8_t reed_is_active();

/**
 * @brief enable the interrupt
 */
void enable_reed_switch_interrupt();

/**
 * @brief disable the interrupt
 */
void disable_reed_switch_interrupt();


/**@}*/
#endif /* REED_SWITCH_H_ */
