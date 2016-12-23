#ifndef FLAPPY_H_
#define FLAPPY_H_

/**
 *  @defgroup mode_flappy Mode: Flappy-Bird
 *  @brief Flappy Bird is a cover of the game which is originally coded by Dong Nguyen
 *
 *  @author Clemens Weissenberg clweit00@hs-esslingen.de
 *  @{
 */

// #################################################################################################
// INCLUDES

#include <stdint.h>
#include <stdlib.h>
#include "../input.h"
#include "../display.h"

// #################################################################################################
// PUBLIC DEFINES

/**
 * @brief	count of LED-cols of the field
 */
#define FLAPPY_X_WIDTH_FIELD num_rows
/**
 * @brief	count of LED-rows of the field
 */
#define FLAPPY_Y_WIDTH_FIELD NUM_RGB_LEDS_PER_ROW

/**
 * @brief	indent of the playing-zone of the field
 */
#define FLAPPY_BORDER_INDENT 10
/**
 * @brief	index of top-border of the playing-zone of the field
 */
#define FLAPPY_TOP_BORDER FLAPPY_BORDER_INDENT
/**
 * @brief	index of top-border of the playing-zone of the field
 */
#define FLAPPY_BOTTOM_BORDER ((FLAPPY_Y_WIDTH_FIELD-FLAPPY_BORDER_INDENT)-1)
/**
 * @brief	index of left-border of the playing-zone of the field
 */
#define FLAPPY_LEFT_BORDER 0
/**
 * @brief	index of right-border of the playing-zone of the field
 */
#define FLAPPY_RIGHT_BORDER (FLAPPY_X_WIDTH_FIELD-1)

/**
 * @brief	frames per computation
 */
#define FLAPPY_FRAMES_PER_COMPUTATION 1

/**
 * @brief	x-index of the bird of the playing-zone in the field
 * @note	x-position has to be smaller than space between obstacles!
 */
#define FLAPPY_BIRD_X_POSITION 10
/**
 * @brief	x-speed of the bird (pixels per computation)
 */
#define FLAPPY_BIRD_X_SPEED 1
/**
 * @brief	max y-speed in upward direction of the bird (pixels per computation)
 */
#define FLAPPY_BIRD_MAX_Y_UP_SPEED 2
/**
 * @brief	max y-speed in downward direction of the bird (pixels per computation)
 */
#define FLAPPY_BIRD_MAX_Y_DOWN_SPEED 2
/**
 * @brief	width and height of the bird (pixels)
 */
#define FLAPPY_BIRD_WIDTH_AND_HEIGHT 3

/**
 * @brief	width of the obstabcle (pixels)
 */
#define FLAPPY_OBSTACLE_WIDTH 4
/**
 * @brief	max height of the obstabcle (pixels)
 */
#define FLAPPY_OBSTACLE_MAX_HEIGHT 18
/**
 * @brief	min passage width in the obstabcle (pixels)
 */
#define FLAPPY_OBSTACLE_MIN_PASSAGE_WIDTH (FLAPPY_BIRD_WIDTH_AND_HEIGHT+6)
/**
 * @brief	max passage width in the obstabcle (pixels)
 */
#define FLAPPY_OBSTACLE_MAX_PASSAGE_WIDTH ((FLAPPY_BOTTOM_BORDER-FLAPPY_TOP_BORDER)-FLAPPY_OBSTACLE_MAX_HEIGHT)
/**
 * @brief	space between one obstacle and the next obstacle (pixels)
 */
#define FLAPPY_SPACE_BETWEEN_OBSTACLE 20

// #################################################################################################
// PUBLIC VARIABLES

extern RGB leds[NUM_RGB_LEDS_PER_ROW]; //!< numbers of LEDs per Row

// #################################################################################################
// PUBLIC METHODS
 
/**
 * @brief	Initalitation of flappy bird.
 */
void flappy_init();

/**
 * @brief	The main peace of the game flappy bird. It is were the sequence of the game is defined.
 *
 * @param	index	Zero-based index of the display row which will currently be displayed.
 */
void mode_flappy(uint8_t index);

/**
 * @brief	Initalitation of flappy bird.
 *
 * @return the score
 */
uint16_t flappy_get_score();

/**
 * @}
 */

#endif /* FLAPPY_H_ */