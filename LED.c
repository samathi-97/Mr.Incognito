/*
 * LED.c
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

//Import the LED Header File
#include "LED.h"
 
 //Function to initialize port settings
 	void init_io()
 	{
	
	 	//Set Data Direction Register to output mode for
	 	//Green LED pin
	 	LED_G_DDR = 0xFF;
		 
		//Set Data Direction Register to output mode for
		//Red LED pin
		LED_R_DDR |= (1<<(LED_R_BIT));
	 	
 	}
// Function for Green LED on
void LED_G_ON()
{
	OUTPUT_LED_PORT = 0x40;
}

// Function for Green LED off
void LED_G_OFF()
{
	OUTPUT_LED_PORT = 0x00;
}

// Function for Red LED on
void LED_R_ON()
{
	OUTPUT_LED_PORT |= (1<<(LED_R_BIT));
}

// Function for Red LED off
void LED_R_OFF()
{
	OUTPUT_LED_PORT &=~ (1<<(LED_R_BIT));
}