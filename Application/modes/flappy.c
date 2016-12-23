#include "flappy.h"

/**
 *  @addtogroup mode_flappy
 *  @{
 */

// #################################################################################################
// PRIVATE VARIABLES

/**
 * @typedef	enum game_states
 *
 * @brief	Defines an alias representing the states of the game.
 */

typedef enum game_states
{
	INIT    =0x00,
	PLAYING =0x01,
	GAMEOVER=0x02,
} GameState;

// game variables
uint8_t flappy_num_frame=0; //!< count of frames after computation
GameState gamestate=INIT; //!< flag for gamestate
uint16_t flappy_score=0; //!< current score in game

// snake specific variables
struct obstacle_bar {
	uint8_t x_position; //!< distance of obstacle from left border
	uint8_t height; //!< solid blocks from top till the passage (pixels)
	uint8_t passage_width; //!< space between solid blocks
	struct obstacle_bar * next; //!< pointer to next obstacle to the right
}; //!< linked list for moving obstacles.

typedef struct obstacle_bar* obstacle;

obstacle first_obstacle=NULL; //!< pointer to the first obstalce

uint8_t bird_y_position; //!< distance of the bird from ground level
int8_t bird_mov_vec; //!< movement vector of the bird

RGB obstacle_color; //!< color of obstacles

// #################################################################################################
// PRIVATE METHODS DEFINITIONS

/**
 * @brief	moves the bird in y-direction by taking user input.
 * 			
 * @return	returns gamestate gameover if bird hits the ground
 */
GameState move_bird();

/**
 * @brief	moves every obstacle one step closer to the bird.
 * 			
 * @note	thats how the bird is moving foward
 * 			
 * @return	returns gamestate gameover if bird hits the obstacle
 */
GameState move_obstacles();

/**
 * @brief	checks if bird hits first obstacle
 * 			
 * @return	returns gamestate
 */
uint8_t is_bird_hitting_obstacle();

/**
 * @brief	moves every obstacle one step closer to the bird.
 * 			
 * @param	x_position	x-Position of the obstacle created
 * @param	height	height of obstacle, see struct at the top
 * @param	passage_width	passage width of obstacle, see struct at the top
 * 			
 * @return	returns gamestate gameover if bird hits the obstacle
 */
obstacle create_obstacle(uint8_t x_position, uint8_t height, uint8_t passage_width);

/**
 * @brief	deletes obstacle
 * 			
 * @param	obstacle_to_delete	pointer to the obstacle which shall be deleted
 */
void delete_obstacles(obstacle obstacle_to_delete);

/**
 * @brief	main display function, calling the other display functions
 * 			
 * @param	index	Zero-based index of the display row which will currently be displayed.
 */
void display_flappy(uint8_t index);

/**
 * @brief	displays bird, taking bitmap as input
 * 			
 * @param	index	Zero-based index of the display row which will currently be displayed.
 */
void display_bird(uint8_t index);

/**
 * @brief	displays all obstacles in field
 * 			
 * @param	index	Zero-based index of the display row which will currently be displayed.
 */
void display_obstacles(uint8_t index);

/**
 * @brief	displays one obstacle
 * 			
 * @param	index	Zero-based index of the display row which will currently be displayed.
 * @param	obstacle_to_display	pointer to obstacle being displayed
 */
void display_obstacle(uint8_t index, obstacle obstacle_to_display);

// #################################################################################################
// PUBLIC METHODS

void flappy_init()
{
	flappy_score=0;
	flappy_num_frame=0;
	gamestate=PLAYING;

	bird_y_position = FLAPPY_TOP_BORDER;
	bird_mov_vec = FLAPPY_BIRD_MAX_Y_UP_SPEED;

	delete_obstacles(first_obstacle);
	first_obstacle = NULL;
	first_obstacle = create_obstacle(60,
		get_random_value(0,FLAPPY_OBSTACLE_MAX_HEIGHT),
		get_random_value(FLAPPY_OBSTACLE_MIN_PASSAGE_WIDTH, FLAPPY_OBSTACLE_MAX_PASSAGE_WIDTH));

	obstacle_color = get_color(LIGHTGREEN);
}

void mode_flappy(uint8_t index)
{
	if(index==0)
	{
		flappy_num_frame++;
	}
	if(PLAYING==gamestate)
	{
		if(flappy_num_frame>=FLAPPY_FRAMES_PER_COMPUTATION)
		{
			gamestate = move_bird();
			//this if clause needs to done, otherwise the gamestate would be overwritten anyway.
			gamestate = move_obstacles() == GAMEOVER ? GAMEOVER : gamestate;
			flappy_num_frame=0;
		}
	}
	else
	{
		if(10==flappy_num_frame)
		{
			flappy_init();
		}
	}
	display_flappy(index);
}

// #################################################################################################
// PRIVATE METHODS

GameState move_bird()
{
	uint8_t bird_y_position_next;
	//change movement vector
	if(is_button_pressed(UP))
	{
		bird_mov_vec = FLAPPY_BIRD_MAX_Y_UP_SPEED;
	}
	else
	{
		bird_mov_vec--;
		//Constant is absolute value --> change sign of mov_vec
		if(bird_mov_vec * (-1) > FLAPPY_BIRD_MAX_Y_DOWN_SPEED)
		{
			bird_mov_vec = FLAPPY_BIRD_MAX_Y_DOWN_SPEED * (-1);
		}
	}

	//change bird position
	//display is wrong way round --> -mov_vec
	//uint8_t and int8_t operation, maybe mistake?
	bird_y_position_next = bird_y_position-bird_mov_vec;

	//if bird moves up
	if(bird_mov_vec>0)
	{
		//bumps against top border
		if(bird_y_position_next < FLAPPY_TOP_BORDER || bird_y_position_next > bird_y_position)
		{
			bird_y_position_next = FLAPPY_TOP_BORDER;
		}
	}
	//bumps against ground
	else
	{
		if(bird_y_position_next>FLAPPY_BOTTOM_BORDER || bird_y_position_next < bird_y_position)
		{
			return GAMEOVER;
		}
	}
	bird_y_position = bird_y_position_next;
	return PLAYING;
}

GameState move_obstacles()
{
	GameState game_state = PLAYING;
	uint8_t obstacle_x_position_tmp;
	obstacle tmp, last_obstacle;

	//next position of first obstacle (first obstacle --> nearest obstacle to bird)
	obstacle_x_position_tmp = (first_obstacle->x_position) - FLAPPY_BIRD_X_SPEED;

	//bird is flying in first obstacle
	if((FLAPPY_BIRD_X_POSITION + FLAPPY_BIRD_WIDTH_AND_HEIGHT) > obstacle_x_position_tmp && (obstacle_x_position_tmp + FLAPPY_OBSTACLE_WIDTH) > FLAPPY_BIRD_X_POSITION)
	{
		game_state = 1 == is_bird_hitting_obstacle() ? GAMEOVER : PLAYING;
	}

	//first obstacle meets left border
	if(obstacle_x_position_tmp==0 || obstacle_x_position_tmp > (first_obstacle->x_position))
	{
		tmp = first_obstacle->next;
		first_obstacle->next = NULL;
		delete_obstacles(first_obstacle);
		first_obstacle = tmp;	//next position of first obstacle (first obstacle --> nearest obstacle to bird)
		obstacle_x_position_tmp = (first_obstacle->x_position) - FLAPPY_BIRD_X_SPEED;
	}

	//move obstacles
	first_obstacle->x_position = obstacle_x_position_tmp;
	tmp = first_obstacle->next;
	last_obstacle = first_obstacle;
	while(tmp!=NULL)
	{
		tmp->x_position = (tmp->x_position) - FLAPPY_BIRD_X_SPEED;
		last_obstacle = tmp;
		tmp = tmp->next;
	}

	//create new obstacle if enough space is there
	if((last_obstacle->x_position + FLAPPY_OBSTACLE_WIDTH + FLAPPY_SPACE_BETWEEN_OBSTACLE) <= FLAPPY_X_WIDTH_FIELD)
	{
		last_obstacle->next = create_obstacle(
			(last_obstacle->x_position + FLAPPY_OBSTACLE_WIDTH + FLAPPY_SPACE_BETWEEN_OBSTACLE),
			 get_random_value(0,FLAPPY_OBSTACLE_MAX_HEIGHT),
			 get_random_value(FLAPPY_OBSTACLE_MIN_PASSAGE_WIDTH,FLAPPY_OBSTACLE_MAX_PASSAGE_WIDTH));
	}
	return game_state;
}

uint8_t is_bird_hitting_obstacle()
{
	//bird is flying to high
	//e.g. obstacle height = 20 --> max obstacle index = 19
	// bird can fly at index 20 at min!
	if(bird_y_position < FLAPPY_TOP_BORDER + (first_obstacle->height))
	{
		return 1;
	}
	//bird is flying to low
	//e.g. obstacle height = 20; passage width = 10 --> max obstacle index = 30
	// bird y position = 27; bird width and height = 3
	//bird can fly at index 27 max!
	if(bird_y_position + FLAPPY_BIRD_WIDTH_AND_HEIGHT > FLAPPY_TOP_BORDER + (first_obstacle->height) + (first_obstacle->passage_width))
	{
		return 1;
	}
	return 0;
}

obstacle create_obstacle(uint8_t x_position, uint8_t height, uint8_t passage_width)
{
	obstacle new_obstacle = (obstacle) malloc(sizeof(struct obstacle_bar));
	new_obstacle->x_position = x_position;
	new_obstacle->height = height;
	new_obstacle->passage_width = passage_width;
	new_obstacle->next = NULL;
	return new_obstacle;
}

void delete_obstacles(obstacle obstacle_to_delete)
{
	if(obstacle_to_delete != NULL)
	{
		if(obstacle_to_delete->next != NULL)
		{
			delete_obstacles(obstacle_to_delete->next);
		}
		free(obstacle_to_delete);
		obstacle_to_delete = NULL;
	}
}

void display_flappy(uint8_t index)
{
	RGB background_color, cloud_color;
	uint8_t i, cloudlevel;

#ifdef AVR
	background_color = get_color(LIGHTTURQUOISE); //ON HARDWARE
#else
	background_color = get_color(BLACK); // ON SIMULATION
#endif

	cloud_color = get_color(GREY);
	cloudlevel = (FLAPPY_BOTTOM_BORDER - 2) + get_random_value(0,4);
	for(i=0;i<NUM_LEDS_PER_ROW;i++)
	{
		if(i<cloudlevel)
		{
			leds[i] = background_color;
		}
		else
		{
			leds[i] = cloud_color;
		}
	}
	
	display_obstacles(index);
	if(FLAPPY_BIRD_X_POSITION <= index && index < FLAPPY_BIRD_X_POSITION + FLAPPY_BIRD_WIDTH_AND_HEIGHT)
	{
		display_bird(index);
	}
	display_set_row(leds);
}

void display_bird(uint8_t index)
{
	uint8_t x = index-FLAPPY_BIRD_X_POSITION, y;
	for(y=bird_y_position;y<bird_y_position+FLAPPY_BIRD_WIDTH_AND_HEIGHT;y++)
	{
		switch(x)
		{
		case 0:
			{
				switch(y-bird_y_position)
				{
				case 0: break;
				case 1: leds[y] = get_color(WHITE); break;
				case 2: leds[y] = get_color(ORANGE); break;
				default: break;
				}
				break;
			}
		case 1:
			{
				switch(y-bird_y_position)
				{
				case 0: leds[y] = get_color(YELLOW); break;
				case 1: leds[y] = get_color(YELLOW); break;
				case 2: leds[y] = get_color(ORANGE); break;
				default: break;
				}
				break;
			}
		case 2:
			{
				switch(y-bird_y_position)
				{
				case 0: leds[y] = get_color(WHITE); break;
				case 1: leds[y] = get_color(RED); break;
				case 2: break;
				default: break;
				}
				break;
			}
		default: break;
		}
	}
}

void display_obstacles(uint8_t index)
{
	obstacle tmp;
	tmp = first_obstacle;
	while(tmp!=NULL)
	{
		if(index >= (tmp->x_position) && index < (tmp->x_position) + FLAPPY_OBSTACLE_WIDTH)
		{
			display_obstacle(index, tmp);
		}
		tmp = tmp->next;
	}
}

void display_obstacle(uint8_t index, obstacle obstacle_to_display)
{
	uint8_t i, tmp;
	/* Object to display:
	*	| |
	*  |___|
	* 
	*   ___
	*  |   |
	*   | |
	*/
	if(index==(obstacle_to_display->x_position) || index==(obstacle_to_display->x_position) + (FLAPPY_OBSTACLE_WIDTH-1))
	{
		tmp = (obstacle_to_display->height) + FLAPPY_TOP_BORDER;
		for(i = tmp-1;i >= tmp-4 ;i--)
		{
			leds[i] = obstacle_color;
		}
		tmp = (obstacle_to_display->height)+(obstacle_to_display->passage_width) + FLAPPY_TOP_BORDER;
		for(i=tmp;i<tmp+4;i++)
		{
			leds[i] = obstacle_color;
		}
	}
	else
	{
		tmp = (obstacle_to_display->height) + FLAPPY_TOP_BORDER;
		for(i=0;i<tmp;i++)
		{
			leds[i] = obstacle_color;
		}
		tmp = (obstacle_to_display->height)+(obstacle_to_display->passage_width) + FLAPPY_TOP_BORDER;
		for(i=tmp;i<NUM_LEDS_PER_ROW;i++)
		{
			leds[i] = obstacle_color;
		}
	}
}

uint16_t flappy_get_score()
{
	return flappy_score;
}

/**
 * @}
 */
