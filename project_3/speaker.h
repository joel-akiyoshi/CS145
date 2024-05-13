/*
 * speaker.h
 *
 * Created: 5/13/2024 1:26:53 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

typedef enum {A, As, B, C, Cs, D, Ds, E, F, Fs, G, Gs} Note;
	
int THTL[] = {0,0,0,0,0,0,0,0,0,0,0,0};
int dur[] = {0,0,0,0,0,0,0,0,0,0,0,0};

typedef enum {W, H, Q, E} Duration;
	
typedef struct  
{
	Note note;
	Duration duration;
} PlayingNote;

void play_song(const PlayingNote song[], int length);
void play_note(const PlayingNote* note);