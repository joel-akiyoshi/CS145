/*
 * project_3.c
 *
 * Created: 5/13/2024 1:21:07 PM
 * Author : Chan Young Ji & Joel Akiyoshi
 */ 


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
	return 0;
}

