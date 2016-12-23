#ifdef SWITCH_PACMAN
#ifndef PACMAN_FIELD_H_
#define PACMAN_FIELD_H_

// #################################################################################################
// INCLUDES

#ifdef AVR
#include <avr/pgmspace.h>
#else
#define PROGMEM /**/
#endif
#include <stdint.h>


/**
 *  @addtogroup mode_pacman
 *  @{
 */

//#################################################################################################
// PUBLIC DEFINES

#define PACMAN_FIELD_WIDTH 84	//!< A constant that defines pacman field width.
#define PACMAN_FIELD_HEIGHT 93	//!< A constant that defines pacman field height.
#define PACMAN_FOOD_FIELD_WIDTH ((PACMAN_FIELD_WIDTH-4)/3)		//!< Width of the pacman food field.
#define PACMAN_FOOD_FIELD_HEIGHT ((PACMAN_FIELD_HEIGHT-4)/3)	//!< Height of the pacman food field.

// #################################################################################################
// PUBLIC METHODS

/**
 * @brief	Checks if wall at certain position.
 *
 * @param	x	x-coordinate.
 * @param	y	y-coordinate.
 *
 * @return	0x00 nothing; 0x01 for wall; 0x02 for cage.
 */
uint8_t is_wall_at(uint8_t x, uint8_t y);


/**
 * @brief	Checks if food is on certain position.
 *
 * @param	x	x-coordinate.
 * @param	y	y-coordinate.
 *
 * @return	0x00 no food; 0x01 food; 0x02 special food.
 */
uint8_t is_food_at(uint8_t x, uint8_t y);


/**
 * @brief	Checks if all food is gone.
 *
 * @return	0x01=all food is gone; 0x00=there is food left.
 */
uint8_t is_all_food_gone();


/**
 * @brief	Deletes the food at certain position.
 *
 * @param	x	x-coordinate of food.
 * @param	y	y-coordinate of food.
 * 				
 * @note	does not check if food is there
 */
void delete_food_at(uint8_t x, uint8_t y);


/**
 * @brief	Initialises the food.
 */
void init_food();

/**
 * @}
 */

#endif /* PACMAN_FIELD_H_ */
#endif
