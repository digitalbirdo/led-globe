/**************************************************************
*
*   Studienarbeit:  LED-Globe
*   Autoren:        Tobias Finke, Clemens Weissenberg
*
*   Erstellt am:    03.04.2014
*   Datei:          pong.c
*
***************************************************************/

#include "pong.h"

/**
 *  @addtogroup mode_pong
 *  @{
 */

// #################################################################################################
// PRIVATE VARIABLES

// variables display
uint8_t pong_num_frame; //!< count of frames after computation

RGB paddle_color; //!< the paddle color
RGB border_color; //!< the border color
RGB ball_color; //!< the ball color

uint8_t x_ball; //!< tx-coordinate of the ball
uint8_t x_ball_next; //!< the x-coordinate of the ball of the next step
uint8_t y_ball; //!< the y-coordinate of the ball
uint8_t y_ball_next; //!< the x-coordinate of the ball of the next step

uint8_t mov_ball_vec; //!< ball movement vector; [X][XXX][Y][YYY] first-half is x-vector and second-half is y-vector

uint8_t y_paddle; //!< y-coordinate of the paddle

uint8_t pong_game_over=1; //!< flag for gamestate

uint16_t pong_score=0; //!< current score in game

// #################################################################################################
// PRIVATE METHODS DEFINITIONS

/**
 * @brief	moves ball to the next spot in x and y-direction
 * 			
 * @return	returns gamestate
 */
uint8_t move_ball();

/**
 * @brief	moves paddle to the next spot in y-direction
 */
void move_paddle();

/**
 * @brief	checks if ball is hitting the paddle
 * 			
 * @return	game_over if ball is passing the paddle
 */
uint8_t is_ball_hitting_paddle();

/**
 * @brief	main display function
 * 			
 * @param	index	Zero-based index of the display row which will currently be displayed.
 */
void display_pong(uint8_t index);

// #################################################################################################
// PUBLIC METHODS

void pong_init()
{
	x_ball = PONG_X_BALL_START;
	x_ball_next = x_ball;
	y_ball = PONG_Y_BALL_START;
	y_ball_next = y_ball;
	mov_ball_vec = PONG_MOV_BALL_VEC_START;
	y_paddle = PONG_Y_PADDLE_START;
	pong_score=0;
	pong_num_frame=0;
	pong_game_over=0;

	ball_color = get_color(LIGHTRED);
	paddle_color = get_color(LIGHTGREEN);
	border_color = get_color(LIGHTPURPLE);
}

void mode_pong(uint8_t index)
{
	if(index==0)
	{
		pong_num_frame++;
	}
	if(!pong_game_over)
	{
		if(pong_num_frame>=PONG_FRAMES_PER_COMPUTATION)
		{
			pong_game_over=move_ball();
			pong_num_frame=0;
		}
		move_paddle();
	}
	else
	{
		if(pong_num_frame%2 == 1)
		{
			border_color = get_color(LIGHTGREEN);
			paddle_color = get_color(RED);
			ball_color = get_color(BLUE);
		}
		else
		{
			border_color = get_color(LIGHTPURPLE);
			paddle_color = get_color(LIGHTGREEN);
			ball_color = get_color(RED);
		}
		if(10==pong_num_frame)
		{
			pong_init();
		}
	}
	display_pong(index);
}

uint16_t pong_get_score()
{
	return pong_score;
}

// #################################################################################################
// PRIVATE METHODS

uint8_t move_ball()
{
	//Y-Direction
	//moves up (negative direction)
	if(mov_ball_vec & 0x08)
	{
		y_ball_next = y_ball - (mov_ball_vec & 0x07);
		//ball bumps against top border
		if(y_ball_next > y_ball || y_ball_next < PONG_TOP_BORDER)
		{
			y_ball = PONG_TOP_BORDER;
			mov_ball_vec = mov_ball_vec & 0xF7;
			border_color = get_color(LIGHTGREEN);
		}
		//doesn't bump
		else
		{
			y_ball = y_ball_next;
			border_color = get_color(LIGHTPURPLE);
		}
	}
	//moves down (positive direction)
	else
	{
		y_ball_next = y_ball + (mov_ball_vec & 0x07);
		//ball bumps against bottom border
		if(y_ball_next < y_ball || y_ball_next > PONG_BOTTOM_BORDER)
		{
			y_ball = PONG_BOTTOM_BORDER;
			mov_ball_vec = mov_ball_vec | 0x08;
			border_color = get_color(LIGHTGREEN);
		}
		//doesn't bump
		else
		{
			border_color = get_color(LIGHTPURPLE);
			y_ball = y_ball_next;
		}
	}

	//X-Direction
	//moves left (negative direction)
	if(mov_ball_vec & 0x80)
	{
		x_ball_next = x_ball - ((mov_ball_vec & 0x70) >> 4);
		//ball should bump paddle from right
		if(x_ball_next > x_ball || x_ball_next < PONG_LEFT_BORDER)
		{
			if(!is_ball_hitting_paddle())
			{
				paddle_color = get_color(RED);
				return 1;
			}
			x_ball = PONG_LEFT_BORDER+1;
			mov_ball_vec = mov_ball_vec & 0x7F;
			paddle_color = get_color(BLUE);
		}
		//doesn't bump
		else
		{
			x_ball = x_ball_next;
			paddle_color = get_color(LIGHTGREEN);
		}
	}
	//moves right (positive direction)
	else
	{
		x_ball_next = x_ball + ((mov_ball_vec & 0x70) >> 4);
		//ball should bump paddle from left
		if(x_ball_next < x_ball || x_ball_next > PONG_RIGHT_BORDER)
		{
			if(!is_ball_hitting_paddle())
			{
				paddle_color = get_color(RED);
				return 1;
			}
			x_ball = PONG_RIGHT_BORDER;
			mov_ball_vec = mov_ball_vec | 0x80;
			paddle_color = get_color(BLUE);
		}
		//doesn't bump
		else
		{
			x_ball = x_ball_next;
			paddle_color= get_color(LIGHTGREEN);
		}
	}
	return 0;
}

uint8_t is_ball_hitting_paddle()
{
	uint8_t mov_ball_vec_y, mov_ball_vec_x;
	if(y_ball_next >= y_paddle && y_ball_next < y_paddle+PONG_PADDLE_WIDTH)
	{
		pong_score++;
		//ball bounces in bottom half of paddle
		if(y_ball_next-y_paddle>(PONG_PADDLE_WIDTH/2))
		{
			mov_ball_vec_y = (y_ball_next-y_paddle) - (PONG_PADDLE_WIDTH/2);
			//paddle has two pixel in the middle
			if(PONG_PADDLE_WIDTH % 2)
			{
				mov_ball_vec_y--;
			}
			//ball moves down (positive direction)
			mov_ball_vec = mov_ball_vec & 0xF7;
		}
		else
		{
			mov_ball_vec_y = (PONG_PADDLE_WIDTH/2) - (y_ball_next-y_paddle);
			//ball moves up (negative direction)
			mov_ball_vec = mov_ball_vec | 0x08;
		}
		if(mov_ball_vec_y>PONG_BALL_MAX_SPEED_Y)
		{
			mov_ball_vec_y = PONG_BALL_MAX_SPEED_Y;
		}
		//set y_speed of ball to new value
		mov_ball_vec = (mov_ball_vec & 0xF8) | mov_ball_vec_y;

		//increase x_speed
		mov_ball_vec_x = (mov_ball_vec & 0x70) >> 4;
		mov_ball_vec_x++;
		if(mov_ball_vec_x>PONG_BALL_MAX_SPEED_X)
		{
			mov_ball_vec_x = PONG_BALL_MAX_SPEED_X;
		}
		mov_ball_vec = (mov_ball_vec & 0x8F) | (mov_ball_vec_x << 4);
		return 1;
	}
	return 0;
}

void move_paddle()
{
	uint8_t tmp;
	//paddle moves down (negative direction)
	if(is_button_pressed(UP))
	{
		tmp = y_paddle - PONG_PADDLE_STEP;
		//paddle bumps against top border
		if(tmp < PONG_TOP_BORDER || tmp > y_paddle)
		{
			y_paddle = PONG_TOP_BORDER;
		}
		//paddle doesn't bump
		else
		{
			y_paddle = tmp;
		}
	}
	if(is_button_pressed(DOWN))
	{
		tmp = y_paddle + PONG_PADDLE_STEP + PONG_PADDLE_WIDTH;
		//paddle bumps against top border
		if(tmp > PONG_BOTTOM_BORDER || tmp < y_paddle)
		{
			y_paddle = PONG_BOTTOM_BORDER-PONG_PADDLE_WIDTH+1;
		}
		//paddle doesn't bump
		else
		{
			y_paddle = tmp - PONG_PADDLE_WIDTH;
		}
	}
}

void display_pong(uint8_t index)
{
	uint8_t i;
	for(i=0; i<NUM_LEDS_PER_ROW; i++)
	{
		if(i==PONG_TOP_BORDER || i==PONG_BOTTOM_BORDER){
			leds[i] = border_color;
		}
		else
		{
			leds[i] = get_color(BLACK);
		}
	}
	
	//display score
	write_int_to_led(pong_score, (PONG_X_WIDTH_FIELD/8), (PONG_Y_WIDTH_FIELD/2)-(FONT_LETTER_HEIGHT/2), paddle_color, index);

	//ball is overlaying paddle --> show paddle first
	//display paddle
	if(0 == index)
	{
		for(i=y_paddle;i<y_paddle+PONG_PADDLE_WIDTH;i++)
		{
			leds[i] = paddle_color;
		}
	}
	//display ball
	if(index == x_ball)
	{
		leds[y_ball] = ball_color;
	}
	display_set_row(leds);
}

/**
 * @}
 * End of doc-section
 */


