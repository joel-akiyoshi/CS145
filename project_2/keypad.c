/*
 * keypad.c
 *
 * Created: 5/1/2024 12:23:05 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

#include "avr.h"
#include "keypad.h"

int get_key()
{
	int i, j;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			if (is_pressed(i,j))
			{
				return i * 4 + j + 1;
			}
		}
	}
}

int is_pressed(int r, int c)
{
	// set all 8 GPIO's to N/C
	DDRC = 0;
	PORTC = 0;

	SET_BIT(DDRC, r);  // row r mode to output
	CLR_BIT(PORTC, r);  // row r value to 0
	
	SET_BIT(PORTC, c + 4);  // col c value to w1 (not actually pulling up)
	
	if (!GET_BIT(PINC, (c + 4)))
	{
		return 1;
	}
	return 0;
}