/*
 * puzzle.c
 *
 * Created: 6/4/2024 3:56:36 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

#include "avr.h"
#include "puzzle.h"

const char operations[2] = {'+', '*'};

Equation randomEq(void)
{
	int a = rand() % 10; // a random int between 0~9
	int b = rand() % 10;
	int c = rand() % 10;
	int o1 = rand() % 2; // a random choice between 0 or 1
	int o2 = rand() % 2; 
	
	Operation op1 = (o1) ? Add : Multiply;
	Operation op2 = (o2) ? Add : Multiply;
	
	Equation randEq = {a, b, c, op1, op2};
	return randEq;
}

int calcEq(Equation eq)
{
	int temp1;
	int answer;
	
	if (eq.op1 == Multiply)
	{
		temp1 = eq.a * eq.b;
		if (eq.op2 == Multiply)
		{
			answer = temp1 * eq.c;
		}
		else //eq.op2 == Add
		{
			answer = temp1 + eq.c;
		}
	}
	else //eq.op1 == Add
	{
		if (eq.op2 == Multiply)
		{
			temp1 = eq.b * eq.c;
			answer = eq.a + temp1;
		}
		else //both operations are Add
		{
			answer = eq.a + eq.b + eq.c;
		}
	}
	
	return answer;
}

void printEq(Equation eq)
{
	lcd_pos(0,0);
	lcd_put(eq.a + '0');
	lcd_put(operations[eq.op1]);
	lcd_put(eq.b + '0');
	lcd_put(operations[eq.op2]);
	lcd_put(eq.c + '0');
}

void printAns(Equation eq)
{
	lcd_pos(1,0);
	int ans = calcEq(eq);
	
	int hun = 0;
	int ten = 0;
	
	while (ans >= 100)
	{
		hun++;
		ans -= 100;
	}
	while (ans >= 10)
	{
		ten++;
		ans -= 10;
	}
	
	lcd_put(hun + '0');
	lcd_put(ten + '0');
	lcd_put(ans + '0');
}

int getAns(void)
{
	int keys[] = {1, 2, 3, 10,
				  4, 5, 6, 10,
				  7, 8, 9, 10,
				 10, 0, 10, 10};
	
	lcd_pos(1,0);
	char buf[] = "Ans: ";
	lcd_puts2(buf);
	
	int index = 0;
	int ans[] = {0,0,0};
	
	while(1)
	{
		if (is_pressed(3,3) && index != 0) { break ; } //press D for done
			
		int k = get_key();
		if (k > 0 && k <= 16 && k%4 && k!=13 && k!=15 && index < 3) //key press only numbers up to 3 times
		{
			int num = keys[k - 1];
			lcd_put(num + '0');
			ans[index] = num;
			index++;
		}
		avr_wait(3000);
	}
	
	lcd_clr();
	
	if (index == 1)
	{
		return ans[0];
	} else if (index == 2)
	{
		return ans[0] * 10 + ans[1];
	} else //index == 3
	{
		return ans[0] * 100 + ans[1] * 10 + ans[2];
	}
}

int checkAns(Equation eq, int ans)
{
	lcd_clr();
	lcd_pos(0,0);
	int right = calcEq(eq);
	if (right == ans)
	{
		lcd_puts2("Correct!");
		return 1;
	}
	else
	{
		lcd_puts2("Try again.");
		return 0;
	}
}