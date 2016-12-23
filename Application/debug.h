#ifndef DEBUG_H_
#define DEBUG_H_

// #################################################################################################
// INCLUDES

#include <stdint.h>


/**
 *  @defgroup debug Debug
 *  @brief
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
 * display a strig to the terminal
 * @param s String which should be displayed
 */
void debug_string(const char * s);

/**
 * display an integer to the terminal
 * @param x Value which should be displayed
 */
void debug_int(uint8_t x);

/**
 * @}
 */

#endif /* DEBUG_H_ */
