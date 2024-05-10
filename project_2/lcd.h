/*
 * CFile1.c
 *
 * Created: 4/26/2024 12:25:14 PM
 *  Author: Chan Young Ji & Joel Akiyoshi
 */ 

#ifndef _LCD_H
#define _LCD_H

void lcd_init(void);

void lcd_clr(void);

void lcd_pos(unsigned char r, unsigned char c);

void lcd_put(char c);

void lcd_puts1(const char *s);

void lcd_puts2(const char *s);

typedef struct {
	int year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char military;
	unsigned char am;
	int mode_ampm;
	int is_am;
} DateTime;

void init_dt(DateTime *dt);

void advance_dt(DateTime *dt);

void print_dt(const DateTime *dt);

void print_time(const DateTime *dt);

void set_year(DateTime *dt);

void set_month(DateTime *dt);

void set_day(DateTime *dt);

void set_hour(DateTime *dt);

void set_minute(DateTime *dt);

void set_second(DateTime *dt);

void change_mode(DateTime *dt);

void change_ampm(DateTime *dt);

#endif /* _LCD_H */