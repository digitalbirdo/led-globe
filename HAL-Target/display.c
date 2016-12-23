/*
 * globe.c
 *
 *  Created on: 31.03.2014
 *      Author: netzwerg
 *
 *
 *
 *
 *
 */
#include <util/delay.h>
#include "../Application/display.h"
#include "ws2803.h"
#include "timer.h"


uint8_t num_rows=0;
uint8_t current_row=0;

void display_init(){
	ws2803_init();
	timer_init();
}



void display_set_num_rows(uint8_t num){
	num_rows=num;
}

uint8_t display_get_num_rows(){
	return num_rows;
}

void display_set_row(struct cRGB *led_array){
	uint8_t ii=0;
	while(!ready_to_send);
	for(uint8_t i=NUM_RGB_LEDS_PER_ROW; i>0;i-=6){


		ii=i-3;
		ws2803_send(led_array[ii].r);
		ws2803_send(led_array[ii].g);
		ws2803_send(led_array[ii].b);

		ii=i-4;
		ws2803_send(led_array[ii].r);
		ws2803_send(led_array[ii].g);
		ws2803_send(led_array[ii].b);

		ii=i-5;
		ws2803_send(led_array[ii].r);
		ws2803_send(led_array[ii].g);
		ws2803_send(led_array[ii].b);

		ii=i;
		ws2803_send(led_array[ii].r);
		ws2803_send(led_array[ii].g);
		ws2803_send(led_array[ii].b);

		ii=i-1;
		ws2803_send(led_array[ii].r);
		ws2803_send(led_array[ii].g);
		ws2803_send(led_array[ii].b);

		ii=i-2;
		ws2803_send(led_array[ii].r);
		ws2803_send(led_array[ii].g);
		ws2803_send(led_array[ii].b);


	}
	//_delay_us(600);
	timer_start_600us();
}

void display_set_row_rgb(uint8_t r,uint8_t g,uint8_t b){

	while(!ready_to_send);
	for(uint8_t i=0; i<NUM_RGB_LEDS_PER_ROW;i++){

		ws2803_send(r);
		ws2803_send(g);
		ws2803_send(b);
	}
	//_delay_us(600);
	timer_start_600us();
}

void display_set_row_color(Color color){

	while(!ready_to_send);
	struct cRGB temp_led={0,0,0};

	switch(color){
		case RED:
			temp_led.r=0xFF;
			temp_led.g=0;
			temp_led.b=0;
			break;
		case GREEN:
			temp_led.r=0;
			temp_led.g=0xFF;
			temp_led.b=0;
			break;
		case BLUE:
			temp_led.r=0;
			temp_led.g=0;
			temp_led.b=0xFF;
			break;
		case WHITE:
			temp_led.r=0xFF;
			temp_led.g=0xFF;
			temp_led.b=0xFF;
			break;
		case BLACK:
			temp_led.r=0;
			temp_led.g=0;
			temp_led.b=0;
			break;
	}

	for(uint8_t i=0; i<NUM_RGB_LEDS_PER_ROW;i++){

		ws2803_send(temp_led.r);
		ws2803_send(temp_led.g);
		ws2803_send(temp_led.b);
	}
	//_delay_us(600);
	timer_start_600us();


}

uint8_t get_random_value(uint8_t min, uint8_t max)
{
	srand(0);
	return (rand() % max + min);
}
