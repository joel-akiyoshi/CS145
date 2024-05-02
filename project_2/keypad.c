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
	DDRC = 0;
	PORTC = 0;
	//set r to 0
	CLR_BIT(PORTC, r);
	//set c to w1
	SET_BIT(PORTC, c);
	if (!PORTC)
	{
		return 1;
	}
	return 0;
}