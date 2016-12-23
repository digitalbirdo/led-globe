/*
 * btm222.h
 *
 *  Created on: 02.04.2014
 *      Author: netzwerg
 */

#ifndef BTM222_H_
#define BTM222_H_


#include <avr/io.h>

/**
 *  @defgroup btm222 BTM222 Bluetooth-Module
 *  @brief Includes the API for the BTM222 Bluetooth Module.
 *
 *  @author Tobias Finke tofiit00@hs-esslingen.de
 */

/**@{*/

#if defined(__AVR_ATTmega128__)
	#define BTM222_PIN   PINB7 	//!< PIN  connected with reset-pin of BTM222
	#define BTM222_PORT  PINB 	//!< PORT connected with BTM222
	#define BTM222_DDR   DDRB	//!< DDR  connected with BTM222
#elif defined(__AVR_ATmega88P__)|defined(__AVR_ATmega328P__)
	#define BTM222_PIN   PINB7 	//!< PIN  connected with reset-pin of BTM222
	#define BTM222_PORT  PINB 	//!< PORT connected with BTM222
	#define BTM222_DDR   DDRB 	//!< DDR  connected with BTM222
#endif

/**
 * Initialize the BTM222
 */
void btm222_init();

/**@}*/

#endif /* BTM222_H_ */
