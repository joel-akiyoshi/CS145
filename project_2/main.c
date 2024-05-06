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
	
	int r, c;
	char a = '0';
	for (r = 0; r < 2; r++) 
	{
		for (c = 0; c < 16; c++)
		{
			lcd_pos(r, c);
			lcd_put(a);
			avr_wait(100);
		}
	}
}
