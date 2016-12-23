
#ifdef SWITCH_PACMAN
#ifndef PACMAN_H_
#define PACMAN_H_

//#################################################################################################
// PUBLIC INCLUDES

#include <stdint.h>
#include <stdlib.h>
#include "../input.h"
#include "../display.h"
#include "../font.h"
#include "pacman_field.h"

#ifdef AVR
#include <avr/pgmspace.h>
#else
#define PROGMEM /**/
#endif

/**
 *  @defgroup mode_pacman Mode: Pacman
 *  @brief
 *  @todo Dokumentieren :)
 *
 *  @author Clemens Weissenberg clweit00@hs-esslingen.de
 *  @{
 */

//#################################################################################################
// PUBLIC DEFINES

//#################################################################################################
// PUBLIC VARIABLES

extern RGB leds[NUM_LEDS_PER_ROW];


//#################################################################################################
// PUBLIC METHOD-DEFINITIONS

/**
 * @brief	A constant that defines pacman display field width.
 */
#define PACMAN_DISPLAY_FIELD_WIDTH num_rows

/**
 * @brief	A constant that defines pacman display field height.
 */
#define PACMAN_DISPLAY_FIELD_HEIGHT NUM_LEDS_PER_ROW

/**
 * @brief	A macro that defines pacman taker width and height.
 */
#define PACMAN_TAKER_WIDTH_AND_HEIGHT 5

/**
 * @brief	A macro that defines pacman frames per computation.
 */
#define PACMAN_FRAMES_PER_COMPUTATION 1


/**
 * @brief	Initalitation of Pacman.
 */
void pacman_init();

/**
 * @brief	The main peace of the game pacman. It is were the sequence of the game is defined.
 *
 * @param	index	Zero-based index of the display row which will currently be displayed.
 * 					
 * @todo	[Pacman_Biting_Ghost Extension]: eating routine has to be changed
 */
void mode_pacman(uint8_t index);

/**
 * @brief	get score.
 *
 * @return	An uint16_t.
 */
uint16_t pacman_get_score();

/**
 * @}
 */

#endif /* PACMAN_H_ */
#endif
