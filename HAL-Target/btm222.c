/*
 * btm222.c
 *
 *  Created on: 02.04.2014
 *      Author: netzwerg
 */


#include "btm222.h"

#include <util/delay.h>

/**
 *  @addtogroup mode_conway
 *  @{
 */

void btm222_init(){

	// Pin auf Ausgang setzen
	BTM222_DDR |= (1 << BTM222_PIN);

	BTM222_PORT&= ~(1<<BTM222_PIN);
	_delay_ms(50);

	// Pullup einschlaten
	BTM222_PORT|= (1<<BTM222_PIN);
	BTM222_DDR &= ~(1 << BTM222_PIN);
	_delay_ms(3000);

}

/**@}*/
