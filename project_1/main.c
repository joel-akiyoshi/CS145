/**
 * avr.c
 * Copyright (C) 2001-2020, Tony Givargis
 */

#include "avr.h"

void
avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

int main(void)
{
	DDRB = 1; //set PORTB Pin 0 as output, all else as input

	while(1)
	{
		if (!GET_BIT(PINB, 1))
		{
			SET_BIT(PORTB, 0); //turn PORTB PIN0 to 1, LED ON
			avr_wait(500); //delay
			CLR_BIT(PORTB, 0); //turn PORTB PIN0 to 0, LED OFF
			avr_wait(500); //delay	
		}
	}
}