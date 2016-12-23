/**************************************************************
*
*   Studienarbeit:  LED-Globe
*   Autoren:        Tobias Finke, Clemens Weissenberg
*
*   Erstellt am:    03.04.2014
*   Datei:          pong.h
*
***************************************************************/

#ifndef PONG_H_
#define PONG_H_

/**
 *  @defgroup mode_pong Mode: Pong
 *  @brief cover of the game pong for one player
 *
 *  @author Clemens Weissenberg clweit00@hs-esslingen.de
 *  @{
 */

// #################################################################################################
// INCLUDES

#include <stdint.h>
#include "../input.h"
#include "../display.h"
#include "../font.h"

// #################################################################################################
// PUBLIC DEFINES

/**
 * @brief	count of LED-cols of the field
 */
#define PONG_X_WIDTH_FIELD num_rows
/**
 * @brief	count of LED-rows of the field
 */
#define PONG_Y_WIDTH_FIELD NUM_RGB_LEDS_PER_ROW

/**
 * @brief	indent of the playing-zone of the field
 */
#define PONG_BORDER_INDENT 10
/**
 * @brief	index of top-border of the playing-zone of the field
 */
#define PONG_TOP_BORDER PONG_BORDER_INDENT
/**
 * @brief	index of top-border of the playing-zone of the field
 */
#define PONG_BOTTOM_BORDER ((PONG_Y_WIDTH_FIELD-PONG_BORDER_INDENT)-1)
/**
 * @brief	index of left-border of the playing-zone of the field
 */
#define PONG_LEFT_BORDER 0
/**
 * @brief	index of right-border of the playing-zone of the field
 */
#define PONG_RIGHT_BORDER (PONG_X_WIDTH_FIELD-1)

/**
 * @brief	x-position of the starting position of the ball
 */
#define PONG_X_BALL_START (PONG_X_WIDTH_FIELD/2)
/**
 * @brief	y-position of the starting position of the ball
 */
#define PONG_Y_BALL_START (PONG_Y_WIDTH_FIELD/2)
/**
 * @brief	starting movingvector of the ball
 */
#define PONG_MOV_BALL_VEC_START 0x11
/**
 * @brief	max speed in x-direction
 * 			
 * @note	WARNING: 7 IS MAX!
 */
#define PONG_BALL_MAX_SPEED_X 1
/**
 * @brief	max speed in y-direction
 * 			
 * @note	WARNING: 7 IS MAX!
 */
#define PONG_BALL_MAX_SPEED_Y 2

/**
 * @brief	width of paddle
 */
#define PONG_PADDLE_WIDTH 8
/**
 * @brief	y-position of the starting position of the paddle
 */
#define PONG_Y_PADDLE_START ((PONG_Y_WIDTH_FIELD/2)-(PONG_PADDLE_WIDTH/2))
/**
 * @brief	step size of the paddle
 */
#define PONG_PADDLE_STEP 2

/**
 * @brief	frames per computation
 */
#define PONG_FRAMES_PER_COMPUTATION 1

// #################################################################################################
// PUBLIC VARIABLES

extern RGB leds[NUM_RGB_LEDS_PER_ROW];

// #################################################################################################
// PUBLIC METHODS
 
/**
 * @brief	Initalitation of pong.
 */
void pong_init();

/**
 * @brief	The main peace of the game pong. It is were the sequence of the game is defined.
 *
 * @param	index	Zero-based index of the display row which will currently be displayed.
 */
void mode_pong(uint8_t index);

/**
 * @brief	Initalitation of pong.
 *
 * @return the score
 */
uint16_t pong_get_score();

/**
 * @}
 */

#endif /* PONG_H_ */
