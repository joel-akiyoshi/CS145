/*
 * voltmeter.c
 *
 * Created: 5/29/2024 12:28:29 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

#include "voltmeter.h"
#include "avr.h"

int get_sample()
{
	ADMUX = 0b01000000;
	ADCSRA = 0b11000000;
	while (GET_BIT(ADCSRA, 6));
	return ADC;
}

int compute_max(int current_max)
{
	int new_sample = get_sample();
	if (new_sample > current_max)
	{
		current_max = new_sample;
	}
	return current_max;
}

int compute_min(int current_min)
{
	int new_sample = get_sample();
	if (new_sample < current_min)
	{
		current_min = new_sample;
	}
	return current_min;
}

int compute_avg(int current_avg)
{
	
}