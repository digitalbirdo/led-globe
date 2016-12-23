/*
 * timer.c
 *
 *  Created on: 11.04.2014
 *      Author: netzwerg
 */


#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../Application/debug.h"

/**
 *  @addtogroup timer
 *  @{
 */


volatile uint8_t ready_to_send;


void timer_init(){
	ready_to_send=1;
}

timer_overflow_fktn ov_fktn;


void timer_start_600us(){
	//ov_fktn=f;

	TCNT1=0xFFFF-75; //600us


	//TCNT1=0xFFFF-31250; //1 s
	TIMSK1=(1<<TOIE1);

	//TCCR1B=(1<<CS12)|(1<<CS10); //256
	TCCR1B=(1<<CS11)|(1<<CS10); //preescaler 64 stazt
	//sei();
	ready_to_send=0;
}

/**
 * @brief Interrupt-Service-Routine (ISR) for receiving the Timer1 Overflow-Interrrupt.
 * @param TIMER1_OVF_vect
 */
ISR (TIMER1_OVF_vect){
	TCCR1B=0; // stop timer
	ready_to_send=1;
	/*
	//ov_fktn();
	//debug_string("Overflow\n");
	 * //TCNT1=0xFFFF-31250;
	//TCNT1=0xFFFF-75; //600us
	 */

	if(PORTB&(1<<6)){
		PORTB &= ~(1 << 6);
	}else{
		PORTB|=(1<<6);
	}


}

/**@}*/
