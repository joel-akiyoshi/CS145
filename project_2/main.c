/*
 * project2.c
 *
 * Created: 4/26/2024 12:16:17 PM
 * Author : Chan Young Ji & Joel Akiyoshi
 */ 

#include "avr.h"
#include "keypad.h"

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
	for (;;)
	{
		avr_wait(1000);
		int k = 0;
		k = get_key();
		if (!k)
		{
			SET_BIT(PORTB, 0);
		}
	}
}

