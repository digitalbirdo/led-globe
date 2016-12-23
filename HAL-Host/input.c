/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *  Studienarbeit: LED-Globe
 *
 *  File: input.c
 *
 *  Created on: 09.04.2014
 *      Author: Clemens
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "../Application/input.h"


uint8_t buttonflags[NUM_BUTTONS];

void input_init()
{
	int i=0;
	for(i=0; i<NUM_BUTTONS; i++)
	{
		buttonflags[i] = 0x00;
	}
}

void set_button_flag(Button button)
{
	//antibeat
	// only set flag if it is not already set.
	if((buttonflags[button] >> 1) < 1)
	{
		buttonflags[button] = 0x01 | ((uint8_t) NUM_TICKS_ANTIBEAT << 1);
	}
}

void dec_antibeat_counters()
{
	int i=0;
	uint8_t tmp;
	for(i=0; i<NUM_BUTTONS; i++)
	{
		tmp = buttonflags[i] >> 1;
		if(0 == tmp)
		{
			buttonflags[i] = 0x00;
		}
		else
		{
			buttonflags[i] = 0x00 | ((tmp-1) << 1);
		}
	}
}

uint8_t is_button_pressed(Button button)
{
	if(0x01 & buttonflags[button]){
		buttonflags[button]=0;
		return 1;
	}
	return 0;
}

void check_button_flags(uint8_t c)
{
	//TODO: getchar waits for user input but it shouldn't.
	uint8_t pressed_button = c;
	dec_antibeat_counters();
	switch(pressed_button)
	{
	case 'w':
	{
		set_button_flag(UP);
		break;
	}
	case 's':
	{
		set_button_flag(DOWN);
		break;
	}
	case 'a':
	{
		set_button_flag(LEFT);
		break;
	}
	case 'd':
	{
		set_button_flag(RIGHT);
		break;
	}
	case '#':
	{
		set_button_flag(SELECT);
		break;
	}
	default:
	{
		break;
	}
	}
}

void process_input(){
	char c=' ';
	if(current_row==56){
		c=getchar();
		fflush(stdin);
		//sleep(1);

		switch (c) {
			case '?':
				printf("LED-Globe \n");
				printf("Directions:\nw = up\na = left\ns = down\nd = right\n\n");

				printf("\nModes:\n");
				printf("f = RGB-Fade\n");
				printf("t = Testing\n");
				printf("m = Manual color-selection\n");
				printf("    r|g|b = decrease color-value\n");
				printf("    R|G|B = increase color-value\n");
				printf("p = Pong (Game)\n");
				printf("n = Snake (Game)\n");
				printf("l = Game of Life (Animation)\n");
				printf("x = Dots (Animation)\n");

				printf("\nOptions:\n");
				printf("D = Debugging on/off\n");
				printf("o = Rotation on/off\n");

				break;

			// Commands for games and directions
			//     w
			//     ^
			// a < + > d
			//     v
			//     s
			case 'w':
				//check_button_flags(c);
				printf("UP pressed \n");
				break;
			case 'a':
				//check_button_flags(c);
				printf("LEFT pressed \n");
				break;
			case 's':
				//check_button_flags(c);
				printf("DOWN pressed \n");
				break;
			case 'd':
				//check_button_flags(c);
				printf("RIGHT pressed \n");
				break;
			case '#':
				//check_button_flags(c);
				printf("SELECT pressed \n");
				break;

			// Modes
			case 'f':
				mode_set(RGB_FADE);
				printf("Fading Leds... \n");
				break;
			case 't':
				mode_set(TEST);
				printf("Testing... \n");
				break;
			case 'm':
				mode_set(MANUAL);
				printf("Manual Colorselection started... \n");
				break;
#ifdef SWITCH_PONG
			case 'p':
				mode_set(PONG);
				printf("Pong started... \n");
				break;
#endif
#ifdef SWITCH_SNAKE
			case 'n':
				mode_set(SNAKE);
				printf("Snake started... \n");
				break;
#endif
#ifdef SWITCH_PACMAN
			case 'c':
				mode_set(PACMAN);
				printf("Pacman started... \n");
				break;
#endif
#ifdef SWITCH_CONWAY
			case 'l':
				mode_set(GAME_OF_LIFE);
				printf("Game of Life started... \n");
				break;
#endif
			case 'x':
				mode_set(RAIN);
				printf("rain started... \n");
				break;
#ifdef SWITCH_WORLD
			case 'o':
				mode_set(WORLD_MAP);
				printf("world started... \n");
				break;
#endif


			// changing color in mode_manual
			case 'r':
				manual_color.r--;
				break;
			case 'g':
				manual_color.g--;
				break;
			case 'b':
				manual_color.b--;
				break;
			case 'R':
				manual_color.r++;
				break;
			case 'G':
				manual_color.g++;
				break;
			case 'B':
				manual_color.b++;
				break;
			default:
				break;
		}

		printf("RGB={%i,%i,%i} CurrentROW=%i numrows=%i\n",manual_color.r,manual_color.g,manual_color.b,current_row,num_rows);
	}
	check_button_flags(c);
}

