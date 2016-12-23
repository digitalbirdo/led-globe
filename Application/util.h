#ifndef UTIL_H_
#define UTIL_H_

// #################################################################################################
// INCLUDES

#include <stdint.h>

/**
 *  @defgroup util Util
 *  @brief contains some usefull funktions and often used structs
 *
 *  @author Tobias Finke info@digitalbird.de
 *  @{
 */

//#################################################################################################
// PUBLIC DEFINES

//#################################################################################################
// PUBLIC VARIABLES

/**
 * struct for storing an RGB-value
 */
typedef struct cRGB {
	uint8_t r;	//!< value of red   between 0-255 in the rgb-colorspace
	uint8_t g;	//!< value of green between 0-255 in the rgb-colorspace
	uint8_t b;	//!< value of blue  between 0-255 in the rgb-colorspace
} RGB;

/**
 * some predefined colors
 */
typedef enum colors{
	LIGHTRED,      //!< LIGHTRED
	LIGHTGREEN,    //!< LIGHTGREEN
	LIGHTBLUE,     //!< LIGHTBLUE
	LIGHTYELLOW,   //!< LIGHTYELLOW
	LIGHTTURQUOISE,//!< LIGHTTURQUOISE
	LIGHTPURPLE,   //!< LIGHTPURPLE
	RED,           //!< RED
	GREEN,         //!< GREEN
	BLUE,          //!< BLUE
	YELLOW,        //!< YELLOW
	TURQUOISE,     //!< TURQUOISE
	PURPLE,        //!< PURPLE
	WHITE,         //!< WHITE
	GREY,          //!< GREY
	BLACK,         //!< BLACK
	ORANGE         //!< ORANGE
}Color;

RGB get_color(Color color); //!< Beschreibung fuer die Variable


//#################################################################################################
// PUBLIC METHOD-DEFINITIONS

/**
* @brief Convert HSV-Color to the corresponding RGB-Value
* HSV-to-RGB-Converter
* http://www.mikrocontroller.net/topic/54561 (Beitrag von Benedikt K.)
* http://www.mikrocontroller.net/attachment/highlight/18560
*
*
* @param h Hue
* @param s Saturation
* @param v Value
* @param red computet red-value 0-255
* @param green computed green-value 0-255
* @param blue computed blue-value 0-255
*
* @note uses an 8-bit resolution
* @todo diesen punkt im bericht nŠher erklŠren
*/
void hsv_to_rgb (uint8_t h, uint8_t s, uint8_t v,uint8_t * red, uint8_t * green, uint8_t * blue);

/**
 * @}
 */

#endif /* UTIL_H_ */
