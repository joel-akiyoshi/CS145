/*
 * keypad.c
 *
 * Created: 5/1/2024 12:23:05 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

#include "avr.h"
#include "keypad.h"
#include "stdio.h"

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
<<<<<<< HEAD:project2/keypad.c
	CLR_BIT(PORTA, 0);
	// set all GPIO to 0
	DDRC = 0;
	PORTC = 0xF0;
=======
	// set all GPIO to 0
	DDRC = 0;
	PORTC = 0;
>>>>>>> 8bb36e9b56c1b6958fc24492eb13d137f1b45ddf:project_2/keypad.c

    SET_BIT(DDRC, r);  // set row pin to OUTPUT
	CLR_BIT(PORTC, r);  // write a '0' to PORTC at r

	SET_BIT(PORTC, c + 4);  // pull up GPIO at col c
	
	if (!GET_BIT(PINC, c + 4))  // check to see if PINC is zero at col c
	{
		SET_BIT(PORTA, 0);
		return 1;
	}
	return 0;
}