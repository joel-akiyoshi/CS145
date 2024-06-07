/*
 * speaker.h
 *
 * Created: 5/13/2024 1:26:53 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 
#ifndef _SPEAKER_H
#define _SPEAKER_H

typedef enum {A, As, B, C, Cs, D, Ds, E, F, Fs, G, Gs} Note;
	
const double THTL[]; 
const double period[];

typedef enum {W = 8, H = 4, Q = 2, Ei = 1} Duration;
	
typedef struct  
{
	Note note;
	Duration duration;
} PlayingNote;

void play_song(const PlayingNote song[], int length);
void play_note(const PlayingNote* note);
void play(PlayingNote note);
void stop_playing();


#endif /* _SPEAKER_H */