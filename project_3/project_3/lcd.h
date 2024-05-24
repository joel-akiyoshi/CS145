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

void display_song(int sn);

#endif /* _LCD_H */