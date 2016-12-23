/*
 * conway.h
 *
 *  Created on: 12.04.2014
 *      Author: netzwerg
 */
#ifdef SWITCH_CONWAY
#ifndef CONWAY_H_
#define CONWAY_H_

// #################################################################################################
// INCLUDES

/**
 *  @defgroup mode_conway Alorythm: Game of Life
 *  @brief displays the Game of Life Algorythm developped by Connway
 *
 *  @author Tobias Finke info@digitalbird.de
 *  @{
 */
// #################################################################################################
// PUBLIC DEFINES

// #################################################################################################
// PUBLIC METHODS

/**
 * @brief
 * @note see a demo at: https://www.youtube.com/watch?v=Q7BnNd866O8
 * @param index
 */
void mode_game_of_life(uint8_t index);

/**
 * @brief Init Conways Game of Life
 *
 * A startpattern is generated which consists of Gliders or expanding patterns.
 */
void cgol_init();

/**
 * @brief Re-init Game of Life
 */
void reset_cgol();

/**
 * @}
 */

#endif /* CONWAY_H_ */

#endif
