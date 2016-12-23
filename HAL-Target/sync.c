/*
 * sync.c
 *
 *  Created on: 08.04.2014
 *      Author: netzwerg
 */


#include "../Application/sync.h"
#include <stdint.h>
#include "reed_switch.h"

/**
 *  @addtogroup sync
 *  @{
 */


volatile uint8_t sync_interrupt_flag=0;
volatile uint8_t sync_interrupt_enabled=1;


void sync_init(){
	reed_switch_init();
	sync_interrupt_flag=0;
	sync_interrupt_enabled=1;
}

void enable_sync_interrupt(){
	sync_interrupt_enabled=1;
	enable_reed_switch_interrupt();
}
void disable_sync_interrupt(){
	sync_interrupt_enabled=0;
	disable_reed_switch_interrupt();
}

uint8_t sync_is_active(){
	return reed_is_active();
}


/**@}*/
