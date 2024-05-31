/*
 * project_4.c
 *
 * Created: 5/24/2024 3:33:06 PM
 * Author : Chan Young Ji & Joel Akiyoshi
 */ 

#include "avr.h"
#include "lcd.h"
#include "voltmeter.h"
#include "keypad.h"

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
	DDRA = 0;
	char volt[20];
	char avg[20];
	unsigned int max;
	unsigned int min;
	char max_str[20];
	char min_str[20];
	avr_init();
	lcd_init();
	
	unsigned long sum = 0;
	unsigned long count = 0;
	
	char reset_state = 0;
	
	while(1)
	{
	    lcd_clr();
		int new_sample = get_sample();  // int value from 0-1023
		max = compute_max(max);
		sprintf(max_str, "%.2f", (max / 1023.0) * 5);

		min = compute_min(min);
		sprintf(min_str, "%.2f", (min / 1023.0) * 5);
		
		sum += new_sample;
		sprintf(avg, "%.2f", ((sum / ++count) / 1023.0) * 5);
		
		// instantaneous voltage
    	sprintf(volt, "%.2f", (new_sample / 1023.0) * 5);
		lcd_pos(0, 0);
		lcd_puts2(volt);
		
		if (get_key() == 4)
		{
			reset_state = !reset_state;
		}
		
		if (!reset_state)
		{
			// max
			lcd_pos(1, 0);
			lcd_puts2(max_str);
		
			// min
			lcd_pos(1, 9);
			lcd_puts2(min_str);
		
			// avg
			lcd_pos(0, 9);
			lcd_puts2(avg);	
			avr_wait(1000);
		} else {
			lcd_pos(1, 0);
			lcd_puts2("---");
			max = new_sample;
			lcd_pos(1, 9);
			lcd_puts2("---");
			min = new_sample;
			lcd_pos(0, 9);
			lcd_puts2("---");
			sum = 0;
			count = 0;
			avr_wait(500);
		}
	}
}

