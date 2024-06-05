/*
 * puzzle.h
 *
 * Created: 6/4/2024 3:57:00 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

#ifndef _PUZZLE_H
#define _PUZZLE_H
	
typedef enum {Add, Multiply} Operation;
	
typedef struct
{
	int a;
	int b;
	int c;
	Operation op1;
	Operation op2;
} Equation;

Equation randomEq(void);

int calcEq(Equation eq);

void printEq(Equation eq);

int getAns(void);

int checkAns(Equation eq, int ans);


#endif /* _PUZZLE_H */