/*
 * StepperMotor.h
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

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

//Function prototypes
void init_stepper();
void setup_wheel(void);
void wheel_Moving_front(void);
void move_round_front(void);
void move_angles_front(float angles);

float angle=45, radius=25.00, move_length=330, round_length, full_rounds, balance_length, angle_length, rounds_per_Round;
uint8_t angle_needed;
const int period = 100;

#endif /* STEPPERMOTOR_H_ */