#ifndef _ULTRA_H_
#define _ULTRA_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define PRESCLR1_VALUE 		            0x01
#define DISABLE_MODULE_VALUE 		    0x00
#define ZER0_INITIALIZER                0x00

#define   TRIGER_DDR    DDRD
#define   ECHO_DDR      DDRD
#define   TRIGER_PORT   PORTD //Data Registers
#define   ECHO_PULLUP   PORTD //to put the pins of the ports in a logic HIGH or logic LOW state
#define   TRIGER        6
#define   ECHO          3

/*************************************************
 ********* functions*****************************
 *************************************************/

void ultrasonic_init(void);
void enable_ex_interrupt(void);
void ultrasonic_triger(void);
void timer0_init(void);
void buzzer_int(void);
void buzzer_alarm(int ms);

#endif