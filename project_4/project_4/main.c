/*
 * project_4.c
 *
 * Created: 5/24/2024 3:33:06 PM
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
    while (1) 
    {
    }
}

