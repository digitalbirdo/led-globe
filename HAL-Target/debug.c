/*
 * debug.c
 *
 *  Created on: 09.04.2014
 *      Author: netzwerg
 */

#include <stdlib.h>
#include "../Application/debug.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"

/**
 *  @addtogroup debug
 *  @{
 */


char buffer[7];

void debug_string(const char * s){
	uart_puts(s);
}

void debug_int(uint8_t x){
	itoa(x, buffer, 10);
	uart_puts(buffer);
}

/**@}*/
