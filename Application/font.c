/*
 * font.c
 *
 *  Created on: 19.04.2014
 *      Author: Clemens
 */

#include "font.h"

//characters are sorted by ascii values.

//special character first part
const char FONT_WHITESPACE[] PROGMEM = {0x00,0x00,0x00};
const char FONT_EXCLAMATION_MARK[] PROGMEM = {0x44,0x40,0x40};
const char FONT_QUOTATION_MARK[] PROGMEM = {0x55,0x00,0x00};
const char FONT_HASH_KEY[] PROGMEM = {0xD7,0xDB,0xA0};
const char FONT_DOLLAR[] PROGMEM = {0x7A,0x65,0xE0};
const char FONT_PERCENT[] PROGMEM = {0x09,0x24,0x90};
const char FONT_AMPERSAND[] PROGMEM = {0x4A,0x4A,0x50};
const char FONT_INVERTED_COMMA[] PROGMEM = {0x44,0x00,0x00};
const char FONT_ROUND_BRACKET_OPEN[] PROGMEM = {0x24,0x44,0x20};
const char FONT_ROUND_BRACKET_CLOSE[] PROGMEM = {0x42,0x22,0x40};
const char FONT_ASTERISK[] PROGMEM = {0x52,0x50,0x00};
const char FONT_PLUS_SIGN[] PROGMEM = {0x04,0xE4,0x00};
const char FONT_COMMA[] PROGMEM = {0x00,0x04,0x40};
const char FONT_MINUS_SIGN[] PROGMEM = {0x00,0xE0,0x00};
const char FONT_DOT[] PROGMEM = {0x00,0x00,0x40};
const char FONT_SLASH[] PROGMEM = {0x12,0x24,0x80};

//numbers
const char FONT_O_NUMBER[] PROGMEM = {0x69,0x99,0x60};
const char FONT_ONE_NUMBER[] PROGMEM = {0x26,0xA2,0x20};
const char FONT_TWO_NUMBER[] PROGMEM = {0x69,0x24,0xF0};
const char FONT_THREE_NUMBER[] PROGMEM = {0xE1,0x61,0xE0};
const char FONT_FOUR_NUMBER[] PROGMEM = {0x99,0xF1,0x10};
const char FONT_FIVE_NUMBER[] PROGMEM = {0xF8,0x61,0xE0};
const char FONT_SIX_NUMBER[] PROGMEM = {0x68,0xE9,0x60};
const char FONT_SEVEN_NUMBER[] PROGMEM = {0xF1,0x24,0x80};
const char FONT_EIGHT_NUMBER[] PROGMEM = {0x69,0x69,0x60};
const char FONT_NINE_NUMBER[] PROGMEM = {0x69,0x71,0x60};

//special character second part
const char FONT_COLON[] PROGMEM = {0x04,0x04,0x00};
const char FONT_SEMICOLON[] PROGMEM = {0x04,0x04,0x40};
const char FONT_LOWER_SIGN[] PROGMEM = {0x03,0x43,0x00};
const char FONT_EQUALS_SIGN[] PROGMEM = {0x0F,0x0F,0x00};
const char FONT_GREATER_SIGN[] PROGMEM = {0x0C,0x2C,0x00};
const char FONT_QUESTION_MARK[] PROGMEM = {0x69,0x20,0x40};
const char FONT_AT_SIGN[] PROGMEM = {0xF7,0xB7,0xB0};

//uppercase letters
const char FONT_A_UPPER[] PROGMEM = {0x69,0xF9,0x90};
const char FONT_B_UPPER[] PROGMEM = {0xE9,0xE9,0xE0};
const char FONT_C_UPPER[] PROGMEM = {0x78,0x88,0x70};
const char FONT_D_UPPER[] PROGMEM = {0xE9,0x99,0xE0};
const char FONT_E_UPPER[] PROGMEM = {0xF8,0xE8,0xF0};
const char FONT_F_UPPER[] PROGMEM = {0xF8,0xE8,0x80};
const char FONT_G_UPPER[] PROGMEM = {0x68,0xA9,0x60};
const char FONT_H_UPPER[] PROGMEM = {0x99,0xF9,0x90};
const char FONT_I_UPPER[] PROGMEM = {0x44,0x44,0x40};
const char FONT_J_UPPER[] PROGMEM = {0xF1,0x19,0x60};
const char FONT_K_UPPER[] PROGMEM = {0x9A,0xCA,0x90};
const char FONT_L_UPPER[] PROGMEM = {0x88,0x88,0xF0};
const char FONT_M_UPPER[] PROGMEM = {0x9F,0x99,0x90};
const char FONT_N_UPPER[] PROGMEM = {0x9D,0xDB,0xB0};
const char FONT_O_UPPER[] PROGMEM = {0x69,0x99,0x60};
const char FONT_P_UPPER[] PROGMEM = {0xE9,0xE8,0x80};
const char FONT_Q_UPPER[] PROGMEM = {0x69,0xDA,0x50};
const char FONT_R_UPPER[] PROGMEM = {0xE9,0xEA,0x90};
const char FONT_S_UPPER[] PROGMEM = {0x78,0x61,0xE0};
const char FONT_T_UPPER[] PROGMEM = {0xF2,0x22,0x20};
const char FONT_U_UPPER[] PROGMEM = {0x99,0x99,0x60};
const char FONT_V_UPPER[] PROGMEM = {0x99,0x96,0x60};
const char FONT_W_UPPER[] PROGMEM = {0x99,0x9F,0x60};
const char FONT_X_UPPER[] PROGMEM = {0x96,0x66,0x90};
const char FONT_Y_UPPER[] PROGMEM = {0x99,0x62,0x20};
const char FONT_Z_UPPER[] PROGMEM = {0xF1,0x24,0xF0};

//special character third part
const char FONT_SQUARED_BRACKET_OPEN[] PROGMEM = {0x64,0x44,0x60};
const char FONT_BACKSLASH[] PROGMEM = {0x84,0x42,0x10};
const char FONT_SQUARED_BRACKET_CLOSE[] PROGMEM = {0x62,0x22,0x60};
const char FONT_CARET[] PROGMEM = {0x4A,0x00,0x00};
const char FONT_UNDER_SCORE[] PROGMEM = {0x00,0x00,0xF0};
const char FONT_GRAVE_ACCENT[] PROGMEM = {0x84,0x40,0x00};

//lowercase letters
const char FONT_A_LOWER[] PROGMEM = {0x06,0x9B,0x50};
const char FONT_B_LOWER[] PROGMEM = {0x88,0xE9,0xE0};
const char FONT_C_LOWER[] PROGMEM = {0x06,0x88,0x60};
const char FONT_D_LOWER[] PROGMEM = {0x11,0xF9,0x70};
const char FONT_E_LOWER[] PROGMEM = {0x69,0xE8,0x60};
const char FONT_F_LOWER[] PROGMEM = {0x34,0xE4,0x40};
const char FONT_G_LOWER[] PROGMEM = {0x69,0x71,0x60};
const char FONT_H_LOWER[] PROGMEM = {0x88,0xE9,0x90};
const char FONT_I_LOWER[] PROGMEM = {0x40,0x44,0x40};
const char FONT_J_LOWER[] PROGMEM = {0x20,0x22,0xC0};
const char FONT_K_LOWER[] PROGMEM = {0x88,0xAC,0xA0};
const char FONT_L_LOWER[] PROGMEM = {0x44,0x44,0x20};
const char FONT_M_LOWER[] PROGMEM = {0x09,0xF9,0x90};
const char FONT_N_LOWER[] PROGMEM = {0x00,0xE9,0x90};
const char FONT_O_LOWER[] PROGMEM = {0x00,0x69,0x60};
const char FONT_P_LOWER[] PROGMEM = {0x06,0x9E,0x80};
const char FONT_Q_LOWER[] PROGMEM = {0x06,0x97,0x10};
const char FONT_R_LOWER[] PROGMEM = {0x00,0xB4,0x40};
const char FONT_S_LOWER[] PROGMEM = {0x68,0x61,0x60};
const char FONT_T_LOWER[] PROGMEM = {0x4E,0x44,0x20};
const char FONT_U_LOWER[] PROGMEM = {0x00,0x99,0x60};
const char FONT_V_LOWER[] PROGMEM = {0x00,0x96,0x60};
const char FONT_W_LOWER[] PROGMEM = {0x00,0x9F,0x60};
const char FONT_X_LOWER[] PROGMEM = {0x00,0xA4,0xA0};
const char FONT_Y_LOWER[] PROGMEM = {0x95,0x24,0x80};
const char FONT_Z_LOWER[] PROGMEM = {0x0F,0x24,0xF0};

//special character fourth part
const char FONT_CURLY_BRACKET_OPEN[] PROGMEM = {0x64,0x84,0x60};
const char FONT_PIPE[] PROGMEM = {0x44,0x44,0x40};
const char FONT_CURLY_BRACKET_CLOSE[] PROGMEM = {0x62,0x12,0x60};
const char FONT_TILDE[] PROGMEM = {0x05,0xA0,0x00};

const char* CHARACTERS_LOOK_UP_TABLE[]= {
	//special character first part
	FONT_WHITESPACE,FONT_EXCLAMATION_MARK,FONT_QUOTATION_MARK,FONT_HASH_KEY,FONT_DOLLAR,FONT_PERCENT,FONT_AMPERSAND,FONT_INVERTED_COMMA,FONT_ROUND_BRACKET_OPEN,FONT_ROUND_BRACKET_CLOSE
	,FONT_ASTERISK,FONT_PLUS_SIGN,FONT_COMMA,FONT_MINUS_SIGN,FONT_DOT,FONT_SLASH
	//numbers
	,FONT_O_NUMBER,FONT_ONE_NUMBER,FONT_TWO_NUMBER,FONT_THREE_NUMBER,FONT_FOUR_NUMBER,FONT_FIVE_NUMBER,FONT_SIX_NUMBER,FONT_SEVEN_NUMBER,FONT_EIGHT_NUMBER,FONT_NINE_NUMBER
	//special character second part
	,FONT_COLON,FONT_SEMICOLON,FONT_LOWER_SIGN,FONT_EQUALS_SIGN,FONT_GREATER_SIGN,FONT_QUESTION_MARK,FONT_AT_SIGN
	//uppercase letters
	,FONT_A_UPPER,FONT_B_UPPER,FONT_C_UPPER,FONT_D_UPPER,FONT_E_UPPER,FONT_F_UPPER,FONT_G_UPPER,FONT_H_UPPER,FONT_I_UPPER,FONT_J_UPPER,FONT_K_UPPER,FONT_L_UPPER,FONT_M_UPPER
	,FONT_N_UPPER,FONT_O_UPPER,FONT_P_UPPER,FONT_Q_UPPER,FONT_R_UPPER,FONT_S_UPPER,FONT_T_UPPER,FONT_U_UPPER,FONT_V_UPPER,FONT_W_UPPER,FONT_X_UPPER,FONT_Y_UPPER,FONT_Z_UPPER
	//special character third part
	,FONT_SQUARED_BRACKET_OPEN,FONT_BACKSLASH,FONT_SQUARED_BRACKET_CLOSE,FONT_CARET,FONT_UNDER_SCORE,FONT_GRAVE_ACCENT
	//lowercase letters
	,FONT_A_LOWER,FONT_B_LOWER,FONT_C_LOWER,FONT_D_LOWER,FONT_E_LOWER,FONT_F_LOWER,FONT_G_LOWER,FONT_H_LOWER,FONT_I_LOWER,FONT_J_LOWER,FONT_K_LOWER,FONT_L_LOWER,FONT_M_LOWER
	,FONT_N_LOWER,FONT_O_LOWER,FONT_P_LOWER,FONT_Q_LOWER,FONT_R_LOWER,FONT_S_LOWER,FONT_T_LOWER,FONT_U_LOWER,FONT_V_LOWER,FONT_W_LOWER,FONT_X_LOWER,FONT_Y_LOWER,FONT_Z_LOWER
	//special character fourth part
	,FONT_CURLY_BRACKET_OPEN,FONT_PIPE,FONT_CURLY_BRACKET_CLOSE,FONT_TILDE
};

const char get_byte_from_character(const char * characteradr, uint8_t index){
#ifdef AVR
	return pgm_read_byte(&characteradr[index]);
#else
	return characteradr[index];
#endif
}

const char * get_char_matrix (const char ch)
{
	if(ch >= ' ' && ch <= '~')
	{
		return CHARACTERS_LOOK_UP_TABLE[ch-' '];
	}
	else
	{
		return NULL;
	}
}

void display_char(const char* char_matrix, uint8_t x_pos, uint8_t y_pos,RGB color, uint8_t index)
{
	uint8_t i, x_pos_cur, is_pixel_active, char_matrix_line;
	if(x_pos+FONT_LETTER_WIDTH<=num_rows && y_pos+FONT_LETTER_HEIGHT<=NUM_RGB_LEDS_PER_ROW)
	{
		x_pos_cur = index-x_pos;
		for(i=0;i<FONT_LETTER_HEIGHT;i++)
		{
			is_pixel_active = 0;
			if(0==i%2)
			{
				char_matrix_line = get_byte_from_character(char_matrix,(i/2));
				if((char_matrix_line >> (7-x_pos_cur) & 0x01))
				{
					is_pixel_active = 1;
				}
			}
			else
			{
				if((char_matrix_line >> (3-x_pos_cur) & 0x01))
				{
					is_pixel_active = 1;
				}
			}
			if(is_pixel_active)
			{
				leds[y_pos+i]=color;
			}
		}
	}
}

void write_char_to_led(const char ch, uint8_t x_pos, uint8_t y_pos, RGB color, uint8_t index)
{
	const char * char_matrix;
	//char tmp[] = {0, 0};
	if(index >= x_pos && index < x_pos + FONT_LETTER_WIDTH)
	{
		//tmp[0] = ch;
		//debug_string("get_char_matrix(ch=");
		//debug_string(tmp);
		//debug_string(")\n");
		char_matrix = get_char_matrix(ch);
		//debug_string("=>[");
		//debug_int(char_matrix[0]);
		//debug_string("][");
		//debug_int(char_matrix[1]);
		//debug_string("][");
		//debug_int(char_matrix[2]);
		//debug_string("]\n");
		if(NULL != char_matrix)
		{
			display_char(char_matrix, x_pos, y_pos, color, index);
		}
	}
}

void write_str_to_led(const char* str, uint8_t x_pos, uint8_t y_pos, RGB color, uint8_t index)
{
	uint8_t i=0, x_pos_tmp=x_pos;
	while(str[i]!=NULL && i<=FONT_MAX_LETTERS_IN_ROW)
	{
		write_char_to_led(str[i], x_pos_tmp, y_pos, color,index);
		x_pos_tmp += FONT_LETTER_WIDTH + FONT_SPACE_BETWEEN_LETTER;
		i++;
	}
}

void write_int_to_led(const uint32_t num, uint8_t x_pos, uint8_t y_pos, RGB color, uint8_t index)
{
	uint32_t tmp;
	uint8_t num_of_digits, i;
	char str_of_num[FONT_MAX_NUM_DIGITS];
	//only display num if number is short enough to display
	tmp = 1;
	for(i=0;i<FONT_MAX_NUM_DIGITS;i++)
	{
		tmp *= 10;
	}
	if(num<=tmp-1)
	{
		//convert num into decimal string
		tmp = num;
		for (i=0;i<FONT_MAX_NUM_DIGITS;i++)
		{
			str_of_num[(FONT_MAX_NUM_DIGITS-1)-i] = '0' + (tmp%10);
			tmp /= 10;
		}
		//delete leading '0's by pushing relevant string to the front of the array
		num_of_digits=FONT_MAX_NUM_DIGITS;
		while(str_of_num[0] == '0' && num_of_digits!=1)
		{
			for(i=1;i<num_of_digits;i++)
			{
				str_of_num[i-1]=str_of_num[i];
				str_of_num[i]=0;
			}
			num_of_digits--;
		}
		//only display if there is a number
		if(num_of_digits>0)
		{
			write_str_to_led(str_of_num,x_pos,y_pos,color,index);
		}
	}
}
