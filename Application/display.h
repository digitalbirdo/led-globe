/*
 * globe.h
 *
 *  Created on: 31.03.2014
 *      Author: netzwerg
 */

#ifndef GLOBE_H_
#define GLOBE_H_

#include <stdint.h>
#include "util.h"

/**
 *  @defgroup display Globe-Display
 *  @brief Logic behind displaying content on the LEDs
 *
 *  @author Tobias Finke tofiit00@hs-esslingen.de
 *
 *  @todo rename row to column!
 *  @{
 */


extern uint8_t current_row;	//!< current row-number. This variable gets 0 when the sync-interrupt happens.
extern uint8_t num_rows;	//!< number of rows between the last and the second last sync-interrupt


#define NUM_RGB_LEDS_PER_ROW 48											//!< Number of RGB-led-chips per row
#define NUM_LEDS_PER_ROW (NUM_RGB_LEDS_PER_ROW)							//!< Number of RGB-led-chips per row
#define NUM_SINGLE_LEDS_PER_ROW (NUM_RGB_LEDS_PER_ROW*3)				//!< Number of PWM-Channels per row
#define NUM_PWM_CHANNEL_PER_WS2803 18									//!< Number of PWM-Channels one WS2803-Chip can handle
#define NUM_WS2803 (NUM_SINGLE_LEDS_PER_ROW/NUM_PWM_CHANNEL_PER_WS2803)	//!< Number of WS2803-Chips used in the project an connected over SPI

/**
 * @bug get other power-supply
 */
#define MAX_HELLIGKEIT 50	//!< Maximum Brightness if all leds are on. Otherwhise the power-supply can't handle the load.

/**
 * @brief init the display
 */
void display_init();

/**
 * @brief send a row-pattern over spi to the ws2803-chain
 * @param led_array row-pattern of rgb-values
 */
void display_set_row(RGB *led_array);

/**
 * @brief Set a whole row to a specified color
 * @param color color of the row
 */
void display_set_row_color(Color color);

/**
 * @brief Set a whole row to a specified color
 * @param r value of red   in the rgb-colorspace
 * @param g value of green in the rgb-colorspace
 * @param b value of blue  in the rgb-colorspace
 */
void display_set_row_rgb(uint8_t r,uint8_t g,uint8_t b);

/**
 * @brief Set the number of rows per cycle
 * @param num number of rows per cycle
 */
void display_set_num_rows(uint8_t num);

/**
 * @brief get the number of rows per cycle
 * @return number of rows per cycle
 */
uint8_t display_get_num_rows();

/**
 * @brief get a random number between the bgiven borders
 * @param min minimum value of the random number
 * @param max maximum value of the random number
 * @return generated random number
 */
uint8_t get_random_value(uint8_t min, uint8_t max);

/**
 * @brief setup a seed for the generation of random numbers
 * @note should be called once at startup
 * @todo check if this works ok and genearates a real random seed!
 */
void setup_seed();

/**@}*/


#endif /* GLOBE_H_ */
