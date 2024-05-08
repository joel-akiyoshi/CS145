/*
 * project2.c
 *
 * Created: 4/26/2024 12:16:17 PM
 * Author : Chan Young Ji & Joel Akiyoshi
 */ 

// testing git branch with a comment

#include "avr.h"
#include "keypad.h"
#include "lcd.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void
avr_init(void)
{
	WDTCR = 15;
}

void
avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

main()
{
	lcd_init();
	lcd_clr();
	
	DateTime dt;
	init_dt(&dt);
	while(1)
	{
		avr_wait(1000);
		advance_dt(&dt);
		print_dt(&dt);
		print_time(&dt);
		if (is_pressed(0,3)) //if A is pressed (2 sec press)
		{
			enter_year(&dt);
		}
	}

// 	char keys[16] = {'1', '2', '3', 'A',
// 					 '4', '5', '6', 'B',
// 					 '7', '8', '9', 'C',
// 					 '*', '0', '#', 'D'};
// 
// 	DDRA = 0x01;
// 	int k;
// 	
// 	lcd_pos(0,0);
// 	while (1)
// 	{
// 		k = get_key();
// 		if (k > 0 && k <= 16)
// 		{
// 			if (k == 12)
// 			{
// 				lcd_clr();
// 				lcd_pos(0,0);
// 			} else {
// 				lcd_put(keys[k-1]);
// 				avr_wait(300);	
// 			}
// 		}
// 	}
	return 0;
}