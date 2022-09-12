#include "ultra_buzzer.h"
#define Buzzer_pin PIND7
/**************************
       variables
**************************/	   
uint8_t sensor_working=0;
uint8_t rising_edge=0;
uint32_t timer_counter=0;
uint32_t distance;
uint8_t distance_str[10];
/***********************
Ultrasonic functions
***********************/
void ultrasonic_init(void){

	TRIGER_DDR|=(1<<TRIGER);
	ECHO_DDR&=~(1<<ECHO);
	ECHO_PULLUP|=(1<<ECHO);
	enable_ex_interrupt();
	timer0_init();
	return;
}

void enable_ex_interrupt(void){

	MCUCR |= (1<<ISC10);		// Trigger INT1 on any logic change.
	GICR  |= (1<<INT1);			// Enable INT1 interrupts.

	return;
}

void ultra_triger(void){
	if(!sensor_working){
		TRIGER_PORT|=(1<<TRIGER);
		_delay_us(15);
		TRIGER_PORT&=~(1<<TRIGER);
		sensor_working=1;
	}
}

ISR(INT1_vect){
	if(sensor_working==1){
		if(rising_edge==0){
			TCNT0=0x00;
			rising_edge=1;
			timer_counter=0;
		}
		else{
			distance=(timer_counter*256+TCNT0)/466;
			//lcd_goto_xy(1,0);
			//itoa(distance,distance_str,10);
			//strcat(distance_str, " cm ");
			//lcd_write_word(distance_str);
			_delay_ms(40);
			if (distance>=25)
			{
				buzzer_alarm(100);
			}
			timer_counter=0;
			rising_edge=0;
		}
	}}

	ISR(TIMER0_OVF_vect){
		timer_counter++;
		if(timer_counter >730){
			TCNT0=0x00;
			sensor_working=0;
			rising_edge=0;
			timer_counter=0;
		}
	}
/*********************
       TIMER
*********************/	   	
	void timer0_init(void)
	{
		
		TCCR0 = DISABLE_MODULE_VALUE;// Disable Timer 0 
		TCCR0 = (PRESCLR1_VALUE);// Setting pre-scaler 
		TCNT0 = ZER0_INITIALIZER;// Initializing the timer with zero 
		TIMSK |=(1<<TOIE0);// Timer overflow interrupt enable

		return;
	}
/***********************
        buzzer
************************/		
void buzzer_int(void)
{
	DDRD |= 1<< Buzzer_pin;
}
void buzzer_alarm(int ms)
{
	for(int i=0;i<ms;i++)
	{
		PORTD |= (1<< Buzzer_pin);
		_delay_ms(2);
		PORTD &=~(1<< Buzzer_pin);
		_delay_ms(2);
	}
}
