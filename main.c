/*
 * Final_code_Member3.c
 *************************************************
 Author: group 25
 First written: 15/11/2020
 Last updated: 08/06/2021

 MCU:Atmega32
 Crystal:8 MHz
 Platform:Atmel Studio 7

 PURPOSE:
 Class Management System
 ************************************************/

// 8 MHz crystal oscillator on my Development System.
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define input PIND2

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>

//Include Files
#include "LED.h"
#include "ServoMotor.h"
#include "StepperMotor.h"
#include "DCMotor.h"
#include "ultra_buzzer.h"
#include "LCD.h"
#include "doorSystem.h"

//Function prototypes
void setWifiConnection(void);
void usartinit();
void sendToUdr(char *str);
void detectTeacher(void);
void tuteIssuingProcess(void);
void notREgistered(void);
void PIRdetect(void);
void openDoorInside(void);
void refillingSystem(void);
char USART_RxChar(); //rfid
void enable_wifi(); // multiplexer
void disable_wifi();
unsigned char rxvalue(void);

//AT commands
char wifiCmd1[] = "AT\r\n"; // basic command that test AT start
char wifiCmd2[] = "AT+CWLAP\r\n";//List the Access points
char wifiCmd3[] = "AT+CWJAP=123445,1a2Bcd123\r\n";// command to connect as access point,ssid and password (service set identifier /known name)
char wifiCmd4[] = "AT+CIPMUX=1\r\n"; // enable or disable multiple connections
char wifiCmd5[] = "AT+CWMODE=2\r\n";//set wifi mode of operation,station access point both
char wifiCmd6[] = "AT+CIFSR\r\n";//get local address
char wifiCmd7[] = "AT+CIPSERVER=1,80\r\n"; //to create as server

//variables
int Teacher=0; //Check whether a teacher or not (If a teacher, Teacher=1)
int paid=0; //Check whether paid or not (If paid student, paid=1)
int registered=0; // Check whether registered or not
int week=0; // Check whethere first week or not
int value3[4]; // databese data
int r=0;
char RFID[12]="/0";
char IpAddress[20];
unsigned char rxdata;

int main(void)
{
	init_io();
	init_servo();
	setup_wheel();
	init_DC();
	ultrasonic_init();
	buzzer_int();
	lcd_init();
	usartinit();
	sei();
	
	DDRB = 0xEF; // edited 0F to FF
	DDRA = 0xFF;
	DDRD =  0xD7; // edited FF to D7 PD3 and PD5 Input
	DDRC =  0xFF;
	
	memset(RFID,0,15);
	while (1)
	{
		// RFID
		disable_wifi();
		for (r=0;r<12;r++)
		{
			RFID[r]=USART_RxChar();
			//Reading 12 digit number from Rfid reader 
		}
		sendToUdr(RFID);		
		_delay_ms(1000);	
		r=0;
		
		//wifi module
		enable_wifi();
		setWifiConnection();
		getIPAdress();
		//Send RFID number to database
		//Receiving data from database. Assigning  data to variables(teacher,paid etc) as 1 and 0
				
		//Tute issuing machine.
		refillingSystem(); // Ultrasonic Sensor
		
		while(1){						
			int characters=0; // count the number of characters in data, received from the database
			while(1)
			{
				while((UCSRA)&(1<<RXC)) // read the data in UDR until RXC enable  read bit by bit
				{
					value3[characters]=UDR;
					_delay_ms(1);
					characters++;//bit by bit and count up
				}
				if (characters>=4) // Check whether number of characters are equal
				{
					if (Teacher==1 && registered==0 && paid==0 && week==0) 
					{						
						detectTeacher();
						PIRdetect();						
					}					
					else if (Teacher==0 && registered==0 && paid==0 && week==0) {
						notREgistered();
						lcd_write_word("No operation"); // No operation because of a not registered, not paid and not week 1 of the month
						lcd_clear();
					}
					else if (Teacher==0 && registered==1 && paid==0 && week==0){ 
						Red_LED();
						lcd_write_word("Not paid");
						lcd_goto_xy(1,0);
						lcd_write_word("Cannot attend");
						lcd_clear();
					}
					else if (Teacher==0 && registered==1 && paid==0 && week==1){ 
						Red_LED();
						lcd_write_word("Can attend");
						lcd_goto_xy(1,0);
						lcd_write_word("Cannot Issue Tute");
						lcd_clear();
						DoorOpen();
						PIRdetect();						
					}
					else if (Teacher==0 && registered==1 && paid==1 && week==0){
						tuteIssuingProcess();
						DoorOpen();
						PIRdetect();
					}
					else if (Teacher==0 && registered==1 && paid==1 && week==1){
						tuteIssuingProcess();
						DoorOpen();
						PIRdetect();
					}
					break;					
				}				
			}
		}
		openDoorInside();
	 }
}

//Functions 
void Red_LED()
{
	//Code for blink Red LED
	LED_R_ON();
	_delay_ms(1000);
	LED_R_OFF();
	//_delay_ms(1000);
}

void Green_LED()
{
	//Code for blink Red LED
	LED_G_ON();
	_delay_ms(1000);
	LED_G_OFF();
	//_delay_ms(1000);
}

// Functions for stepper motor
void setup_wheel(void)
{
	DDRC = 0xFF;
	rounds_per_Round = 360/(angle*8);
	round_length = (2*22/7*radius);
	angle_length =round_length/360*angle;
}

void wheel_Moving_front(void)
{	
	full_rounds = floor(move_length/round_length);
	balance_length = move_length - (full_rounds*round_length);
	angle_needed = floor(balance_length/angle_length);
	
	for (int i=0; i<full_rounds; i++)
	{
		for (int j=0; j<rounds_per_Round; j++)
		{
			move_round_front();
		}
	}
	move_angles_front(angle_needed);
}

void move_round_front(void)
{
	PORTC = 0x01;
	_delay_ms(period);
	PORTC = 0x05;
	_delay_ms(period);
	PORTC = 0x04;
	_delay_ms(period);
	PORTC = 0x06;
	_delay_ms(period);
	PORTC = 0x02;
	_delay_ms(period);
	PORTC = 0x0A;
	_delay_ms(period);
	PORTC = 0x08;
	_delay_ms(period);
	PORTC = 0x09;
	_delay_ms(period);
	PORTC = 0x01;
	_delay_ms(period);	
}

void move_angles_front(float angles)
{
	int i=0;
	if (angles>0)
	{
		while (1)
		{
			PORTC = 0x01;
			_delay_ms(period);
			PORTC = 0x05;
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x04;
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x06;
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x02;
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x0A;
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x08;
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x09;
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
			PORTC = 0x01;
			_delay_ms(period);
			i++;
			if (i>=angles)
			{
				break;
			}
		}
	}
}

// Functions of wifi Module

void usartinit()
{
	UBRRL = BAUD_PRESCALE;			/* Load lower 8-bits of the baud rate */
	UBRRH = (BAUD_PRESCALE >> 8);		/* Load upper 8-bits*/
	UCSRB|=(1<<RXEN)|(1<<TXEN);// enable trans and receive of data
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);//URSEL is register selector and other 11 set number of data bits 8 bits
}

void sendToUdr(char *str)// we write data to UDR AT commands
{
	for (int i=0; str[i]!='\0'; i++)
	{
		UDR = str[i];
		_delay_ms(100);
	}
}

void setWifiConnection(void)
{
	sendToUdr(wifiCmd1);
	_delay_ms(500);
	sendToUdr(wifiCmd2);
	_delay_ms(500);
	sendToUdr(wifiCmd3);
	_delay_ms(500);
	sendToUdr(wifiCmd4);
	_delay_ms(500);
	sendToUdr(wifiCmd5);
	_delay_ms(500);
	//getIPAdress();
	_delay_ms(500);
	sendToUdr(wifiCmd7);
	_delay_ms(500);
	//sendToUdr(wifiMassage);
}
void getIPAdress(void)
{
		while(!(UCSRA&(1<<RXC))){}
	sendToUdr(wifiCmd6);
	int counts=0;
	while(counts<10){
		IpAddress[counts]=rxvalue();
	}
	// IpAddress;
}
unsigned char rxvalue(void)
{
	while(UCSRA&(1<<RXC));
	{
		rxdata=UDR;
		return rxdata;
	}
}

void detectTeacher(void){
	lcd_write_word("Teacher");// Display "Teacher"
	_delay_us(20);
	lcd_goto_xy(1,0);
	lcd_clear();
	DoorOpen();
}

void tuteIssuingProcess(void){ 
	lcd_write_word("Take your Tute");  //Display " Paid Student", can issue a tutorial.
	_delay_us(20);
	lcd_goto_xy(1,0);
	lcd_clear();
	Green_LED();
	SERVO_CLOCKWISE();
	wheel_Moving_front();
	SERVO_ANTI_CLOCKWISE();
	while(1)
	{
		DC_Rotate();
		if(SENSE_IR_PORT & (1<<5))
		{
			DC_Stop();
			break;
		}
	}
}

void notREgistered(void){
		lcd_write_word("Not registered"); //Display "Not Registered"
		_delay_us(20);
		lcd_goto_xy(1,0);
		lcd_clear();		
}

void PIRdetect(void){
	while(1){
		if(PIR&0x40)  // check whether someone is cross the PIR
		{
			DoorClose(); //door close
			break;
		}
	}
}

void openDoorInside(void){
	if(SWITCH&0x80) // Check whether push the button or not
	{
		DoorOpen();
		_delay_ms(2000);
		DoorClose();
	}
}

void refillingSystem(void){
	ultra_triger();// ultrasonic sensor
	_delay_ms(15);
}


// RFID
char USART_RxChar()
/* Data receiving function */
{
	while (!(UCSRA & (1 << RXC)));
	/* Wait until new data receive */
	return(UDR);
	/* Get and return received data */
}


// Multiplexer
void enable_wifi(){
	// enable channel 0
	DDRD &=~(1<< input);
}
void disable_wifi(){
	// enable channel 2
	DDRD &=~(1<< input);
}