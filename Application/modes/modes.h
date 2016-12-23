#ifndef MODES_H_
#define MODES_H_

// #################################################################################################
// MODE SWITCHES

#define SWITCH_GAMES
#ifdef SWITCH_GAMES
#define SWITCH_PONG
#define SWITCH_SNAKE
#define SWITCH_FLAPPY
//#define SWITCH_PACMAN
#endif

#define SWITCH_ALGORITHMS
#ifdef SWITCH_ALGORITHMS
#define SWITCH_CONWAY
#define SWITCH_WORLD
#endif

// #################################################################################################
// INCLUDES

#include <stdint.h>
#include "../display.h"
#include "../font.h"
#include "../input.h"


#ifdef SWITCH_PONG
#include "pong.h"
#endif
#ifdef SWITCH_SNAKE
#include "snake.h"
#endif
#ifdef SWITCH_FLAPPY
#include "flappy.h"
#endif
#ifdef SWITCH_PACMAN
#include "pacman.h"
#endif
#ifdef SWITCH_CONWAY
#include "conway.h"
#endif
#ifdef SWITCH_WORLD
#include "world.h"
#endif



/**
 *  @defgroup modes Mode-Select
 *  @brief handle switching between modes which are displayed on the Led-Globe
 *
 *  @author Tobias Finke tofiit00@hs-esslingen.de
 *  @author Clemens Weissenberg clweit00@hs-esslingen.de
 *  @{
 */

// #################################################################################################
// PUBLIC DEFINES

// #################################################################################################
// PUBLIC VARIABLES

typedef void (*mode_fktn) (uint8_t);
extern RGB manual_color;
extern RGB leds[NUM_RGB_LEDS_PER_ROW];

typedef enum modes{
	SELECT_MODE = 0,
	RGB_FADE,
	STRIPES,
#ifdef SWITCH_CONWAY
	GAME_OF_LIFE,
#endif
	RAIN,
#ifdef SWITCH_PACMAN
	PACMAN,
#endif
#ifdef SWITCH_WORLD
	WORLD_MAP,
#endif
#ifdef SWITCH_PONG
	PONG,
#endif
#ifdef SWITCH_SNAKE
	SNAKE,
#endif
#ifdef SWITCH_FLAPPY
	FLAPPY,
#endif
	TEST,
	MANUAL
}Mode;


// #################################################################################################
// PUBLIC METHOD-DEFINITIONS

void modes_init();

void mode_execute(uint8_t index);

void mode_set(Mode set_mode);

/**
 * @}
 */


#endif /* MODES_H_ */
