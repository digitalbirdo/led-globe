/*
 * font.h
 *
 *  Created on: 19.04.2014
 *      Author: Clemens
 */

#ifndef FONT_H_
#define FONT_H_

/**
 *  @defgroup font Font
 *  @brief letters and symbols to write
 *
 *	@todo	refactor functions for better performance
 *			rename functions led --> display
 *
 *  @author Clemens Weissenberg clweit00@hs-esslingen.de
 *  @{
 */

// #################################################################################################
// INCLUDES

#include "display.h"
#include <stdint.h>
#include <stdlib.h>
#include "debug.h"

// #################################################################################################
// PUBLIC DEFINES

#ifdef AVR
#include <avr/pgmspace.h>
#else
#define PROGMEM /**/
#endif

/**
 * @brief	width of each letter or symbol
 */
#define FONT_LETTER_WIDTH 4
/**
 * @brief	height of each letter or symbol
 */
#define FONT_LETTER_HEIGHT 5
/**
 * @brief	pixel between two letters or symbols
 */
#define FONT_SPACE_BETWEEN_LETTER 1

/**
 * @brief	max count of letters per row on display
 * 			
 * @note	if the text is longer than max count it will be cut
 */
#define FONT_MAX_LETTERS_IN_ROW (num_rows/(FONT_LETTER_WIDTH + FONT_SPACE_BETWEEN_LETTER))
/**
 * @brief	max count of digits of number
 * 			
 * @note	max number = 10^FONT_MAX_NUM_DIGITS
 */
#define FONT_MAX_NUM_DIGITS 11

// #################################################################################################
// PUBLIC METHODS

/**
 * @brief	writes string to display
 * 			
 * @param	str		string to write
 * @param	x_pos	x-position of first letter
 * @param	y_pos	y-position of first letter
 * @param	color	color of letters
 * @param	index	Zero-based index of the display row which will currently be displayed.
 */
void write_str_to_led(const char* str, uint8_t x_pos, uint8_t y_pos, RGB color, uint8_t index);
/**
 * @brief	writes char to display
 * 			
 * @param	str		string to write
 * @param	x_pos	x-position of first letter
 * @param	y_pos	y-position of first letter
 * @param	color	color of letters
 * @param	index	Zero-based index of the display row which will currently be displayed.
 */
void write_char_to_led(const char ch, uint8_t x_pos, uint8_t y_pos, RGB color, uint8_t index);
/**
 * @brief	writes number to display
 * 			
 * @param	str		string to write
 * @param	x_pos	x-position of first letter
 * @param	y_pos	y-position of first letter
 * @param	color	color of letters
 * @param	index	Zero-based index of the display row which will currently be displayed.
 */
void write_int_to_led(const uint32_t num, uint8_t x_pos, uint8_t y_pos, RGB color, uint8_t index);

// #################################################################################################
// PUBLIC VARIABLES

extern RGB leds[];

#endif /* FONT_H_ */
