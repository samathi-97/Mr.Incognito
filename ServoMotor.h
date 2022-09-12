/*
 * ServoMotor.h
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

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

//Output Port for Servo motor
#define OUTPUT_SERVO_PORT PORTB

//Servo Motor bit/pin
#define SERVO_BIT PB3

//Servo Motor Data Direction Register
#define SERVO_DDR DDRB

#include <avr/io.h>
#include <util/delay.h>

//Function prototypes
void init_servo();
void SERVO_CLOCKWISE();
void SERVO_ANTI_CLOCKWISE();


#endif /* SERVOMOTOR_H_ */