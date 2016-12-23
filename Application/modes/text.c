/*
 * text.c
 *
 *  Created on: 21.04.2014
 *      Author: netzwerg
 */

#include "text.h"
#include "modes.h"
#include "../font.h"
#include "../display.h"

void mode_text(uint8_t index){
	uint8_t i=0;
	RGB red={100,0,0};
	RGB black={0,0,0};
	for(i=0;i<NUM_LEDS_PER_ROW;i++){
		leds[i]=black;
	}
	write_str_to_led("Hello World",3,20,red,index);
	display_set_row(leds);
}
