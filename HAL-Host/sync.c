/*
 * sync.c
 *
 *  Created on: 08.04.2014
 *      Author: netzwerg
 */


#include "../Application/sync.h"
#include <stdint.h>
#include <stdio.h>
#include "../Application/display.h"


volatile uint8_t sync_interrupt_flag=0;
volatile uint8_t sync_interrupt_enabled=1;


void sync_init(){
	//printf("Hello \u001b[1;31mred\u001b[0m world!\n");
	printf("bla\n");
	printf("%c[1;1H %c[2J\n",27,27);
	printf("\033[44;1;34m    \033[0mTESTAUSGABE \033[43;4;34m KUNTER \033[45;1;32m BUNT \033[44;1;33m ANGESTRICHEN \033[0m");
	printf("%c[0;00mHello, world!\n", 27); /* White color     */
	printf("%c[1;33mHello, world!\n", 27); /* Yellowish color */
	printf("%c[1;34mHello, world!\n", 27); /* Blueish color   */
	printf("bla\n");
	sync_interrupt_flag=0;
	sync_interrupt_enabled=1;
}

void enable_sync_interrupt(){
	//printf("sync interrupt enabled\n");
	sync_interrupt_enabled=1;
}
void disable_sync_interrupt(){
	//printf("sync interrupt disabled\n");
	sync_interrupt_enabled=0;
}

uint8_t sync_is_active(){

	if(current_row==56){
		return 1;
	}
	return 0;
}
