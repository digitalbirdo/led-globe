// #################################################################################################
// INCLUDES


#include "world.h"
#include "world_bmp.h"
#include "testpattern.bmp.h"
#include "../display.h"
#include  "modes.h"

#ifdef AVR
#include <avr/pgmspace.h>
#endif

/**
 *  @addtogroup world Mode: World
 *  @{
 */


// #################################################################################################
// PRIVATE DEFINES

#define BMP_WIDTH 80 					//!< width of the world-bitmap
#define BMP_HEIGHT NUM_LEDS_PER_ROW		//!< height of the world-bitmap
#define BMP_BYTES_PER_COL (BMP_WIDTH/8)	//!< number of bytes used per column


// #################################################################################################
// PRIVATE VARIABLES

// #################################################################################################
// PRIVATE METHOD-DEFINITIONS

/**
 * get a pixel of worldmap
 * @param x X-Coordinate of the pixel
 * @param y Y-Corordinate of the pixel
 * @return value of the pixel
 */
uint8_t get_bmp_bit(uint8_t x,uint8_t y);


/**
 * @}
 */



// #################################################################################################
// PUBLIC METHODS

void mode_world_map(uint8_t index){
	index=num_rows-index;
	uint8_t i;
	//if(index<CGOL_WIDTH_MAX){
		for(i=0;i<BMP_HEIGHT;i++){
			if(get_bmp_bit(BMP_WIDTH-index,i)){
				leds[i].r=0;
				leds[i].g=128;
				leds[i].b=0;
			}else{
				leds[i].r=0;
				leds[i].g=0;
				leds[i].b=0;
			}

		}
	//}
		display_set_row(leds);
}

// #################################################################################################
// PRIVATE METHODS

uint8_t get_bmp_bit(uint8_t x,uint8_t y){
#ifdef AVR
	return (pgm_read_byte(&world_bmp[y*BMP_BYTES_PER_COL+(x/8)]) &   (1<< (7-((x)%8))));
#else
	return (world_bmp[y*BMP_BYTES_PER_COL+(x/8)] &   (1<< (7-((x)%8)) ));
#endif
}

