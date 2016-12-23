
// #################################################################################################
// INCLUDES

#include <stdio.h>
#include <stdint.h>
#include "display.h"
#include "input.h"
#include "modes/modes.h"
#include "sync.h"
#include "debug.h"

/**
 *  @defgroup main Main
 *  @brief
 *  @author Tobias Finke tofiit00@hs-esslingen.de
 *  @author Clemens Weissenberg clweit00@hs-esslingen.de
 *  @{
 */

// #################################################################################################
// PRIVATE DEFINES

// #################################################################################################
// PRIVATE VARIABLES

// #################################################################################################
// PRIVATE METHOD-DEFINITIONS

/**
 * @brief Main-Loop
 * @return not used, because it's an endless loop and we will hopefully never return ;)
 */
int main(void);


/**
 * @}
 */

// #################################################################################################
// PRIVATE METHODS

int main(void)
{
	// init serial interface

	input_init();

	// init interrupts/reed-switch
	sync_init();

	// init modes
	modes_init();

	// init display
	display_init();

	//debug_string("yay debug tut");

	current_row=0;

	while(1){

		// generate the "sync_interrupt_flag"
		/*
		if(current_row>50){
			enable_sync_interrupt();
		}else{
			disable_sync_interrupt();
		}
		*/
		if(sync_is_active() && sync_interrupt_enabled){
				sync_interrupt_flag=1;
		}

		if(current_row==50){
			enable_sync_interrupt();
		}


		// got the interrupt and start a new frame
		if(sync_interrupt_flag){


			// receive inputs from PC to change modes or get commands
			process_input();

			num_rows=current_row-1;
			sync_interrupt_flag=0;		// clear flag
			current_row=0;				// we start at the first row
			//debug_string("Num_rows=");
			//debug_int(num_rows);
			//debug_string("\n");
		}


		// compute and display a row of a specified mode
#ifdef AVR
		mode_execute((num_rows-1)-current_row);
#else
		mode_execute(current_row);
#endif
		// point to the next row
		current_row++;
	}
}
