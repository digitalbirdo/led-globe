
// #################################################################################################
// INCLUDES

#include "util.h"

/**
 *  @addtogroup util
 *  @{
 */

// #################################################################################################
// PRIVATE DEFINES

// #################################################################################################
// PRIVATE VARIABLES

// #################################################################################################
// PRIVATE METHOD-DEFINITIONS

/**
 * @}
 */


// #################################################################################################
// PUBLIC METHODS

RGB get_color(Color color)
{
	RGB tmp_color;

	tmp_color.r=0;
	tmp_color.g=0;
	tmp_color.b=0;

	switch (color)
	{
	case LIGHTRED:
		{
			tmp_color.r = 128;
			break;
		}
	case LIGHTGREEN:
		{
			tmp_color.g = 128;
			break;
		}
	case LIGHTBLUE:
		{
			tmp_color.b = 128;
			break;
		}
	case LIGHTYELLOW:
		{
			tmp_color.r = 128;
			tmp_color.g = 128;
			break;
		}
	case LIGHTTURQUOISE:
		{
			tmp_color.g = 2;
			tmp_color.b = 2;
			break;
		}
	case LIGHTPURPLE:
		{
			tmp_color.r = 128;
			tmp_color.b = 128;
			break;
		}
	case RED:
		{
			tmp_color.r = 255;
			break;
		}
	case GREEN:
		{
			tmp_color.g = 255;
			break;
		}
	case BLUE:
		{
			tmp_color.b = 255;
			break;
		}
	case YELLOW:
		{
			tmp_color.r = 255;
			tmp_color.g = 255;
			break;
		}
	case TURQUOISE:
		{
			tmp_color.g = 255;
			tmp_color.b = 255;
			break;
		}
	case PURPLE:
		{
			tmp_color.r = 255;
			tmp_color.b = 255;
			break;
		}

	case WHITE:
		{
			tmp_color.r = 255;
			tmp_color.g = 255;
			tmp_color.b = 255;
			break;
		}
	case GREY:
		{
			tmp_color.r = 60;
			tmp_color.g = 60;
			tmp_color.b = 60;
			break;
		}
	case BLACK:
		{
			break;
		}
	case ORANGE:
		{
			tmp_color.r = 255;
			tmp_color.g = 165;
		}
	default:
		break;
	}

	return tmp_color;
}

void hsv_to_rgb (uint8_t h, uint8_t s, uint8_t v,uint8_t * red, uint8_t * green, uint8_t * blue)
{
  uint8_t r,g,b, i, f;
  uint16_t p, q, t;

  if( s == 0 )
   {  r = g = b = v;
  }
  else
  {  i=h/43;
    f=h%43;
    p = (v * (255 - s))/256;
    q = (v * ((10710 - (s * f))/42))/256;
    t = (v * ((10710 - (s * (42 - f)))/42))/256;

    switch( i )
    {  case 0:
        r = v; g = t; b = p; break;
      case 1:
        r = q; g = v; b = p; break;
      case 2:
        r = p; g = v; b = t; break;
      case 3:
        r = p; g = q; b = v; break;
      case 4:
        r = t; g = p; b = v; break;
      case 5:
         r = v; g = p; b = q; break;
    }
  }

  *red=r;
  *green=g;
  *blue=b;

}

// #################################################################################################
// PRIVATE METHODS
