/*
 * lcd.c
 *
 * Created: 4/26/2024 12:26:06 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 
#include "avr.h"
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>


#define DDR    DDRB
#define PORT   PORTB
#define RS_PIN 0
#define RW_PIN 1
#define EN_PIN 2

static inline void
set_data(unsigned char x) 
{
	PORTD = x;
	DDRD = 0xff;
}

static inline unsigned char
get_data(void)
{
	DDRD = 0x00;
	return PIND;
}

static inline void
sleep_700ns(void)
{
	NOP();
	NOP();
	NOP();
}

static unsigned char
input(unsigned char rs)
{
	unsigned char d;
	if (rs) SET_BIT(PORT, RS_PIN); else CLR_BIT(PORT, RS_PIN);
	SET_BIT(PORT, RW_PIN);
	get_data();
	SET_BIT(PORT, EN_PIN);
	sleep_700ns();
	d = get_data();
	CLR_BIT(PORT, EN_PIN);
	return d;
}

static void
output(unsigned char d, unsigned char rs)
{
	if (rs) SET_BIT(PORT, RS_PIN); else CLR_BIT(PORT, RS_PIN);
	CLR_BIT(PORT, RW_PIN);
	set_data(d);
	SET_BIT(PORT, EN_PIN);
	sleep_700ns();
	CLR_BIT(PORT, EN_PIN);
}

static void
write(unsigned char c, unsigned char rs)
{
	while (input(0) & 0x80);
	output(c, rs);
}

void
lcd_init(void)
{
	SET_BIT(DDR, RS_PIN);
	SET_BIT(DDR, RW_PIN);
	SET_BIT(DDR, EN_PIN);
	avr_wait(16);
	output(0x30, 0);
	avr_wait(5);
	output(0x30, 0);
	avr_wait(1);
	write(0x3c, 0);
	write(0x0c, 0);
	write(0x06, 0);
	write(0x01, 0);
}

void
lcd_clr(void)
{
	write(0x01, 0);
}

void
lcd_pos(unsigned char r, unsigned char c)
{
	unsigned char n = r * 40 + c;
	write(0x02, 0);
	while (n--) {
		write(0x14, 0);
	}
}

void
lcd_put(char c)
{
	write(c, 1);
}

void
lcd_puts1(const char *s)
{
	char c;
	while ((c = pgm_read_byte(s++)) != 0) {
		write(c, 1);
	}
}

void
lcd_puts2(const char *s)
{
	char c;
	while ((c = *(s++)) != 0) {
		write(c, 1);
	}
}

void 
init_dt(DateTime *dt)
{
	dt->year = 2022;
	dt->month = 12;
	dt->day = 30;
	dt->hour = 23;
	dt->minute = 59;
	dt->second = 50;
}

void 
advance_dt(DateTime *dt)
{
	//tick seconds
	++dt->second;
	
	//advance minutes
	if (dt->second >= 60)
	{
		++dt->minute;
		dt->second = 0;
	}
	
	//advance hours
	if (dt->minute >= 60)
	{
		++dt->hour;
		dt->minute = 0;
	}
	
	//advance days
	if (dt->hour >= 24)
	{
		++dt->day;
		dt->hour = 0;
	}
	
	//advance months
	if (dt->day >= 32)
	{
		++dt->month;
		dt->day = 1;
	}
	
	//advance years
	if (dt->month >= 13)
	{
		++dt->year;
		dt->month = 1;
	}
}

void 
print_dt(const DateTime *dt)
{
	char buf[17];
	lcd_pos(0,0);
	sprintf(buf, "%04d/%02d/%02d", dt->year, dt->month, dt->day);
	lcd_puts2(buf);
}

void
print_time(const DateTime *dt)
{
	char buf[17];
	lcd_pos(1,0);
	sprintf(buf, "%02d:%02d:%02d", dt->hour, dt->minute, dt->second);
	lcd_puts2(buf);
}

void 
enter_year(DateTime *dt)
{
	lcd_clr();
	char buf[] = "YEAR?";
	lcd_pos(0,0);
	lcd_puts2(buf);
	
	char keys[16] = {'1', '2', '3', 'A',
					 '4', '5', '6', 'B',
					 '7', '8', '9', 'C',
					 '*', '0', '#', 'D'};
	
	int year[4];
	
	lcd_pos(1,0);
	int i, k;
	i = 0;
	while(!is_pressed(3,3)) //until press D
	{
		k = get_key();
		if (k > 0 && k < 16)
		{
			if (k == 12)
			{
				lcd_clr();
				lcd_pos(0,0);
				lcd_puts2(buf);
				lcd_pos(1,0);
				year[0] = 0;
				year[1] = 0;
				year[2] = 0;
				year[3] = 0;
				
			} else {
				lcd_put(keys[k-1]);
				if (i < 4)
				{
					year[i-1] = keys[k-1] - '0';
					++i;
				}
				avr_wait(300);
			}
		}
	}
	dt->year = year[0] * 1000 + year[1] * 100 + year[2] * 10 + year[3] * 1;
}