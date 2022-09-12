/*
 * DCMotor.h
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

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

//Output Port for Motor Driver1 ( DC motor )
#define OUTPUT_DC_PORT PORTC

// Motor Driver1 bit/pin s
#define DC1_1_BIT PC4

// Motor Driver1 Data Direction Register
#define DC1_1_DDR DDRC

//IR Sensor Data Direction Register
#define IR_DDR DDRB

//IR Input Port
#define INPUT_IR_PORT PORTB

//Input register - for reading pins
#define SENSE_IR_PORT PINB

//Input bits/pins individually defined
#define INPUT_IR_BIT PB5

#include <avr/io.h>
#include <util/delay.h>

//Function prototypes
void init_DC();
void DC_Rotate();
void DC_Stop();

#endif /* DC_MOTOR_H_ */