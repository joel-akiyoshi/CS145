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
#include <stdbool.h>


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
	dt->day = 31;
	dt->hour = 11;
	dt->minute = 59;
	dt->second = 47;
	dt->mode_ampm = 0;
	dt->is_am = 1;
}

void
change_mode(DateTime *dt)
{
	if (dt->mode_ampm) //if mode in am/pm
	{
		dt->mode_ampm = 0; //set mode to military
		if (!dt->is_am && dt->hour > 12) //if clock in pm, add 12 hours to get military
		{
			dt->hour += 12;
		} else if (dt->is_am && dt->hour == 12) //else if 12 AM, set to 00 for military
		{
			dt->hour = 0;
		}
	} else {
		dt->mode_ampm = 1; //set mode to am/pm
		if (dt->hour == 0) 
		{
			dt->is_am = 1;
			dt->hour += 12;
		}
		else if (dt->hour >= 13) //if hour was above 13, decrease by 12 and set to PM
		{
			dt->is_am = 0;
			dt->hour -= 12;
		}
	}
}

void
change_ampm(DateTime *dt)
{
	if (dt->mode_ampm) //when only in am/pm mode, switch between am/pm
	{
		dt->is_am = !(dt->is_am);
	}
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
		if (dt->mode_ampm && dt->hour == 12) //if in am/pm and hour is 12, 
		{
			dt->is_am = !(dt->is_am); //switch am/pm
			if (dt->is_am) //if it was 12 am, increment day
			{
				++dt->day;
			}
		}
		dt->minute = 0;
	}
	
	//advance days
	if (dt->mode_ampm) //AM/PM mode
	{		
		if (dt->hour >= 13)
		{
			dt->hour = 1;
		}
	} else if (dt->hour >= 24) //military mode
	{
		++dt->day;
		dt->hour = 0;
	}
	
	//advance months
	if (dt->month == 2) //if February
	{
		if ((dt->year % 4) == 0) //if leap year
		{
			if (dt->day >= 30)
			{
				++dt->month;
				dt->day = 1;
			}
		}
		else if (dt->day >= 29)
		{
			++dt->month;
			dt->day = 1;
		}
	} else if (dt->day >= 32)
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
	if (dt->mode_ampm)
	{
		if (dt->is_am)
		{
			lcd_puts2(" AM");
		} else {
			lcd_puts2(" PM");
		}
	} else {
		lcd_puts2("   ");
	}
}

char keys[16] = {'1', '2', '3', 'A',
				 '4', '5', '6', 'B',
				 '7', '8', '9', 'C',
				 '*', '0', '#', 'D'};

void 
set_year(DateTime *dt)
{
	// prompt for year
	lcd_clr();
	char buf[] = "SET YEAR [YYYY]";
	lcd_pos(0,0);
	lcd_puts2(buf);
	
	// avr_wait(1000);
    
	// track key presses
	lcd_pos(1,0);
	int year[4];
	int element_count = 0;
	while(!(is_pressed(3, 3) && element_count == 4))
	{
		int key_index = get_key();
	    if (key_index > 0 && key_index <= 16 && key_index % 4 && element_count < 4)  // key on keypad, less than 4 digits written
		{
			char key = keys[key_index - 1];
			year[element_count] = key;
			element_count++;
			lcd_put(key);
		}
		avr_wait(500);
	}
	lcd_clr();
	dt->year = 1000 * (year[0] - '0') + 100 * (year[1] - '0') + 10 * (year[2] - '0') + (year[3] - '0');
}

void
set_month(DateTime *dt)
{
	// prompt for month
	lcd_clr();
	char buf[] = "SET MONTH [MM]";
	lcd_pos(0,0);
	lcd_puts2(buf);
	
	// avr_wait(1000);
	
	// track key presses
	lcd_pos(1,0);
	int month[2];
	int element_count = 0;
	while(!(is_pressed(3, 3) && element_count == 2))
	{
		int key_index = get_key();
		if (key_index > 0 && key_index <= 16 && key_index % 4 && element_count < 2)  // if the key is a valid number & less than 2 nums
		{
			char key = keys[key_index - 1];
			month[element_count] = key;
			element_count++;
			lcd_put(key);
		}
		avr_wait(500);
	}
	lcd_clr();
	dt->month = 10 * (month[0] - '0') + (month[1] - '0');
}

void
set_day(DateTime *dt)
{
	// prompt for day
	lcd_clr();
	char buf[] = "SET DAY [DD]";
	lcd_pos(0,0);
	lcd_puts2(buf);
	
	// avr_wait(1000);
	
	// track key presses
	lcd_pos(1,0);
	int day[2];
	int element_count = 0;
	while(!(is_pressed(3, 3) && element_count == 2))
	{
		int key_index = get_key();
		if (key_index > 0 && key_index <= 16 && key_index % 4 && element_count < 2)  // if the key is a valid number & less than 2 nums
		{
			char key = keys[key_index - 1];
			day[element_count] = key;
			element_count++;
			lcd_put(key);
		}
		avr_wait(250);
	}
	lcd_clr();
	dt->day = 10 * (day[0] - '0') + (day[1] - '0');
}

void
set_hour(DateTime *dt)
{
	// prompt for hour
	lcd_clr();
	char buf[] = "SET HOUR [HH]";
	lcd_pos(0,0);
	lcd_puts2(buf);
	
	// avr_wait(1000);
	
	// track key presses
	lcd_pos(1,0);
	int hour[2];
	int element_count = 0;
	while(!(is_pressed(0, 3) && element_count == 2))
	{
		int key_index = get_key();
		if (key_index > 0 && key_index <= 16 && key_index % 4 && element_count < 2)  // if the key is a valid number & less than 2 nums
		{
			char key = keys[key_index - 1];
			hour[element_count] = key;
			element_count++;
			lcd_put(key);
		}
		avr_wait(500);
	}
	lcd_clr();
	dt->hour = 10 * (hour[0] - '0') + (hour[1] - '0');
}

void
set_min(DateTime *dt)
{
	// prompt for minute
	lcd_clr();
	char buf[] = "SET MIN [MM]";
	lcd_pos(0,0);
	lcd_puts2(buf);
	
	// avr_wait(1000);
	
	// track key presses
	lcd_pos(1,0);
	int min[2];
	int element_count = 0;
	while(!(is_pressed(0, 3) && element_count == 2))
	{
		int key_index = get_key();
		if (key_index > 0 && key_index <= 16 && key_index % 4 && element_count < 2)  // if the key is a valid number & less than 2 nums
		{
			char key = keys[key_index - 1];
			min[element_count] = key;
			element_count++;
			lcd_put(key);
		}
		avr_wait(500);
	}
	lcd_clr();
	dt->minute = 10 * (min[0] - '0') + (min[1] - '0');
}

void
set_sec(DateTime *dt)
{
	// prompt for sec
	lcd_clr();
	char buf[] = "SET SEC [SS]";
	lcd_pos(0,0);
	lcd_puts2(buf);
	
	// avr_wait(1000);
	
	// track key presses
	lcd_pos(1,0);
	int sec[2];
	int element_count = 0;
	while(!(is_pressed(0, 3) && element_count == 2))
	{
		int key_index = get_key();
		if (key_index > 0 && key_index <= 16 && key_index % 4 && element_count < 2)  // if the key is a valid number & less than 2 nums
		{
			char key = keys[key_index - 1];
			sec[element_count] = key;
			element_count++;
			lcd_put(key);
		}
		avr_wait(500);
	}
	lcd_clr();
	dt->second = 10 * (sec[0] - '0') + (sec[1] - '0');
}