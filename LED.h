/*
 * LED.h
 *
 Author: Wickramasooriya H.P.E.
 First written: 11/15/2020
 Last updated: 05/04/2021

 MCU:Atmega32
 Crystal:16 MHz
 Platform:Atmel Studio 7

 PURPOSE:
 Tutorial Book Issuing System for Mr.Incognito
 ************************************************/


#ifndef LED_H_
#define LED_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

 //Output Port for LEDs
 #define OUTPUT_LED_PORT PORTC
 
 //Green LED bit/pin
 #define LED_G_BIT PC6

 //Green LED Data Direction Register
 #define LED_G_DDR DDRC
 
 //Red LED bit/pin
 #define LED_R_BIT PC7
 
 //Red LED Data Direction Register
 #define LED_R_DDR DDRC

 #include <avr/io.h>
 #include <util/delay.h>
 
//Function prototypes

void init_io();
void LED_G_ON();
void LED_G_OFF();
void LED_R_ON();
void LED_R_OFF();

#endif /* LED_H_ */