/*
 * project_3.c
 *
 * Created: 5/13/2024 1:21:07 PM
 * Author : Chan Young Ji & Joel Akiyoshi
 */ 


#include "avr.h"
#include "keypad.h"
#include "lcd.h"
#include "speaker.h"

#include <avr/io.h>
#include <stdio.h>

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
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.00001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

int main(void)
{
	SET_BIT(DDRB, 3);
	PlayingNote twinkle[] = {{A, Q}, {A, Q}, {E, Q}, {E, Q}, {Fs, Q}, {Fs, Q}, {E, H}, {D, Q}, {D, Q}, {Cs, Q}, {Cs, Q}, {B, Q}, {B, Q}, {A, H},
		                  {E, Q}, {E, Q}, {D, Q}, {D, Q}, {Cs, Q}, {Cs, Q}, {B, H}, {E, Q}, {E, Q}, {D, Q}, {D, Q}, {Cs, Q}, {Cs, Q}, {B, H},
						  {A, Q}, {A, Q}, {E, Q}, {E, Q}, {Fs, Q}, {Fs, Q}, {E, H}, {D, Q}, {D, Q}, {Cs, Q}, {Cs, Q}, {B, Q}, {B, Q}, {A, H}}; //42 notes
	
	PlayingNote rickRoll[] = {{A, Ei}, {A, Ei}, {A, Ei}, {B, Ei}, {B, H}, {B, Ei}, {B, Ei}, {B, Ei}, {Cs, Ei}, {Cs, Q}, 
						      {E, Ei}, {D, Ei}, {Cs, Ei}, {A, Ei}, {A, Ei}, {A, Ei}, {B, Ei}, {B, H}, {B, Q}, {Cs, H},
							  {A, Ei}, {B, Ei}, {D, Ei}, {B, Ei}, {Fs, Ei}, {Fs, Ei}, {Fs, Ei}, {Fs, Ei}, {Fs, Ei}, {Fs, Ei}, 
							  {E, H}, {A, Ei}, {B, Ei}, {D, Ei}, {B, Ei}, {E, Ei}, {E, Ei}, {E, Ei}, {E, Ei}, {E, Ei}, 
							  {E, Ei}, {D, H}, {A, Ei}, {B, Ei}, {D, Ei}, {B, Ei}, {D, Ei}, {D, Ei}, {D, Ei}, {E, Ei}, 
							  {E, Ei}, {E, Ei}, {Cs, Ei}, {B, Ei}, {A, Ei}, {A, Q}, {A, Q}, {A, Q}, {E, Q}, {D, W}}; //60 notes
							  
	lcd_init();
	
	while(1)
	{
		lcd_pos(0,0);
		char waiting[] = "Not playing...";
		lcd_puts2(waiting);
		
		int k;
		k = get_key();
		if (k == 1) //start song1
		{
			display_song(1);
			play_song(twinkle, 42);
			lcd_clr();
		} else if (k == 2) //start song2
		{
			display_song(2);
			play_song(rickRoll, 60);
			lcd_clr();
		}
	}
	return 0;
}

