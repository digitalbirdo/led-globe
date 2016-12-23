/**************************************************************
*
*   Studienarbeit:  LED-Globe
*   Autoren:        Tobias Finke, Clemens Weissenberg
*
*   Erstellt am:    10.05.2014
*   Datei:          pacman_field.c
*
***************************************************************/
#ifdef SWITCH_PACMAN
#include "pacman_field.h"

/**
 *  @addtogroup mode_pacman
 *  @{
 */


//#################################################################################################
// PRIVATE DEFINES

#define FIELD_BYTES_PER_COL 6 			//!< A constant that defines field bytes per col.
#define FOOD_BYTES_PER_COL 4			//!< A constant that defines food bytes per col.
#define FOOD_BMP_INIT_BYTES_PER_COL 2	//!< A constant that defines bytes per col in the initialization food bitmap.


//#################################################################################################
// PRIVATE VARIABLES

const uint8_t pacman_field_bmp[] PROGMEM = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, //1. & 25
	0xC0, 0x00, 0x00, 0x00, 0x00, 0xF0, //2. & 18.
	0xC1, 0xFF, 0x83, 0xFF, 0xE0, 0xF0, //3. & 19.
	0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, //4. & 24.
	0xC1, 0xFF, 0x83, 0xC1, 0xFF, 0xFF, //5.
	0xC0, 0x00, 0x03, 0xC0, 0x00, 0xF0, //6. & 22.
	0xFF, 0xFF, 0x83, 0xFF, 0xE0, 0xF0, //7. & 8.
	0xFF, 0xFF, 0x83, 0xC0, 0x00, 0x00, //9.
	0xFF, 0xFF, 0x83, 0xC1, 0xFC, 0x03, //10. & 11
	0x00, 0x00, 0x00, 0x01, 0xE0, 0x00, //12.
	0xFF, 0xFF, 0x83, 0xC1, 0xFF, 0xFF, //13. & 14 & 16 & 17
	0xFF, 0xFF, 0x83, 0xC0, 0x00, 0x00, //15.
	0xC0, 0x07, 0x80, 0x00, 0x00, 0x00, //20.
	0xFF, 0x07, 0x83, 0xC1, 0xFF, 0xFF, //21.
	0xC1, 0xFF, 0xFF, 0xFF, 0xE0, 0xF0 //23.
};

uint8_t pacman_food_bmp_tmp[] = {
	0xFF, 0xF3, 0xFF, 0xC0,

	0x84, 0x12, 0x08, 0x40,
	0x84, 0x12, 0x08, 0x40,
	0x84, 0x12, 0x08, 0x40,

	0xFF, 0xFF, 0xFF, 0xFF,
	
	0x84, 0x12, 0x08, 0x40,
	0x84, 0x12, 0x08, 0x40,

	0xFC, 0xF3, 0xCF, 0xC0,

	0x04, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x08, 0x00,
	0x04, 0x00, 0x08, 0x00,

	0xFF, 0xF3, 0xFF, 0xC0,
	
	0x84, 0x12, 0x08, 0x40,
	0x84, 0x12, 0x08, 0x40,
	
	0xE7, 0xFF, 0xF9, 0xC0,
	
	0x24, 0x80, 0x49, 0x00,
	0x24, 0x80, 0x49, 0x00,
	
	0xFC, 0xF3, 0xCF, 0xC0,
	
	0x80, 0x12, 0x00, 0x40,
	0x80, 0x12, 0x00, 0x40,

	0xFF, 0xFF, 0xFF, 0xC0
};


const uint8_t pacman_food_bmp_init[] PROGMEM = {
	0xFF, 0xF3, //1. & 7
	0x84, 0x12, //2. & 8
	0xFF, 0xFF, //3. & 13
	0x84, 0x80, //4.
	0xFC, 0xF3, //5. & 11
	0x04, 0x00, //6.
	0xE7, 0xFF, //9.
	0x24, 0x80, //10.
	0x80, 0x12 //12.
};

//#################################################################################################
// PRIVATE METHOD-DEFINITIONS

/**
 * @brief	Checks if is food at certain position of initialization bitmap.
 *
 * @param	x	The uint8_t to process.
 * @param	y	The uint8_t to process.
 *
 * @return	0x01=food;0x00=no food.
 */
uint8_t is_food_bmp_init_at(uint8_t x, uint8_t y);

/**
 * @brief	Gets food bit.
 *
 * @param	x	x-coordinate.
 * @param	y	y-coordinate.
 *
 * @return	The food bit.
 */
uint8_t get_food_bit(uint8_t x,uint8_t y);

/**
 * @brief	Gets food at certain position of initialization bitmap.
 *
 * @param	x	x-coordinate of food.
 * @param	y	y-coordinate of food.
 *
 * @return	The food bit.
 */
uint8_t get_food_bmp_init_bit(uint8_t x,uint8_t y);

/**
 * @brief	read out one bit of the pacman_field.
 *
 * @param	x	x-coordinate of bit.
 * @param	y	y-coordinate of bit.
 *
 * @return	The field bit.
 */
uint8_t get_field_bit(uint8_t x,uint8_t y);

/**
 * @}
 */


// #################################################################################################
// PUBLIC METHODS


uint8_t is_food_at(uint8_t x, uint8_t y) //0x01 normal food || 0x02 special food
{
	uint8_t x_tmp, y_tmp;
	if(x >= PACMAN_FIELD_WIDTH || y >= PACMAN_FIELD_HEIGHT)
	{
		return 0;
	}
	if(0 == ((x-4)%3) && 0 == ((y-4)%3))
	{
		x_tmp = (x-4)/3;
		y_tmp = (y-4)/3;

		
		if(x_tmp >= PACMAN_FOOD_FIELD_WIDTH || y_tmp >= PACMAN_FOOD_FIELD_HEIGHT)
		{
			return 0;
		}

		//specifal food!
		//normal food
		if(get_food_bit(x_tmp, y_tmp))
		{
			if((2 == y_tmp || 22 == y_tmp) && (0 == x_tmp || 25 == x_tmp))
			{
				return 0x02;
			}
			return 0x01;
		}
	}
	return 0;
}

void init_food()
{
	uint8_t x, y, tmp;
	for(y=0;y<PACMAN_FOOD_FIELD_HEIGHT;y++)
	{
		for(x=0;x<PACMAN_FOOD_FIELD_WIDTH;x=x+8)
		{
			pacman_food_bmp_tmp[y*FOOD_BYTES_PER_COL+(x/8)] = 0x00;
		}
	}
	for(y=0;y<PACMAN_FOOD_FIELD_HEIGHT;y++)
	{
		for(x=0;x<PACMAN_FOOD_FIELD_WIDTH;x++)
		{
			if(is_food_bmp_init_at(x,y))
			{
				tmp = pacman_food_bmp_tmp[y*FOOD_BYTES_PER_COL+(x/8)] | (0x01<< (7-(x%8)));
				pacman_food_bmp_tmp[y*FOOD_BYTES_PER_COL+(x/8)] = tmp;
			}
		}
	}
}

void delete_food_at(uint8_t x, uint8_t y)
{
	uint8_t x_tmp, y_tmp;

	if(x >= PACMAN_FIELD_WIDTH || y >= PACMAN_FIELD_HEIGHT)
	{
		return;
	}
	x_tmp = (x-4)/3;
	y_tmp = (y-4)/3;
	pacman_food_bmp_tmp[y_tmp*FOOD_BYTES_PER_COL+(x_tmp/8)] = pacman_food_bmp_tmp[y_tmp*FOOD_BYTES_PER_COL+(x_tmp/8)] &  (~(0x01<< (7-((x_tmp)%8)) ));
}

uint8_t is_all_food_gone ()
{
	uint8_t x,y;
	for(y=0;y<PACMAN_FOOD_FIELD_HEIGHT;y++)
	{
		//check one byte at once therefore x is increased with stepsize 8
		for(x=0;x<PACMAN_FOOD_FIELD_WIDTH;x=x+8)
		{
			if(pacman_food_bmp_tmp[y*FOOD_BYTES_PER_COL+(x/8)])
			{
				return 0x00;
			}
		}
	}
	return 0x01;
}

uint8_t is_wall_at(uint8_t x, uint8_t y)
{
	uint8_t x_tmp;
	//return if its out of range
	if(x >= PACMAN_FIELD_WIDTH || y >= PACMAN_FIELD_HEIGHT)
	{
		return 0x00;
	}
	//mirror field
	if(x <= (PACMAN_FIELD_WIDTH/2))
	{
		x_tmp = x;
	}
	else
	{
		x_tmp = (PACMAN_FIELD_WIDTH-1)-x;
	}
	//use lookup table for
	switch (y)
	{
	case 0:
	case 1:
	case 91:
	case 92:
			return get_field_bit(x_tmp,0);
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
			return get_field_bit(x_tmp,1);
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 64:
	case 65:
	case 66:
	case 67:
			return get_field_bit(x_tmp,2);
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 86:
	case 87:
	case 88:
	case 89:
	case 90:
			return get_field_bit(x_tmp,3);
	case 19:
	case 20:
	case 21:
	case 22:
			return get_field_bit(x_tmp,4);
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 77:
	case 78:
	case 79:
	case 80:
	case 81:
			return get_field_bit(x_tmp,5);
	case 28:
	case 29:
	case 30:
	case 31:
			return get_field_bit(x_tmp,6);
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
			return get_field_bit(x_tmp,7);
	case 37:
	case 38:
	case 39:
	case 40:
		{
			//cage
			if(x_tmp>=38/* && x_tmp<=45*/)//is not needed when field is mirrored
			{
				return 0x02;
			}
			else
			{
				return get_field_bit(x_tmp,8);
			}
			break;
		}
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
		{
			//cage
			if(x_tmp>=35/* && x_tmp<=48*/)//is not needed when field is mirrored
			{
				return 0x02;
			}
			else
			{
				return get_field_bit(x_tmp,9);
			}
			break;
		}
	case 46:
	case 47:
	case 48:
	case 49:
	case 55:
	case 56:
	case 57:
	case 58:
			return get_field_bit(x_tmp,10);
	case 50:
	case 51:
	case 52:
	case 53:
	case 54:
			return get_field_bit(x_tmp,11);
	case 68:
	case 69:
	case 70:
	case 71:
	case 72:
			return get_field_bit(x_tmp,12);
	case 73:
	case 74:
	case 75:
	case 76:
			return get_field_bit(x_tmp,13);
	case 82:
	case 83:
	case 84:
	case 85:
			return get_field_bit(x_tmp,14);
	default:
		break;
	}
	return 0x00;
}


//#################################################################################################
// PRIVATE METHODS

uint8_t get_food_bmp_init_bit(uint8_t x,uint8_t y){
#ifdef AVR
	return (pgm_read_byte(&pacman_food_bmp_init[y*FOOD_BMP_INIT_BYTES_PER_COL+(x/8)]) &   (1<< (7-((x)%8))));
#else
	return (pacman_food_bmp_init[y*FOOD_BMP_INIT_BYTES_PER_COL+(x/8)] &   (1<< (7-((x)%8)) ));
#endif
}

uint8_t is_food_bmp_init_at(uint8_t x, uint8_t y)
{
	if(x>(PACMAN_FOOD_FIELD_WIDTH/2))
	{
		x = (PACMAN_FOOD_FIELD_WIDTH-1)-x;
	}

	//look up
	switch (y)
	{
	case 0:
	case 19:
		return get_food_bmp_init_bit(x,0);
	case 1:
	case 2:
	case 3:
	case 20:
	case 21:
		return get_food_bmp_init_bit(x,1);
	case 4:
	case 28:
		return get_food_bmp_init_bit(x,2);
	case 5:
	case 6:
		return get_food_bmp_init_bit(x,3);
	case 7:
	case 25:
		return get_food_bmp_init_bit(x,4);
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
		return get_food_bmp_init_bit(x,5);
	case 22:
		return get_food_bmp_init_bit(x,6);
	case 23:
	case 24:
		return get_food_bmp_init_bit(x,7);
	case 26:
	case 27:
		return get_food_bmp_init_bit(x,8);
	default: break;
	}
	return 0;
}

uint8_t get_field_bit(uint8_t x,uint8_t y){
#ifdef AVR
	if (pgm_read_byte(&pacman_field_bmp[y*FIELD_BYTES_PER_COL+(x/8)]) &   (1<< (7-((x)%8))))
#else
	if (pacman_field_bmp[y*FIELD_BYTES_PER_COL+(x/8)] &   (1<< (7-((x)%8)) ))
#endif
	{
		return 0x01;
	}
	return 0x00;
}

uint8_t get_food_bit(uint8_t x,uint8_t y){
	if (pacman_food_bmp_tmp[y*FOOD_BYTES_PER_COL+(x/8)] &   (0x01<< (7-((x)%8)) ))
	{
		return 0x01;
	}
	return 0;
}
#endif

