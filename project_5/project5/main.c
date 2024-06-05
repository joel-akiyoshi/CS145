/*
 * project5.c
 *
 * Created: 6/4/2024 3:46:48 PM
 * Author : Chan Young Ji & Joel Akiyoshi
 */ 

#include "avr.h"
//#include "speaker.h"
#include "keypad.h"
#include "lcd.h"
#include "puzzle.h"

#include <avr/io.h>

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
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.0001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

int keys[] = {1, 2, 3, 10,
    		  4, 5, 6, 10,
			  7, 8, 9, 10,
		     10, 0, 10, 10};



int main(void)
{
	lcd_init();
	lcd_clr();
	lcd_pos(0,0);
	Equation savedEq;
	int attempt = 0;
	int correct = 0;
	
    while (1) 
    {
		int new_sample = get_sample();
		
		if (new_sample > 400) //D to display
		{
			while(!correct)
			{
				Equation eq = randomEq(); //continuously randomized
				
				lcd_clr();
				if (attempt == 0) //first attempt => new question
				{
					savedEq = eq;
				}
				printEq(savedEq); //display equation
				int ans = getAns(); //get user answer
			
				correct = checkAns(savedEq, ans); //check answer
				if (correct)
				{
					avr_wait(20000);
					lcd_clr();
					// stop speaker noise
				} else
				{
					if (attempt == 0)
					{
						attempt = 1;
					} else //if attempt == 1
					{
						attempt = 0;
					}
				}
			}
			correct = 0;
		}
		
		avr_wait(2500);
    }
}


// int main(void)
// {
// 	lcd_init();
// 	lcd_clr();
// 	char light[20];
// 	
// 	while(1)
// 	{
// 		int new_sample = get_sample();
// 		sprintf(light, "%u", new_sample);
// 		lcd_pos(0, 0);
// 		lcd_puts2(light);
// 		
// 		avr_wait(2000);
// 	}
// 
// }

