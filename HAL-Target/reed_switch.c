/*
 * reed_switch.c
 *
 *  Created on: 02.04.2014
 *      Author: netzwerg
 */

#include "reed_switch.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Application/debug.h"
#include "../Application/sync.h"


/**
 *  @addtogroup reed_switch
 *  @{
 */

void reed_switch_init(){

	// Pin auf Eingang setzen
	REED_SWITCH_DDR &= ~(1 << REED_SWITCH_PIN);

	// Pullup einschlaten
	REED_SWITCH_PORT|= (1<<REED_SWITCH_PIN);

	DDRD &=~(1<<PIND3)|(1<<PIND2);
	PORTD|=(1<<PIND3)|(1<<PIND2);

	EICRA=(1<<ISC11)|(1<<ISC01); // falling edge

}

// return 1, wenn reed-Switch aktiv
uint8_t reed_is_active(){
	return !(REED_SWITCH_PORT & ( 1 << REED_SWITCH_PIN));
}

void enable_reed_switch_interrupt(){
	EIFR|=(1<<INTF1);
	EIMSK=(1<<INT1)|(1<<INT0); // interrupt enable
}
void disable_reed_switch_interrupt(){
	EIMSK &=~(1<<INT1)|(1<<INT0);
}

/**
 * @brief Interrupt-Service-Routine (ISR) for receiving INT0-Interrrupt on Pin PD2
 * @param INT0_vect
 */
ISR (INT0_vect){
	//debug_string("INT0");
	sync_interrupt_flag=1;
	disable_reed_switch_interrupt();
	EIFR|=(1<<INTF0);
}

/**
 * @brief Interrupt-Service-Routine (ISR) for receiving the INT1-Interrrupt on Pin PD3
 * @param INT1_vect
 */
ISR (INT1_vect){
	EIMSK &=~(1<<INT1);
	sync_interrupt_flag=1;
	EIFR|=(1<<INTF1);
}

/**@}*/


