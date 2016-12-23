
#include "../display.h"
#include "modes.h"
#include "conway.h"
#include "../debug.h"
#include "../font.h"

/**
 *  @addtogroup mode_conway
 *  @{
 */

// #################################################################################################
// PRIVATE DEFINES

#define CGOL_HEIGHT NUM_LEDS_PER_ROW 	//!< height of the GOL-field
#define CGOL_WIDTH_MAX 100				//!< maximum width of the GOL-field
#define CGOL_WIDTH num_rows				//!< current width of the GOL-field

#define DEBOUNCER 6						//!< Split the computation of a new generation into multiple peaces, which each computed in one frame
#define LEDS_TO_COMPUTE (NUM_LEDS_PER_ROW/DEBOUNCER)	//!< Number of LEDs we have to compute per frame

/**
 * @brief  Set bit at x,y in a
 * @param a pointer of the array
 * @param x x-coordinate of the bit
 * @param y y-coordinate of the bit
 */
#define SETBIT(a,x,y) ((a)[((x)/8)*CGOL_WIDTH_MAX+y] |=  (1<< ((x)%8) ) )

/**
 * @brief  Clear bit in the array
 * @param a pointer of the array
 * @param x x-coordinate of the bit
 * @param y y-coordinate of the bit
 */
#define CLRBIT(a,x,y) ((a)[((x)/8)*CGOL_WIDTH_MAX+y] &= ~(1<< ((x)%8) ) )

/**
 * @brief  Check bit in the array
 * @param a pointer of the array
 * @param x x-coordinate of the bit
 * @param y y-coordinate of the bit
 */
#define TSTBIT(a,x,y) ((a)[((x)/8)*CGOL_WIDTH_MAX+y] &   (1<< ((x)%8) ) )


// #################################################################################################
// PRIVATE VARIABLES

uint8_t gen0[CGOL_WIDTH_MAX/8][CGOL_HEIGHT]; 	//!< Bit-Array which holds information about a generation
uint8_t gen1[CGOL_WIDTH_MAX/8][CGOL_HEIGHT]; 	//!< Bit-Array which holds information about a generation

uint8_t * current_generation; 					//!< pointer to the current generation
uint8_t * next_generation;						//!< pointer to the next generation
uint8_t * tmp_ptr_generation;					//!< pointer which is needed for swapping the generations

uint8_t initialised=0; 							//!< indicates if Connway is initialized
uint32_t num_checks=0; 							//!< for counting the bit-checks which are done in the calculation (for performance optimizations)

uint8_t debouncer=0;


// #################################################################################################
// PRIVATE METHOD-DEFINITIONS

/**
 * Check bit in the array
 * @param array pointer of the array
 * @param x x-coordinate of the bit
 * @param y y-coordinate of the bit
 * @return 1 = bit is set  / 0 = bit is not set
 */
uint8_t get_bit(uint8_t *array,uint8_t x, uint8_t y);


/**
 * Set bit at x,y in a
 * @param array pointer of the array
 * @param x x-coordinate of the bit
 * @param y y-coordinate of the bit
 */
void set_bit(uint8_t *array,uint8_t x, uint8_t y);


/**
 * Clear bit in the array
 * @param array pointer of the array
 * @param x x-coordinate of the bit
 * @param y y-coordinate of the bit
 */
void clear_bit(uint8_t *array,uint8_t x, uint8_t y);

uint8_t check_pixel(uint8_t x, uint8_t y);

/**
 * @}
 */


// #################################################################################################
// PUBLIC METHODS

void reset_cgol(){
	initialised=0;
}

void init_cgol(){
	uint8_t x,y;

	// point the Generation-Pointers an allocated Array
	current_generation=&gen0[0][0];
	next_generation=&gen1[0][0];

	// Clear the arrays completely
	for(x=0;x<CGOL_WIDTH_MAX;x++){
		for (y=0; y < CGOL_HEIGHT; y++) {
			CLRBIT(current_generation,x,y);
			CLRBIT(next_generation,x,y);
		}
	}

	/* This pattern is called glider.
	 * It travels in a direction.
	 *
	 *   1 2 3 4 x
	 * 1
	 * 2   #
	 * 3     #
	 * 4 # # #
	 * 5
	 * y
	 *
	 */
	SETBIT(current_generation,3,2);
	SETBIT(current_generation,4,3);
	SETBIT(current_generation,4,4);
	SETBIT(current_generation,3,4);
	SETBIT(current_generation,2,4);


	/* This pattern expands really strong.
	 *
	 *    20 21 22
	 * 15    #  #
	 * 16 #  #
	 * 17    #
	 * 18
	 */
	SETBIT(current_generation,40,26);
	SETBIT(current_generation,41,25);
	SETBIT(current_generation,41,26);
	SETBIT(current_generation,41,27);
	SETBIT(current_generation,42,25);

	initialised=1;
}


void mode_game_of_life(uint8_t index){
	uint8_t x,y,i;
	uint8_t fence;

	if(index==0 && !initialised){
		init_cgol();
	}


	if(index==0){									// Start of a new Frame
		//printf("num checks= %u\n",num_checks);
		num_checks=0;
		debouncer++;
		if(debouncer==DEBOUNCER){					// We have computed everything and can mark the next generation as current generation
			debouncer=0;
			tmp_ptr_generation=current_generation;
			current_generation=next_generation;
			next_generation=tmp_ptr_generation;
		}
	}


	fence=0;
	if(index>=1){
		if(debouncer!=0){
			fence=1;
		}else if(debouncer==(DEBOUNCER-1)){
			fence=-1;
		}else{
			fence=0;
		}
		for (y=fence+(LEDS_TO_COMPUTE*(debouncer-1)); y < debouncer*LEDS_TO_COMPUTE+fence; y++) {
			if(check_pixel(index,y)){
				SETBIT(next_generation,index,y);
			}else{
				CLRBIT(next_generation,index,y);
			}
		}
	}

	// set the pixels of the current generaton
	for(i=0;i<CGOL_HEIGHT;i++){
		if(TSTBIT(current_generation,index,i)){
			leds[i].r=0;
			leds[i].g=128;
			leds[i].b=0;
		}else{
			leds[i].r=0;
			leds[i].g=0;
			leds[i].b=0;
		}
	}

	// display the leds
	display_set_row(leds);
}


// #################################################################################################
// PRIVATE METHODS

uint8_t get_bit(uint8_t *array,uint8_t x, uint8_t y){
	uint8_t byte_pos_x=x/8;
	uint8_t byte_pos_y=y;
	return array[byte_pos_x*CGOL_WIDTH_MAX+byte_pos_y] & (1<<(x%8));
}

void set_bit(uint8_t *array,uint8_t x, uint8_t y){
	array[(x/8)*CGOL_WIDTH_MAX+y]|= (1<<(x%8));
}

void clear_bit(uint8_t *array,uint8_t x, uint8_t y){
	array[(x/8)*CGOL_WIDTH_MAX+y]&= ~(1<<(x%8));
}

uint8_t check_pixel(uint8_t x, uint8_t y){
	uint8_t num=0;
	uint8_t * array=current_generation;
	uint8_t current=get_bit(current_generation,x  ,y);
	num_checks++;

	if(TSTBIT(array,x-1,y-1))num++;
	if(TSTBIT(array,x  ,y-1))num++;
	if(TSTBIT(array,x+1,y-1))num++;

	if(TSTBIT(array,x-1,y))num++;
	if(TSTBIT(array,x+1,y))num++;

	if(TSTBIT(array,x-1,y+1))num++;
	if(TSTBIT(array,x  ,y+1))num++;
	if(TSTBIT(array,x+1,y+1))num++;

	if(num!=0){
		//printf("x%i y%i num%i\n",x,y,num);
	}

	if(current&&num<2){
		return 0;
	}else if(current&&num>3){
		return 0;
	}else if(current){
			return 1;
	}else if(num==3){
		return 1;
	}else{
		return 0;
	}
}










