/**************************************************************
*
*   Studienarbeit:  LED-Globe
*   Autoren:        Tobias Finke, Clemens Weissenberg
*
*   Erstellt am:    03.04.2014
*   Datei:          pacman.c
*
***************************************************************/
#ifdef SWITCH_PACMAN

#include "pacman.h"


/**
 *  @addtogroup mode_pacman
 *  @{
 */


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
	WIN     =0x03
} GameState;

/**
 * @typedef	enum directions
 *
 * @brief	Defines an alias representing the cardinal directions.
 * 
 * @note	Directions combined bitwise will result new directions
 * 			e.g. NORTH | EAST = NORTHEAST
 */

typedef enum directions {
	NODIRECTION=0,
	NORTH=0x01,
	EAST=0x02,
	SOUTH=0x04,
	WEST=0x08,
	NORTHEAST=0x03,
	SOUTHEAST=0x06,
	SOUTHWEST=0x0C,
	NORTHWEST=0x09
} Direction;


/**
 * @fn	Direction get_opposite_direction(Direction direction)
 *
 * @brief	Gets opposite direction.
 *
 * @param	direction	The direction.
 *
 * @return	The opposite direction.
 */
#define OPPOSITEDIRECTION(direction) (((direction << 2) | (direction >> 2)) & 0x0F)

/**
 * @struct	taker_object
 *
 * @brief	A taker object, which will represent either pacman or a ghost.
 * 			
 * @todo	[Pacman_Biting_Ghost Extension]: state_flag
 * 			in case of pacman if he eats special food time will be ticking
 * 			in case of ghost if it can be eaten or not
 */

struct taker_object {
	uint8_t x_pos;
	uint8_t y_pos;
	Direction direction;
	Direction direction_next;
	RGB color;
};

/**
 * @typedef	struct taker_object * taker
 *
 * @brief	Defines an alias representing the taker.
 */

typedef struct taker_object * taker;

taker pacman = NULL;
taker ghosts[4];

uint8_t pacman_has_eaten;

// variables
uint8_t pacman_num_frame;
GameState game_state; // 0=init; 1=playing; 2=game over
uint16_t pacman_score;

uint8_t ghost_navigation_points_x[4];
uint8_t ghost_navigation_points_y[4];

RGB background_color;
RGB wall_color;
RGB food_color;
RGB special_food_color;
RGB text_color;

void dispose_pacman();
taker create_taker(Direction direction, uint8_t x, uint8_t y, RGB color);
void init_ghosts();
void init_display();

/**
 * @fn	void pacman_init()
 *
 * @brief	Initalitation of Pacman.
 */

void pacman_init()
{
	game_state = INIT;
	dispose_pacman();

	pacman_num_frame = 0;
	pacman_score = 0;
	pacman_has_eaten = 0;

	//pacman = create_taker(WEST,28,34, get_color(YELLOW));
	pacman = create_taker(WEST,41,70, get_color(YELLOW));
	
	init_food();

	init_ghosts();

	init_display();
	game_state = PLAYING;
}

/**
 * @fn	void pacman_dispose()
 *
 * @brief	Dispose pacman and the ghosts.
 */

void dispose_pacman()
{
	uint8_t i;
	free(pacman);
	pacman = NULL;
	for(i=0;i<4;i++)
	{
		free(ghosts[i]);
		ghosts[i] = NULL;
	}
}

/**
 * @fn	taker create_taker(Direction direction, uint8_t x, uint8_t y, RGB color)
 *
 * @brief	Creates a taker, like pacman or ghost.
 *
 * @param	direction	The direction in which taker is heading.
 * @param	x		 	The x-coordinate.
 * @param	y		 	The y-coordinate.
 * @param	color	 	The displaycolor.
 *
 * @return	The new taker.
 * 			
 * @todo	[Pacman_Biting_Ghost Extension]: set default state flag
 */

taker create_taker(Direction direction, uint8_t x, uint8_t y, RGB color)
{
	taker new_taker = (taker) malloc(sizeof(struct taker_object));
	new_taker->direction = direction;
	new_taker->direction_next = direction;
	new_taker->x_pos = x;
	new_taker->y_pos = y;
	new_taker->color = color;
	return new_taker;
}

void set_random_navigation_point(uint8_t ghostnumber);

/**
 * @fn	void init_ghosts()
 *
 * @brief	Initialises the ghosts in predefined position in cage (therefore it knows about pacman_field ;-) )
 * 			and give them a random point on map to run to.
 */

void init_ghosts()
{
	ghosts[0] = create_taker(EAST, 37, 43, get_color(TURQUOISE));
	ghosts[1] = create_taker(EAST, 40, 43, get_color(PURPLE));
	ghosts[2] = create_taker(EAST, 43, 43, get_color(RED));
	ghosts[3] = create_taker(EAST, 46, 43, get_color(ORANGE));

	set_random_navigation_point(0);
	set_random_navigation_point(1);
	set_random_navigation_point(2);
	set_random_navigation_point(3);
}

/**
 * @fn	void set_random_navigation_point(uint8_t ghostnumber)
 *
 * @brief	Sets random navigation point on map for ghost to run to.
 *
 * @param	ghostnumber	The index number of ghost.
 */

void set_random_navigation_point(uint8_t ghostnumber)
{
	uint8_t x, y;
	do
	{
		x = (get_random_value(0,PACMAN_FOOD_FIELD_WIDTH-1) * 3) + 4;
		y = (get_random_value(0,PACMAN_FOOD_FIELD_HEIGHT-1) * 3) + 4; 
	}while(is_wall_at(x,y));

	ghost_navigation_points_x[ghostnumber] = x;
	ghost_navigation_points_y[ghostnumber] = y;
}

/**
 * @fn	void init_display()
 *
 * @brief	Initialises the display.
 */

void init_display()
{
	//set colors for field
	background_color = get_color(BLACK);
	wall_color = get_color(BLUE);
	food_color = get_color(WHITE);
	special_food_color = get_color(GREEN);
	text_color = get_color(RED);
}

void change_direction_of_pacman();
uint8_t is_pacman_eating();
void move_taker(taker taker);
void change_direction_of_taker(taker taker);
void compute_next_move_of_ghost(uint8_t ghostnumber);
uint8_t was_pacman_bitten();
void display_pacman(uint8_t index);

/**
 * @fn	void mode_pacman(uint8_t index)
 *
 * @brief	The main peace of the game pacman. It is were the sequence of the game is defined.
 *
 * @param	index	Zero-based index of the display row which will currently be displayed.
 * 					
 * @todo	[Pacman_Biting_Ghost Extension]: eating routine has to be changed
 */

void mode_pacman(uint8_t index)
{
	uint8_t i;

	//counts every fully displayed frame
	if(index==0)
	{
		pacman_num_frame++;
	}

	//game is in playing state
	if(PLAYING==game_state)
	{
		change_direction_of_pacman();
		if(pacman_num_frame>=PACMAN_FRAMES_PER_COMPUTATION)
		{
			// procedure for pacman
			pacman_has_eaten = is_pacman_eating();
			if(pacman_has_eaten)
			{
				game_state = is_all_food_gone() ? WIN : PLAYING;
			}
			if(WIN != game_state)
			{
				move_taker(pacman);
				change_direction_of_taker(pacman);

				//procedure for ghosts
				for(i=0;i<4;i++)
				{
					move_taker(ghosts[i]);
					compute_next_move_of_ghost(i);
					change_direction_of_taker(ghosts[i]);
				}

				game_state = was_pacman_bitten() ? GAMEOVER : PLAYING;
			}
			pacman_num_frame=0;
		}
	}

	//game is in game over or winning state
	else
	{
		if(10<=pacman_num_frame)
		{
			pacman_num_frame=0;
			pacman_init();
		}
	}
	display_pacman(index);
}

/**
 * @fn	void change_direction_of_pacman()
 *
 * @brief	Handles the Input of the user and changes direction of pacman.
 */

void change_direction_of_pacman()
{
	if(is_button_pressed(UP))
	{
		pacman->direction_next = NORTH;
	}
	if(is_button_pressed(RIGHT))
	{
		pacman->direction_next = EAST;
	}
	if(is_button_pressed(DOWN))
	{
		pacman->direction_next = SOUTH;
	}
	if(is_button_pressed(LEFT))
	{
		pacman->direction_next = WEST;
	}
}

/**
 * @fn	uint8_t is_pacman_eating()
 *
 * @brief	Checks if pacman is eating.
 *
 * @return	0x00=no food; 0x01=food; 0x02=special food.
 * 			
 * @note is using pacman_field.h
 * 		 
 * @todo	[Pacman_Biting_Ghost Extension]: when special food was eaten act!
 */

uint8_t is_pacman_eating()
{
	//food needs to temporarly stored for it can be special (0x02) or normal food (0x01)!
	uint8_t food;
	food = is_food_at(pacman->x_pos,pacman->y_pos);
	if(food)
	{
		delete_food_at(pacman->x_pos,pacman->y_pos);
		return food;
	}
	return 0;
}

/**
 * @fn	void move_taker(taker taker)
 *
 * @brief	Moves taker in current direction.
 *
 * @param	taker	The taker to be moved.
 * 					
 * @note	if takers walks out of field he will be teleported at the other side of field. (only effetcs for EAST and WEST)
 */

void move_taker(taker taker)
{
	uint8_t x_next, y_next;

	x_next = taker->x_pos;
	y_next = taker->y_pos;

	//sets next position of taker
	switch(taker->direction)
	{
	case NORTH:
		{
			if(is_wall_at(x_next,y_next-3) != 0x01)
			{
				y_next--;
			}
			break;
		}
	case EAST:
		{
			if(is_wall_at(x_next+3,y_next) != 0x01)
			{
				x_next++;
			}
			break;
		}
	case SOUTH:
		{
			if(is_wall_at(x_next,y_next+3) != 0x01)
			{
				y_next++;
			}
			break;
		}
	case WEST:
		{
			if(is_wall_at(x_next-3,y_next) != 0x01)
			{
				x_next--;
			}
			break;
		}
	default: break;
	}

	//when taker walks out of the field in the horizontal middle tunnel teleports to the opposite position
	if(x_next<=3)
	{
		x_next = (PACMAN_FIELD_WIDTH-1) - 4;
	}
	if(x_next >= (PACMAN_FIELD_WIDTH-1) - 3)
	{
		x_next = 4;
	}

	taker->x_pos = x_next;
	taker->y_pos = y_next;
}

/**
 * @fn	void change_direction_of_taker(taker taker)
 *
 * @brief	Change direction of taker.
 *
 * @param	taker	The taker.
 */

void change_direction_of_taker(taker taker)
{
	//change direction of taker if it turns round or if it is on a spot where a possible crossroad is.
	if(
		(0 == (taker->x_pos-4)%3 && 0 == (taker->y_pos-4)%3) || (taker->direction == OPPOSITEDIRECTION(taker->direction_next)))
	{
		taker->direction = taker->direction_next;
	}
}

void navigate_to_next_direction_of_ghost(uint8_t ghostnumber);

/**
 * @fn	void compute_next_move_of_ghost(uint8_t ghostnumber)
 *
 * @brief	changes the next_direction of the ghost ==> Thats where the heart of the game is!
 *
 * @param	ghostnumber	The index of the ghost.
 * 			
 * @todo	[Pacman_Biting_Ghost Extension]: handle new states
 */

void compute_next_move_of_ghost(uint8_t ghostnumber)
{
	//when ghost arrived at his navigation point get a new one
	if(ghosts[ghostnumber]->x_pos == ghost_navigation_points_x[ghostnumber] &&
		ghosts[ghostnumber]->y_pos == ghost_navigation_points_y[ghostnumber])
	{
		set_random_navigation_point(ghostnumber);
	}

	//when ghost is on possible crossroad compute next direction
	if(0 == (ghosts[ghostnumber]->x_pos-4)%3 && 0 == (ghosts[ghostnumber]->y_pos-4)%3)
	{
		navigate_to_next_direction_of_ghost(ghostnumber);
	}
}

uint8_t get_possible_directions_of_ghost(taker ghost);

/**
 * @fn	void navigate_to_next_direction_of_ghost(uint8_t ghostnumber)
 *
 * @brief	Navigate to navigationpoint by changing the next direction of.
 *
 * @param	ghostnumber	The ghostnumber.
 * 						
 * @note	This is the difficult part.
 * 			first rule: ghosts never spin round except pacman is behind them or there is no other possibility
 * 			
 * @todo	[Pacman_Biting_Ghost Extension]:
 */

void navigate_to_next_direction_of_ghost(uint8_t ghostnumber)

{
	int16_t x_diff, y_diff;
	uint8_t possible_directions;
	uint8_t navigation_direction = 0x00;

	possible_directions = get_possible_directions_of_ghost(ghosts[ghostnumber]);

	//if ghost is in dead end turn round
	if(possible_directions & 0x10)
	{
		ghosts[ghostnumber]->direction_next = (Direction) (possible_directions & 0x0F);
		return;
	}

	//when ghost is in same row or col like pacman, chase him!
	if(ghosts[ghostnumber]->x_pos == pacman->x_pos || ghosts[ghostnumber]->y_pos == pacman->y_pos)
	{
		ghost_navigation_points_x[ghostnumber] = pacman->x_pos;
		ghost_navigation_points_y[ghostnumber] = pacman->y_pos;
	}
	else
	{
		//Delete direction where ghost came from possible directions
		possible_directions = possible_directions & (~OPPOSITEDIRECTION(ghosts[ghostnumber]->direction));
	}

		
	//calculate ghost diff to navigationpoint
	x_diff = ((int16_t)ghost_navigation_points_x[ghostnumber])-((int16_t)ghosts[ghostnumber]->x_pos);
	y_diff = ((int16_t)ghost_navigation_points_y[ghostnumber])-((int16_t)ghosts[ghostnumber]->y_pos);

	//calculate navigation direction
	if(y_diff > 0)
	{
		navigation_direction = navigation_direction | SOUTH;
	}
	else if(y_diff < 0)
	{
		navigation_direction = navigation_direction | NORTH;
	}

	if(x_diff > 0)
	{
		navigation_direction = navigation_direction | EAST;
	}
	else if(x_diff < 0)
	{
		navigation_direction = navigation_direction | WEST;
	}

	//Is ghost's current direction heading to navigation point and possible?
	if((ghosts[ghostnumber]->direction & navigation_direction)
		&&
		(ghosts[ghostnumber]->direction & possible_directions))
	{
		ghosts[ghostnumber]->direction_next = ghosts[ghostnumber]->direction;
		return;
	}

	if(navigation_direction & possible_directions)
	{
		possible_directions = navigation_direction & possible_directions;
	}

	switch(possible_directions)
	{
	case NORTH:
	case EAST:
	case SOUTH:
	case WEST:
		{
			ghosts[ghostnumber]->direction_next = (Direction) possible_directions;
			return;
		}
	case NORTHEAST:
	case SOUTHEAST:
	case SOUTHWEST:
	case NORTHWEST:
		{
			ghosts[ghostnumber]->direction_next = (Direction) (possible_directions & (NORTH | SOUTH));
			return;
		}
	default:
		{
			if(possible_directions & EAST)
			{
				ghosts[ghostnumber]->direction_next = EAST;
			}
			else if(possible_directions & WEST)
			{
				ghosts[ghostnumber]->direction_next = WEST;
			}
			else if(possible_directions & NORTH)
			{
				ghosts[ghostnumber]->direction_next = NORTH;
			}
			else if(possible_directions & SOUTH)
			{
				ghosts[ghostnumber]->direction_next = SOUTH;
			}
			return;
		}
	}
}

/**
 * @fn	uint8_t get_possible_directions_of_ghost(taker ghost)
 *
 * @brief	computes all possible direction in which ghost can walk without bumping
 *
 * @param	ghost	The ghost.
 *
 * @return	The possible directions of ghost and in addition to that checks if deadend
 */

uint8_t get_possible_directions_of_ghost(taker ghost)
{
	uint8_t possible_directions = NODIRECTION, direction_counter=0;
	//check NORTH direction
	if(is_wall_at(ghost->x_pos, (ghost->y_pos-3)) != 0x01)
	{
		possible_directions = possible_directions | NORTH;
		direction_counter++;
	}
	//check EAST direction
	if(is_wall_at((ghost->x_pos+3), ghost->y_pos) != 0x01)
	{
		possible_directions = possible_directions | EAST;
		direction_counter++;
	}
	//check SOUTH direction
	if(is_wall_at(ghost->x_pos, (ghost->y_pos+3)) != 0x01)
	{
		possible_directions = possible_directions | SOUTH;
		direction_counter++;
	}
	//check WEST direction
	if(is_wall_at((ghost->x_pos-3), ghost->y_pos) != 0x01)
	{
		possible_directions = possible_directions | WEST;
		direction_counter++;
	}
	//check if there are more than 2 directions otherwise dead end
	if(direction_counter == 1)
	{
		possible_directions = possible_directions | 0x10;
	}
	return possible_directions;
}

/**
 * @fn	uint8_t was_pacman_bitten()
 *
 * @brief	Checks if was pacman bitten.
 *
 * @return	An uint8_t.
 * 			
 * @todo	[Pacman_Biting_Ghost Extension]: was pacman bitten or is pacman biting?
 */

uint8_t was_pacman_bitten()
{
	uint8_t i;
	for(i=0;i<4;i++)
	{
		//when pacman and ghost are on the same position
		if(pacman->x_pos == ghosts[i]->x_pos && pacman->y_pos == ghosts[i]->y_pos
			//there was this moment when pacman and a ghost run face to face without crash but just passes on
			//when ghost is near pacman (one field distance)
				||
				(pacman->x_pos == ghosts[i]->x_pos && (pacman->y_pos == ghosts[i]->y_pos+1 || pacman->y_pos == ghosts[i]->y_pos-1))
				||
				(pacman->y_pos == ghosts[i]->y_pos && (pacman->x_pos == ghosts[i]->x_pos+1 || pacman->x_pos == ghosts[i]->x_pos-1))
			)
		{
			return 0x01;
		}
	}
	return 0x00;
}

void display_field_and_food(uint8_t index);
uint8_t get_bit_pacman_bmp(uint8_t x, uint8_t y);
uint8_t get_bit_ghost_bmp(uint8_t x, uint8_t y);
void display_taker(uint8_t index, taker taker);

/**
 * @fn	void display_pacman(uint8_t index)
 *
 * @brief	Main function for displaying Pacman.
 *
 * @param	index	Zero-based index of the row to display.
 */

void display_pacman(uint8_t index)
{
	uint8_t i;

	//first layer:				field
	//second layer:				pacman
	//third layer-last layer:	ghosts in ascending order

	display_field_and_food(index);

	//display pacman
	if((PACMAN_DISPLAY_FIELD_WIDTH/2)-(PACMAN_TAKER_WIDTH_AND_HEIGHT/2)<=index
		&& index <= (PACMAN_DISPLAY_FIELD_WIDTH/2)+(PACMAN_TAKER_WIDTH_AND_HEIGHT/2))
	{
		display_taker(index, pacman);
	}

	//display ghosts if in display range
	for(i=0;i<4;i++)
	{
		display_taker(index,ghosts[i]);
	}

	//display text when winning or losing
	if(game_state != PLAYING)
	{
		if(WIN == game_state)
		{
			//won
			write_str_to_led("You Win!",
				(PACMAN_DISPLAY_FIELD_WIDTH/2)-((FONT_LETTER_WIDTH+FONT_SPACE_BETWEEN_LETTER)*4),
				(PACMAN_DISPLAY_FIELD_HEIGHT/2)-(FONT_LETTER_HEIGHT/2),
				text_color,index);
		}
		else
		{
			//lost
			write_str_to_led("You Lose",
				(PACMAN_DISPLAY_FIELD_WIDTH/2)-((FONT_LETTER_WIDTH+FONT_SPACE_BETWEEN_LETTER)*4),
				(PACMAN_DISPLAY_FIELD_HEIGHT/2)-(FONT_LETTER_HEIGHT/2),
				text_color,index);
		}
	}
	display_set_row(leds);
}

/**
 * @fn	void display_field_and_food(uint8_t index)
 *
 * @brief	Displays field and food.
 *
 * @param	index	Zero-based index of the row to display.
 */

void display_field_and_food(uint8_t index)
{
	uint8_t i, x_rel, y_rel, food;

	x_rel = pacman->x_pos - (PACMAN_DISPLAY_FIELD_WIDTH/2) + index;
	y_rel = pacman->y_pos - (PACMAN_DISPLAY_FIELD_HEIGHT/2);

	//first layer:		wall
	//second layer:		food
	//third layer:		background

	for(i=0;i<NUM_LEDS_PER_ROW;i++)
	{
		if(is_wall_at(x_rel,y_rel) == 0x01)
		{
			leds[i] = wall_color;
		}
		else if(food = is_food_at(x_rel,y_rel))
		{
			if(0x02 == food)
			{
				leds[i] = special_food_color;
			}
			else
			{
				leds[i] = food_color;
			}
		}
		else
		{
			leds[i] = background_color;
		}
		y_rel++;
	}
}

/**
 * @brief	display pacman (5 bmps) ==> for each direction + when he is eating.
 */

const uint8_t pacman_NORTH_bmp[] PROGMEM = {
	0x00, 0x88, 0xD8, 0xF8, 0x70
};
const uint8_t pacman_EAST_bmp[] PROGMEM = {
	0x70, 0xE0, 0xC0, 0xE0, 0x70
};
const uint8_t pacman_SOUTH_bmp[] PROGMEM = {
	0x70, 0xF8, 0xD8, 0x88, 0x00
};
const uint8_t pacman_WEST_bmp[] PROGMEM = {
	0x70, 0x38, 0x18, 0x38, 0x70
};
const uint8_t pacman_EATING_bmp[] PROGMEM = {
	0x70, 0xF8, 0xF8, 0xF8, 0x70
};

/**
 * @fn	uint8_t get_bit_pacman_bmp(uint8_t x, uint8_t y)
 *
 * @brief	Get single bit from pacman bitmap depending on direction of pacman.
 *
 * @param	x	x-koordinate of the bit.
 * @param	y	y-koordinate of the bit.
 *
 * @return	The bit pacman bitmap.
 */

uint8_t get_bit_pacman_bmp(uint8_t x, uint8_t y)
{
	const uint8_t * bmp_source = NULL;
	if(pacman_has_eaten)
	{
		bmp_source = pacman_EATING_bmp;
	}
	else
	{
		switch (pacman->direction)
		{
		case NORTH: bmp_source = pacman_NORTH_bmp; break;
		case EAST: bmp_source = pacman_EAST_bmp; break;
		case SOUTH: bmp_source = pacman_SOUTH_bmp; break;
		case WEST: bmp_source = pacman_WEST_bmp; break;
		default:
			break;
		}
	}
#ifdef AVR
	return (pgm_read_byte(&bmp_source[y+(x/8)]) &   (1<< (7-((x)%8))));
#else
	return (bmp_source[y+(x/8)] &   (1<< (7-((x)%8)) ));
#endif
}

//display ghost

const uint8_t ghost_bmp[] PROGMEM = {
	0x70, 0xA8, 0xA8, 0xF8, 0xA8
};

/**
 * @fn	uint8_t get_bit_ghost_bmp(uint8_t x, uint8_t y)
 *
 * @brief	Get single bit from ghost bitmap.
 *
 * @param	x	x-koordinate of the bit.
 * @param	y	y-koordinate of the bit.
 *
 * @return	The bit ghost bitmap.
 */

uint8_t get_bit_ghost_bmp(uint8_t x, uint8_t y)
{
#ifdef AVR
	return (pgm_read_byte(&ghost_bmp[y+(x/8)]) &   (1<< (7-((x)%8))));
#else
	return (ghost_bmp[y+(x/8)] &   (1<< (7-((x)%8)) ));
#endif
}

/**
 * @fn	void display_taker(uint8_t index, taker taker)
 *
 * @brief	Displays a taker.
 *
 * @param	index	Zero-based index of the row to be displayed.
 * @param	taker	The taker to be displayed.
 * 					
 * @todo	taker will only be displayed when full taker is in sight... --> correct
 */

void display_taker(uint8_t index, taker taker)
{
	uint8_t i, x, y, x_taker_rel, y_taker_rel, is_pacman;
	//position on field relativ to display
	x_taker_rel = ((int16_t)(PACMAN_DISPLAY_FIELD_WIDTH/2))-(((int16_t)pacman->x_pos)-((int16_t)taker->x_pos));
	y_taker_rel = ((int16_t)(PACMAN_DISPLAY_FIELD_HEIGHT/2))-(((int16_t)pacman->y_pos)-((int16_t)taker->y_pos));

	//check if taker is in display range
	if(x_taker_rel-(PACMAN_TAKER_WIDTH_AND_HEIGHT/2)<=index
		&& index <= x_taker_rel+(PACMAN_TAKER_WIDTH_AND_HEIGHT/2)
		&& y_taker_rel<PACMAN_DISPLAY_FIELD_HEIGHT + (PACMAN_TAKER_WIDTH_AND_HEIGHT/2))
	{
		if(taker==pacman)
		{
			is_pacman = 0x01;
		}
		else
		{
			is_pacman = 0x00;
		}

		x=index-(x_taker_rel-(PACMAN_TAKER_WIDTH_AND_HEIGHT/2));
		y=0;
		for(i=y_taker_rel-(PACMAN_TAKER_WIDTH_AND_HEIGHT/2);i <= y_taker_rel+(PACMAN_TAKER_WIDTH_AND_HEIGHT/2);i++)
		{
			if(is_pacman)
			{
				if(get_bit_pacman_bmp(x,y))
				{
					leds[i] = taker->color;
				}
			}
			else
			{
				if(get_bit_ghost_bmp(x,y))
				{
					leds[i] = taker->color;
				}
			}
			y++;
		}
	}
}

/**
 * @fn	uint16_t pacman_get_score()
 *
 * @brief	get score.
 *
 * @return	An uint16_t.
 */

uint16_t pacman_get_score()
{
	return pacman_score;
}

/**
 * @}
 */
#endif
