/**************************************************************
*
*   Studienarbeit:  LED-Globe
*   Autoren:        Tobias Finke, Clemens Weissenberg
*
*   Erstellt am:    03.04.2014
*   Datei:          pong.c
*
***************************************************************/

#include "snake.h"

/**
 *  @addtogroup mode_pong
 *  @{
 */

// #################################################################################################
// PRIVATE VARIABLES

// game variables
uint8_t snake_num_frame; //!< count of frames after computation
uint8_t snake_game_over; //!< gamestate
uint16_t snake_score; //!< score of game

// snake specific variables
struct snake_tail_bit {
	uint8_t x_position; //!< x-position of snake part
	uint8_t y_position; //!< y-position of snake part
	struct snake_tail_bit * next; //!< pointer to the next snake part
}; //!< linked list for snake parts.

typedef struct snake_tail_bit* tail_bit;

tail_bit head=NULL; //!< pointer to the snake head
uint8_t mov_snake_vec; //!< vector for movement of the snake head
uint8_t snake_length; //!< current snake length

uint8_t head_x_next; //!< x-position of snake head at the next step
uint8_t head_y_next; //!< y-position of snake head at the next step

uint8_t food_x; //!< x-position of the food
uint8_t food_y; //!< x-position of the food

RGB snake_color; //!< color of the snake
RGB food_color; //!< color of the food

// #################################################################################################
// PRIVATE METHODS DEFINITIONS

/**
 * @brief	moves every snakebit further on
 * 			
 * @return	returns gamestate
 */
uint8_t move_snake();
/**
 * @brief	checks if the snake head hits the rest of its body
 * 			
 * @return	if snake eats itself it returns game over
 */
uint8_t is_snake_hitting_itself();
/**
 * @brief	interacts with user input
 */
void change_snake_movement();
/**
 * @brief	creates the snake on default position
 */
void create_snake();
/**
 * @brief	creates single snakebit
 *
 * @param	new_x_position	x-position of snakebit
 * @param	new_y_position	y-position of snakebit
 *
 * @return	pointer on the created snakebit
 */
tail_bit create_snake_tail_bit(uint8_t new_x_position, uint8_t new_y_position);
/**
 * @brief	creates the food bit
 */
void create_food();
/**
 * @brief	deletes snake
 *
 * @param	delete_bit	pointer to the first snakebit
 */
void delete_snake(tail_bit delete_bit);

/**
 * @brief	main display function
 * 			
 * @param	index	Zero-based index of the display row which will currently be displayed.
 */
void display_snake(uint8_t index);

// #################################################################################################
// PUBLIC METHODS

void snake_init()
{

	snake_score=0;
	snake_num_frame=0;
	snake_game_over=0;
	mov_snake_vec = 0x08;

	//srand(time(NULL));
	//srand(0);
	//setup_seed();
	delete_snake(head);
	head=NULL;
	create_snake();
	create_food();

	snake_color = get_color(RED);
	food_color = get_color(BLUE);
}


void mode_snake(uint8_t index)
{
	if(index==0)
	{
		snake_num_frame++;
	}
	if(!snake_game_over)
	{
		if(snake_num_frame>=SNAKE_FRAMES_PER_COMPUTATION)
		{
			snake_game_over = move_snake();
			snake_num_frame=0;
		}
		change_snake_movement();
	}
	else
	{
		if(10==snake_num_frame)
		{
			snake_init();
		}
	}
	display_snake(index);
}

uint16_t snake_get_score()
{
	return snake_score;
}

// #################################################################################################
// PRIVATE METHODS

uint8_t move_snake()
{
	uint8_t has_head_eaten=0;
	uint8_t x_tmp_old, y_tmp_old, x_tmp_new, y_tmp_new;
	tail_bit tmp;

	head_x_next = head->x_position;
	head_y_next = head->y_position;

	switch(mov_snake_vec & 0x0F)
	{
	//snake moves up (negative Y-Direction)
	case 0x01:
		{
			head_y_next--;
			//snake walks through top border
			if(head_y_next > head->y_position)
			{
				head_y_next = 0;
				mov_snake_vec = 0x04;

				head_x_next += (SNAKE_X_WIDTH_FIELD/2);

				if(head_x_next>=SNAKE_X_WIDTH_FIELD || head_x_next<head->x_position)
				{
					head_x_next = (head->x_position)-(SNAKE_X_WIDTH_FIELD/2);
				}
			}
			break;
		}
	//snake moves right (positive X-Direction)
	case 0x02:
		{
			head_x_next++;
			//snake walks through right border
			if(head_x_next < head->x_position || head_x_next >= SNAKE_X_WIDTH_FIELD)
			{
				head_x_next = 0;
			}
			break;
		}
	//snake moves down (positive Y-Direction)
	case 0x04:
		{
			head_y_next++;
			//snake walks through bottom border
			if(head_y_next < head->y_position || head_y_next >= SNAKE_Y_WIDTH_FIELD)
			{
				head_y_next = SNAKE_Y_WIDTH_FIELD-1;
				mov_snake_vec = 0x01;

				head_x_next += (SNAKE_X_WIDTH_FIELD/2);

				if(head_x_next>=SNAKE_X_WIDTH_FIELD || head_x_next<head->x_position)
				{
					head_x_next = (head->x_position)-(SNAKE_X_WIDTH_FIELD/2);
				}
			}
			break;
		}
	//snake moves left (negative X-Direction)
	case 0x08:
		{
			head_x_next--;
			//snake walks through left border
			if(head_x_next > head->x_position)
			{
				head_x_next = SNAKE_X_WIDTH_FIELD-1;
			}
			break;
		}
	default: break;
	}
	
	if(head_x_next == food_x && head_y_next == food_y)
	{
		has_head_eaten = 1;
	}

	//move snake
	//move head
	x_tmp_old = head->x_position;
	y_tmp_old = head->y_position;
	head->x_position = head_x_next;
	head->y_position = head_y_next;
	//move tail
	tmp = head;
	while(tmp->next != NULL)
	{
		tmp = tmp->next;
		x_tmp_new = x_tmp_old;
		y_tmp_new = y_tmp_old;

		x_tmp_old = tmp->x_position;
		y_tmp_old = tmp->y_position;
		tmp->x_position = x_tmp_new;
		tmp->y_position = y_tmp_new;
	}
	if(has_head_eaten)
	{
		snake_score++;
		if(snake_length<=SNAKE_MAX_LENGTH)
		{
			tmp->next = create_snake_tail_bit(x_tmp_old, y_tmp_old);
			snake_length++;
		}
		create_food();
	}


	if(is_snake_hitting_itself())
	{
		return 1;
	}
	return 0;
}

//snake has to be moved already
uint8_t is_snake_hitting_itself()
{
	tail_bit tmp;
	tmp = head;
	while(tmp->next != NULL)
	{
		tmp = tmp->next;
		if(tmp->x_position == head_x_next && tmp->y_position == head_y_next)
		{
			return 1;
		}
	}
	return 0;
}

void change_snake_movement()
{
	if(is_button_pressed(UP) && (mov_snake_vec & 0x0F) != 0x04)
	{
		mov_snake_vec = 0x01;
	}
	if(is_button_pressed(RIGHT) && (mov_snake_vec & 0x0F) != 0x08)
	{
		mov_snake_vec = 0x02;
	}
	if(is_button_pressed(DOWN) && (mov_snake_vec & 0x0F) != 0x01)
	{
		mov_snake_vec = 0x04;
	}
	if(is_button_pressed(LEFT) && (mov_snake_vec & 0x0F) != 0x02)
	{
		mov_snake_vec = 0x08;
	}
}

void create_snake()
{
	tail_bit tmp;
	uint8_t i;
	//delete old snake if existent
	if(head != NULL)
	{
		delete_snake(head);
		head=NULL;
	}
	//create new snake
	head = create_snake_tail_bit(SNAKE_HEAD_START_X_POSITION, SNAKE_HEAD_START_Y_POSITION);
	tmp = head;
	snake_length = SNAKE_START_LENGTH;
	for(i=1;i<snake_length; i++)
	{
		//creates snake tail in right direction --> snake head left - snake tail right --> start movement should be left
		tmp->next = create_snake_tail_bit(SNAKE_HEAD_START_X_POSITION+i, SNAKE_HEAD_START_Y_POSITION);
		tmp = tmp->next;
	}
}

tail_bit create_snake_tail_bit(uint8_t new_x_position, uint8_t new_y_position)
{
	tail_bit new_snake_tail_bit = (tail_bit) malloc(sizeof(struct snake_tail_bit));
	new_snake_tail_bit->x_position = new_x_position;
	new_snake_tail_bit->y_position = new_y_position;
	new_snake_tail_bit->next = NULL;
	return new_snake_tail_bit;
}

void create_food()
{
	tail_bit tmp;
	uint8_t is_food_at_free_place = 1, test;
	do
	{
		if(SNAKE_X_WIDTH_FIELD>0)
		{
			food_x = get_random_value(0,SNAKE_X_WIDTH_FIELD-1);
		}
		else
		{
			food_x = get_random_value(0,60);
		}

		food_y = get_random_value(SNAKE_TOP_BORDER,SNAKE_BOTTOM_BORDER);

		if(head->x_position == food_x && head->y_position == food_y)
		{
			is_food_at_free_place = 0;
		}
		tmp = head;
		while(tmp->next != NULL && is_food_at_free_place)
		{
			tmp = tmp->next;
			if(tmp->x_position == food_x && tmp->y_position == food_y)
			{
				is_food_at_free_place = 0;
			}
		}
	}
	while(!is_food_at_free_place);
}

// recursive delete function (could be problematic)
void delete_snake(tail_bit delete_bit)
{
	if(delete_bit != NULL)
	{
		if(delete_bit->next != NULL)
		{
			delete_snake(delete_bit->next);
		}
		free(delete_bit);
		delete_bit = NULL;
	}
}

void display_snake(uint8_t index)
{
	uint8_t i;
	tail_bit tmp;
	RGB black = get_color(BLACK);
	for(i=0;i<NUM_LEDS_PER_ROW; i++)
	{
		leds[i] = black;
	}
	if(head!=NULL)
	{
		// display snake_tail
		if(index == head->x_position)
		{
			leds[head->y_position] = snake_color;
		}
	
		tmp = head;
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
			if(index == tmp->x_position)
			{
				leds[tmp->y_position] = snake_color;
			}
		}
	
		//display food
		if(index == food_x)
		{
			leds[food_y] = food_color;
		}
	}
	display_set_row(leds);
}

/**
 * @}
 * End of doc-section
 */