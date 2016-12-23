#ifndef SYNC_H_
#define SYNC_H_

// #################################################################################################
// INCLUDES

//#include <avr/interrupt.h>
#include <stdint.h>


/**
 *  @defgroup sync Synchronisation
 *
 *  @brief generate signal for synchronisation.
 *
 *  @author Tobias Finke tofiit00@hs-esslingen.de
 *  @{
 */

// #################################################################################################
// PUBLIC DEFINES

// #################################################################################################
// PUBLIC VARIABLES

extern volatile uint8_t sync_interrupt_flag;	//!< this flag is set in the interrupt-routine
extern volatile uint8_t sync_interrupt_enabled;	//!< is the interrupt enabled


// #################################################################################################
// PUBLIC METHOD-DEFINITIONS

/**
 * @brief init the interrupt
 */
void sync_init();

/**
 * @brief enable the sync interrupt
 */
void enable_sync_interrupt();

/**
 * @brief disable the sync interrupt
 */
void disable_sync_interrupt();

/**
 * @brief Check if we got a sync signal for the Synchronisation
 * @return we got a sync signal
 */
uint8_t sync_is_active();

/**
 * @}
 */

#endif /* SYNC_H_ */
