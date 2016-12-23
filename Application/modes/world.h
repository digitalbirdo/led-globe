/*
 * world.h
 *
 *  Created on: 13.04.2014
 *      Author: netzwerg
 */
#ifdef SWITCH_WORLD

#ifndef WORLD_H_
#define WORLD_H_

// #################################################################################################
// INCLUDES

#include <stdint.h>

/**
 *  @defgroup world Mode: World
 *  @brief
 *
 *  @author Tobias Finke tofiit00@hs-esslingen.de
 *  @{
 */

// #################################################################################################
// PUBLIC DEFINES

// #################################################################################################
// PUBLIC VARIABLES

// #################################################################################################
// PUBLIC METHOD-DEFINITIONS

/**
 * @brief Mode for displaying the map of the world on the globe
 * @param index Column which should be displayed
 */
void mode_world_map(uint8_t index);

/**
 * @}
 */

#endif /* WORLD_H_ */

#endif
