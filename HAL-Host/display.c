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

#include "../Application/display.h"
#include "../Application/debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


RGB display[100][48];

uint8_t current_row=0;
uint8_t num_rows=0;



void display_init(){
	printf("display initalized\n");
	srand(time(NULL));
	num_rows=0;
}

void display_print(){
	uint8_t x, y;
	printf("Reihe:    ");
	for(x=0;x<num_rows;x++){
		printf("%2i ",x);
	}
	printf("\n\n");
	for(y=0;y<NUM_RGB_LEDS_PER_ROW;y++){
				printf("Zeile %2i: ",y);
				for(x=0;x<num_rows;x++){
					if(display[x][y].r!=0){
						//printf("\033[41;1;31m()\033[0m");
						printf("R");
					}else if(display[x][y].g!=0){
						//printf("\033[42;1;32m()\033[0m");
						printf("G");
					}else if(display[x][y].b!=0){
						//printf("\033[44;1;34m()\033[0m");
						printf("B");
					}else{
						printf("-");
					}
				}
				printf("\n");
			}
}


void display_set_row(RGB *led_array){
	uint8_t i;
	for(i=0;i<NUM_RGB_LEDS_PER_ROW;i++){
		display[current_row][i]=led_array[i];
	}

	if(current_row==num_rows){
		display_print();
	}
}

void display_set_row_rgb(uint8_t r,uint8_t g,uint8_t b){
	uint8_t i;
	for(i=0;i<NUM_RGB_LEDS_PER_ROW;i++){
		display[current_row][i].r=r;
		display[current_row][i].r=g;
		display[current_row][i].r=b;
	}
	printf("set_row_rgb\n");
}


void display_set_row_color(Color color){
	RGB temp_led=get_color(color);
	display_set_row_rgb(temp_led.r, temp_led.g, temp_led.b);
}

uint8_t get_random_value(uint8_t min, uint8_t max)
{
	return (rand() % max + min);
}
