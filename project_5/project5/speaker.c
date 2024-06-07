/*
 * speaker.c
 *
 * Created: 5/13/2024 1:26:53 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

#include "avr.h"
#include "speaker.h"
#include <avr/interrupt.h>


const double THTL[] = {22.73, //A
					   21.45, //As
					   20.25, //B
					   19.11, //C
					   18.04, //Cs
					   17.03, //D
					   16.07, //Ds
					   15.17, //E
					   14.32, //F
					   13.51, //Fs
					   12.76, //G
					   12.04, //Gs
					   11.36, //A
					   10.73, //As
					   10.12, //B
					   09.56, //C
					   09.02, //Cs
					   08.51, //D
					   08.04, //Ds
					   07.58, //E
					   07.16, //F
					   06.76, //Fs
					   06.38, //G
					   06.02}; //Gs
					   
const double period[] = {0.004545,
						 0.004290,
						 0.004050,
						 0.003822,
						 0.003606,
						 0.003405,
						 0.003214,
						 0.003034,
						 0.002863,
						 0.002703,
						 0.002551,
						 0.002408,
						 0.002273,
						 0.002145,
						 0.002025,
						 0.001911,
						 0.001804,
						 0.001703,
						 0.001607,
						 0.001517,
						 0.001432,
						 0.001351,
						 0.001276,
						 0.001204};

void play_note(const PlayingNote* note)
{
	int i, k;
	k = note->duration / period[note->note];
	for (i = 0; i < k; ++i)
	{
		SET_BIT(PORTA, 1);
		avr_wait(THTL[note->note]);
		CLR_BIT(PORTA, 1);
		avr_wait(THTL[note->note]);
	}
}

#include "speaker.h"


void play(PlayingNote note) {
	// Set PA1 as output
	DDRA |= (1 << PA1);

	// Calculate the timer compare match value for the desired frequency
	unsigned int compare_match_value = 300;

	TCCR1A = 0;  // Normal port operation
	TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);  // CTC mode, Prescaler = 64
	OCR1A = compare_match_value;  // Set compare match value

	// Enable Timer1 compare match A interrupt
	TIMSK |= (1 << OCIE1A);

	// Enable global interrupts
	sei();
}

void stop_playing(void) {
	// Disable Timer1 compare match A interrupt
	TIMSK &= ~(1 << OCIE1A);

	// Set PA1 to low
	PORTA &= ~(1 << PA1);

	// Reset Timer1 configuration
	TCCR1A = 0;
	TCCR1B = 0;
}

// Timer1 compare match A interrupt service routine
ISR(TIMER1_COMPA_vect) {
	// Toggle PA1
	PORTA ^= (1 << PA1);
}
