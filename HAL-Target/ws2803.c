/*
 * ws2803.c
 *
 *  Created on: 31.03.2014
 *      Author: netzwerg
 */
#include "ws2803.h"
#include "../Application/sync.h"

/**
 *  @addtogroup ws2803
 *  @{
 */


void ws2803_init(void) {
  DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);

  // SPI @ FCK/2 -> 4MHz
  SPCR = (1<<SPE)|(1<<MSTR);
  SPSR = (1<<SPI2X);

  //send dummy data
  SPDR = 0x00;

  //SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

uint8_t ws2803_send(char cData) {

	//if(!sync_interrupt_flag){
		// Wait for old transmission complete
		while(!(SPSR & (1<<SPIF)));

		// Start transmission
		SPDR = cData;

		// Wait for transmission complete
		//while(!(SPSR & (1<<SPIF)));

		// return is not used, because WS2803 does't send data.
		return SPDR;
	//}else{
		//return 0;
	//}
}

/**@}*/
