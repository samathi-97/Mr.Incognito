/*
 * LCD.h
 *
 * Created: 6/4/2021 12:10:04 AM
 *  Author: User
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>

#define LCD_CMD_CLEAR_DISPLAY	             0x01
#define LCD_CMD_CURSOR_HOME		             0x02

// Display control
#define LCD_CMD_DISPLAY_OFF                0x80
#define LCD_CMD_DISPLAY_NO_CURSOR          0x0c
#define LCD_CMD_DISPLAY_CURSOR_NO_BLINK    0x0E
#define LCD_CMD_DISPLAY_CURSOR_BLINK       0x0F

// Function set
#define LCD_CMD_4BIT_2ROW_5X7              0x28
#define LCD_CMD_8BIT_2ROW_5X7              0x38

//LCD DATA AND CONTROL PORTS
#define   DATA_BUS 	    	 PORTA
#define   CTL_BUS		     PORTB
#define   DATA_DDR	    	 DDRA
#define   CTL_DDR		     DDRB

//LCD DATA PINS
#define   LCD_D4			   4
#define   LCD_D5			   5
#define   LCD_D6			   6
#define   LCD_D7			   7

// LCD CONTROL PINS
#define   LCD_EN			   2
#define	  LCD_RW			   1
#define	  LCD_RS			   0

//functions prototype
void lcd_init(void);
void lcd_send_command (uint8_t );
void lcd_write_character(uint8_t );
void lcd_write_word(uint8_t[]);
void lcd_clear(void);
void lcd_set_courser(uint8_t,uint8_t);
void lcd_goto_xy (uint8_t , uint8_t );

//logic gates
#define SWITCH PINB
#define TEACHER PD4
#define REGISTERED PD5
#define WEEK PD6
#define PAID PD7




#endif /* LCD_H_ */

