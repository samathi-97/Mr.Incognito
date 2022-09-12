/*
 * DCMotor.c
  *************************************************
  Author: Wickramasooriya H.P.E.
  First written: 11/15/2020
  Last updated: 05/04/2020

  MCU:Atmega32
  Crystal:16 MHz
  Platform:Atmel Studio 7

  PURPOSE:
  Tutorial Book Issuing System for Mr.Incognito
  ************************************************/

#include "DCMotor.h"

//Function to initialize port settings
void init_DC()
{
	//Set Data Direction Register to output mode for
	// Motor Driver1 pin 1
	DC1_1_DDR = 0xFF;
	
	//Set Data Direction Register to input mode for*********
	// IR sensor
	//IR_DDR = 0xDF;
	
	// Engage the internal pull-up resistors for
	//IR Input pin
	//INPUT_IR_PORT |= (1<<(INPUT_IR_BIT));
}

//Function to DC Motor Rotate
void DC_Rotate()
{
	OUTPUT_DC_PORT = 0x10;
}

//Function to DC Motor Stop
void DC_Stop()
{
	OUTPUT_DC_PORT = 0x00;
}
