/**************************************************************
*
*   Studienarbeit:  LED-Globe
*   Autoren:        Tobias Finke, Clemens Weissenberg
*
*   Erstellt am:    15.04.2014
*   Datei:          snake.h
*
***************************************************************/

#ifndef SNAKE_H_
#define SNAKE_H_

/**
 *  @defgroup snake Mode: Snake
 *  @brief the mobilephone game snake
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
#define SNAKE_X_WIDTH_FIELD num_rows
/**
 * @brief	count of LED-rows of the field
 */
#define SNAKE_Y_WIDTH_FIELD NUM_RGB_LEDS_PER_ROW

/**
 * @brief	length of the snake at the beginning
 */
#define SNAKE_START_LENGTH 5;
/**
 * @brief	maximal length of the snake
 */
#define SNAKE_MAX_LENGTH 80

/**
 * @brief	x-coordinate of the head of the sneak at the beginning
 */
#define SNAKE_HEAD_START_X_POSITION (SNAKE_X_WIDTH_FIELD/2)

/**
 * @brief	y-coordinate of the head of the sneak at the beginning
 */
#define SNAKE_HEAD_START_Y_POSITION (SNAKE_Y_WIDTH_FIELD/2)

/**
 * @brief	indent of the playing-zone of the field
 */
#define SNAKE_BORDER_INDENT 10
/**
 * @brief	index of top-border of the playing-zone of the field
 */
#define SNAKE_TOP_BORDER SNAKE_BORDER_INDENT
/**
 * @brief	index of top-border of the playing-zone of the field
 */
#define SNAKE_BOTTOM_BORDER ((SNAKE_Y_WIDTH_FIELD-SNAKE_BORDER_INDENT)-1)

/**
 * @brief	frames per computation
 */
#define SNAKE_FRAMES_PER_COMPUTATION 1

// #################################################################################################
// PUBLIC VARIABLES

extern RGB leds[NUM_RGB_LEDS_PER_ROW];

// #################################################################################################
// PUBLIC METHODS
 
void snake_init();
void mode_snake(uint8_t index);

uint16_t snake_get_score();

/**
 * @}
 */

#endif /* SNAKE_H_ */
