/*
 * input.c
 *
 *  Created on: 08.04.2014
 *      Author: netzwerg
 */



#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"

#include "../Application/input.h"
#include <avr/pgmspace.h>
#include "../Application/modes/modes.h"

#include "reed_switch.h"
#include "btm222.h"
#include <util/delay.h>
#include "../Application/display.h"
#include "timer.h"
#include "../Application/modes/modes.h"

uint8_t buttonflags[NUM_BUTTONS];

#define UART_BAUD_RATE      19200

timer_overflow_fktn ov=input_init;
void input_init()
{
	DDRB |=(1<<6);
	PORTB &= ~(1 << 6);
	_delay_ms(500);
	PORTB|=(1<<6);
	_delay_ms(500);
	PORTB &= ~(1 << 6);



	//btm222_init();
	PORTB|=(1<<6);

	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	sei();

	uart_puts_P("LED-Globe v1.0\n");


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
	uint8_t ret=0;
	if(0x01 & buttonflags[button]){
		buttonflags[button]=0;
		ret=1;
	}
	return ret;
}

void check_button_flags(uint8_t c)
{
	//TODO: getchar waits for user input but it shouldn't.
	uint8_t pressed_button = c;
	dec_antibeat_counters();
	switch(pressed_button)
	{
	case 0x1E:
	{
		set_button_flag(UP);
		break;
	}
	case 0x1F:
	{
		set_button_flag(DOWN);
		break;
	}
	case 0x1C:
	{
		set_button_flag(LEFT);
		break;
	}
	case 0x1D:
	{
		set_button_flag(RIGHT);
		break;
	}

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

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void process_input(){
	uint8_t c= ' ';
	if(uart_available()){
		c = uart_getc();
		uart_putc(c);

		switch (c) {
			case '?':
				uart_puts_P("LED-Globe \n");
				uart_puts_P("Directions:\nw = up\na = left\ns = down\nd = right\n\n");

				uart_puts_P("\nModes:\n");
				uart_puts_P("f = RGB-Fade\n");
				uart_puts_P("t = Testing\n");
				uart_puts_P("m = Manual color-selection\n");
				uart_puts_P("    r|g|b = decrease color-value\n");
				uart_puts_P("    R|G|B = increase color-value\n");
				uart_puts_P("p = Pong (Game)\n");
				uart_puts_P("n = Snake (Game)\n");
				uart_puts_P("l = Game of Life (Animation)\n");
				uart_puts_P("x = Dots (Animation)\n");

				uart_puts_P("\nOptions:\n");
				uart_puts_P("D = Debugging on/off\n");
				uart_puts_P("o = Rotation on/off\n");


				// How much RAM do we have available?
				uint8_t buffer[10];
				uart_puts_P("available RAM: ");
				itoa(freeRam(), buffer, 10);
				uart_puts(buffer);
				uart_puts_P(" Byte\n");

				// How many rows are displayed?
				uart_puts_P("Number of displayed Rows: ");
				itoa(num_rows, buffer, 10);
				uart_puts(buffer);

				break;

			// Commands for games and directions
			//     w
			//     ^
			// a < + > d
			//     v
			//     s
				//1E hoch
				//1f runer
				//1D rechts
				//1C links
			case 0x1e:
				//check_button_flags(c);
				//uart_puts_P("UP pressed \n");
				break;
			case 0x1C:
				//check_button_flags(c);
				//uart_puts_P("LEFT pressed \n");
				break;
			case 0x1f:
				//check_button_flags(c);
				//uart_puts_P("DOWN pressed \n");
				break;
			case 0x1D:
				//check_button_flags(c);
				//uart_puts_P("RIGHT pressed \n");
				break;


			case 'w':
				//check_button_flags(c);
				uart_puts_P("UP pressed \n");
				break;
			case 'a':
				//check_button_flags(c);
				uart_puts_P("LEFT pressed \n");
				break;
			case 's':
				//check_button_flags(c);
				uart_puts_P("DOWN pressed \n");
				break;
			case 'd':
				//check_button_flags(c);
				uart_puts_P("RIGHT pressed \n");
				break;
			case '#':
				//check_button_flags(c);
				uart_puts_P("SELECT pressed \n");
				break;

			// Modes
			case 'f':
				mode_set(RGB_FADE);
				uart_puts_P("Fading Leds... \n");
				break;
			case 't':
				mode_set(TEST);
				uart_puts_P("Testing... \n");
				break;
			case 'm':
				manual_color.r=0;
				manual_color.g=0;
				manual_color.b=0;
				mode_set(MANUAL);
				uart_puts_P("Manual Colorselection started... \n");
				break;
			case 'p':
				pong_init();
				mode_set(PONG);
				uart_puts_P("Pong started... \n");
				break;
			case 'n':
				mode_set(SNAKE);
				uart_puts_P("Snake started... \n");
				break;
#ifdef SWITCH_CONWAY
			case 'l':
				reset_cgol();
				mode_set(GAME_OF_LIFE);
				uart_puts_P("Game of Life started... \n");
				break;
#endif
			case 'x':
				mode_set(RAIN);
				uart_puts_P("rain started... \n");
				break;
#ifdef SWITCH_WORLD
			case 'o':
				mode_set(WORLD_MAP);
				uart_puts_P("world started... \n");
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

		/*
		char buffer[7];
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

		uart_puts_p("Num_Rows=");
		itoa(num_rows, buffer, 10);
		uart_puts(buffer);
		uart_puts_P("}\n");
		*/
	}
	check_button_flags(c);
}

