/*
 * speaker.c
 *
 * Created: 5/13/2024 1:26:53 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

void play_note(const PlayingNote* note)
{
	int i, k;
	for (i = 0; i < k; ++i)
	{
		SET_BIT(PORTB, 3);
		//avr_wait(TH);
		CLR_BIT(PORTB, 3);
		//avr_wait(TL);
	}
}

void play_song(const PlayingNote song[], int length)
{
	int i;
	for (i = 0; i < length; ++i)
	{
		play_note(&song[i]);
	}
}