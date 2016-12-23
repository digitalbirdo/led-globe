/*
 * ws2803.h
 *
 *  Created on: 31.03.2014
 *      Author: netzwerg
 */

#ifndef WS2803_H_
#define WS2803_H_

#include <avr/io.h>

/**
 *  @defgroup ws2803 WS2803 PWM-Module
 *  @brief This library communicates with the WS2803 PWM-Modules.
 *
 *  @author Tobias Finke tofiit00@hs-esslingen.de
 *  @{
 */

#if defined(__AVR_ATTmega128__)
	#define DD_MOSI  PINB2	//!< PIN  connected with MOSI of WS2803
	#define DD_SCK   PINB1	//!< PIN  connected with SCH of WS2803
	#define DD_SS    PINB0	//!< PIN  connected with SS of WS2803
	#define DDR_SPI  DDRB	//!< DDR  connected with WS2803
#elif defined(__AVR_ATmega88P__)|defined(__AVR_ATmega328P__)
	#define DD_MOSI  PINB3	//!< PIN  connected with MOSI of WS2803
	#define DD_SCK   PINB5	//!< PIN  connected with SCH of WS2803
	#define DD_SS    PINB2	//!< PIN  connected with SS of WS2803
	#define DDR_SPI  DDRB	//!< DDR  connected with WS2803
#endif

/**
 * @brief Initalize the SPI-Module
 *
 *  We also have to send a dummy-byte for setting the SPSR which is needed in ws2803_send(),
 *  because we wait there until a transmission has compleded,
 *  so we need an initial transmission
 */
void ws2803_init(void);

/**
 * @brief Sends a Byte over SPI to a connected WS2803
 *
 * We wait until the old transmission has compleded
 *
 * @param cData Byte which should be send
 * @return Byte we received over SPI (not used here, because MISO is not connected)
 */
uint8_t ws2803_send(char cData);

/**@}*/

#endif /* WS2803_H_ */
