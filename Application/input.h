#ifndef INPUT_H_
#define INPUT_H_

// #################################################################################################
// INCLUDES

#include <stdint.h>
#include <stdio.h>
#include "../Application/modes/modes.h"
#include "../Application/display.h"

/**
 *  @defgroup input Input
 *  @brief
 *  @author Tobias Finke tofiit00@hs-esslingen.de
 *  @author Clemens Weissenberg clweit00@hs-esslingen.de
 *  @{
 */

// #################################################################################################
// PUBLIC DEFINES

//counter for antibeat algorithm (max. 2^7 = 128)
#define NUM_TICKS_ANTIBEAT 5
#define NUM_BUTTONS 5

// #################################################################################################
// PUBLIC VARIABLES

typedef enum buttons{
	UP=0,
	DOWN,
	LEFT,
	RIGHT,
	SELECT
}Button;

// #################################################################################################
// PUBLIC METHOD-DEFINITIONS

void input_init();
uint8_t is_button_pressed(Button button);
void check_button_flags(uint8_t);
void process_input();


/**
 * @}
 */






#endif /* INPUT_H_ */
