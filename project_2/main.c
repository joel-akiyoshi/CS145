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
	DateTime dt;
	lcd_init();
	init_dt(&dt);
	while(1)
	{
		avr_wait(1000);
		advance_dt(&dt);
		print_dt(&dt);
		print_time(&dt);
		
		if(get_key() == 16) //key D
		{
			set_year(&dt);
			set_month(&dt);
			set_day(&dt);
		}
		
		else if(get_key() == 4) //key A
		{
			set_hour(&dt);
			set_min(&dt);
			set_sec(&dt);
		}
	}
	return 0;
}
