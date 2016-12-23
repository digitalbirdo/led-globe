
// #################################################################################################
// INCLUDES

#include "modes.h"
#include "../display.h"

/**
 *  @addtogroup modes
 *  @{
 */

//#################################################################################################
// PRIVATE DEFINES

//#################################################################################################
// PRIVATE METHOD-DEFINITIONS

void mode_test(uint8_t index);
void mode_select_mode(uint8_t index);
void mode_rgb_fade(uint8_t index);
void mode_stripes(uint8_t index);
void mode_rain(uint8_t index);
void mode_manual(uint8_t index);


//#################################################################################################
// PRIVATE VARIABLES

uint8_t num_modes;

mode_fktn current_mode=mode_test;
Mode selected_mode = TEST;

RGB manual_color={0,0,0};
RGB leds[NUM_RGB_LEDS_PER_ROW];

mode_fktn modes_look_up_table[] = {
	mode_select_mode, 
	mode_rgb_fade, 
	mode_stripes, 
#ifdef SWITCH_CONWAY
	mode_game_of_life, 
#endif
	mode_rain,
#ifdef SWITCH_PACMAN
	mode_pacman,
#endif
#ifdef SWITCH_WORLD
	mode_world_map,
#endif
#ifdef SWITCH_PONG
	mode_pong,
#endif
#ifdef SWITCH_SNAKE
	mode_snake,
#endif
#ifdef SWITCH_FLAPPY
	mode_flappy,
#endif
	mode_test,
	mode_manual
	};

const char * modes_names_look_up_table[] = {
	"Sel Mode",
	"RGB Fade",
	"Stripes",
#ifdef SWITCH_CONWAY
	"GOL",
#endif
	"Rain",
#ifdef SWITCH_PACMAN
	"Pacman",
#endif
#ifdef SWITCH_WORLD
	"World Map",
#endif
#ifdef SWITCH_PONG
	"Pong",
#endif
#ifdef SWITCH_SNAKE
	"Snake",
#endif
#ifdef SWITCH_FLAPPY
	"Flappy",
#endif
	"Test",
	"Manual"
};


/**
 * @}
 */


// #################################################################################################
// PUBLIC METHODS

void modes_init(){
	num_modes = sizeof(modes_look_up_table)/sizeof(modes_look_up_table[0]);

	selected_mode = TEST;
	current_mode=mode_select_mode;
	
	//init modes
#ifdef SWITCH_PONG
	pong_init();
#endif
#ifdef SWITCH_SNAKE
	snake_init();
#endif
#ifdef SWITCH_FLAPPY
	flappy_init();
#endif
#ifdef SWITCH_PACMAN
	pacman_init();
#endif
	
	manual_color.r=0;
	manual_color.g=0;
	manual_color.b=0;
}

void mode_execute(uint8_t index){
	if(mode_select_mode != current_mode)
	{
		//by pressing SELECT in mode return to select mode
		if(is_button_pressed(SELECT))
		{
			current_mode = mode_select_mode;
		}
	}
	current_mode(index);
}

void mode_set(Mode set_mode){
	current_mode=modes_look_up_table[set_mode];
}


// #################################################################################################
// PRIVATE METHODS

void mode_select_mode(uint8_t index)
{
	RGB background = {0,0,0};
	RGB mode_color = {0,255,0};
	Mode previous_mode, next_mode;
	uint8_t x_pos, y_pos, tmp, i;

	//handle input
	if(is_button_pressed(SELECT))
	{
		mode_set(selected_mode);
	}
	if(is_button_pressed(UP))
	{
		tmp = selected_mode-1;
		if(tmp < 1 || tmp>selected_mode)
		{
			selected_mode = (Mode) (num_modes - 1);
		}
		else
		{
			selected_mode = (Mode) tmp;
		}
	}
	if(is_button_pressed(DOWN))
	{
		tmp = selected_mode+1;
		if(tmp >= num_modes || tmp<selected_mode)
		{
			selected_mode = (Mode) 1;
		}
		else
		{
			selected_mode = (Mode) tmp;
		}
	}

	//initialize previous and next mode
	if(selected_mode <= 1)
	{
		previous_mode = (Mode) (num_modes - 1);
	}
	else
	{
		previous_mode = (Mode) (selected_mode-1);
	}
	if(selected_mode >= (num_modes - 1))
	{
		next_mode = (Mode) 1;
	}
	else
	{
		next_mode = (Mode) (selected_mode+1);
	}

	//display
	for(i=0;i<NUM_RGB_LEDS_PER_ROW; i++)
	{
		leds[i]=background;
	}
	//display name of three modes
	//selected mode
	x_pos = 6;
	y_pos = (NUM_RGB_LEDS_PER_ROW/2)-(FONT_LETTER_HEIGHT/2);
	write_char_to_led('>',0,y_pos,mode_color,index);
	write_str_to_led(modes_names_look_up_table[selected_mode],x_pos,y_pos,mode_color,index);
	mode_color.g=100;
	//previous mode
	x_pos = 0;
	y_pos = (NUM_RGB_LEDS_PER_ROW/2)-(FONT_LETTER_HEIGHT/2)-FONT_LETTER_HEIGHT-4;
	write_str_to_led(modes_names_look_up_table[previous_mode],x_pos,y_pos,mode_color,index);
	//next mode
	x_pos = 0;
	y_pos = (NUM_RGB_LEDS_PER_ROW/2)-(FONT_LETTER_HEIGHT/2)+FONT_LETTER_HEIGHT+4;
	write_str_to_led(modes_names_look_up_table[next_mode],x_pos,y_pos,mode_color,index);

	display_set_row(leds);
}

void mode_test(uint8_t index){
	uint8_t i;
	static uint8_t x=0;

	if(x==num_rows){
		x=0;
	}

	x++;


	for(i=0;i<NUM_RGB_LEDS_PER_ROW;i++){
		if(i==x){
			leds[i].r=50;
			leds[i].g=0;
			leds[i].b=0;
		}else{
		leds[i].r=0;
		leds[i].g=0;
		leds[i].b=0;
		}
	}

	/* draw diagonale
	for(uint8_t i=0;i<index;i++){
		leds[i].r=MAX_HELLIGKEIT;
		leds[i].g=0;
		leds[i].b=0;
	}
	for(uint8_t i=index;i<NUM_RGB_LEDS_PER_ROW;i++){
		leds[i].r=0;
		leds[i].g=0;
		leds[i].b=0;
	}
	*/

	display_set_row(leds);

}

void mode_manual(uint8_t index){
	uint8_t i;
	for(i=0;i<NUM_LEDS_PER_ROW;i++){
		leds[i].r=manual_color.r;
		leds[i].g=manual_color.g;
		leds[i].b=manual_color.b;
	}

	display_set_row(leds);

	// Print the Color-Value every Frame
	/*
	if(index==0){
		uart_puts_P("RGB={");

		itoa(manual_color.r, buffer, 10);
		uart_puts(buffer);
		uart_puts_P(",");

		itoa(manual_color.g, buffer, 10);
		uart_puts(buffer);
		uart_puts_P(",");

		itoa(manual_color.b, buffer, 10);
		uart_puts(buffer);
		uart_puts_P("}\n");
	}
	*/
}

uint8_t color_offset=0;
void mode_rgb_fade(uint8_t index){
	uint8_t r,g,b;
	if(index==0){
		color_offset++;
	}

	hsv_to_rgb(index*(255/num_rows)+color_offset,255,15,&r,&g,&b);
	display_set_row_rgb(r,g,b);

}

void mode_stripes(uint8_t index){

	switch(index){
		case 0:
			display_set_row_color(RED);
			break;
		case 1:
			display_set_row_color(BLACK);
			break;
		case 2:
			display_set_row_color(BLUE);
			break;
		case 3:
			display_set_row_color(BLACK);
			break;
		case 4:
			display_set_row_color(GREEN);
			break;
		case 5:
			display_set_row_color(BLACK);
			break;
	}
}


void mode_rain(uint8_t index){

}


