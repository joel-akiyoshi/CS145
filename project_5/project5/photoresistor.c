/*
 * photoresistor.c
 *
 * Created: 6/5/2024 3:49:07 PM
 *  Author: jauk4
 */ 

#include "avr.h"
#include "photoresistor.h"

int get_sample()
{
	ADMUX = 0b01000000;
	ADCSRA = 0b11000000;
	while (GET_BIT(ADCSRA, 6));
	return ADC;
}
