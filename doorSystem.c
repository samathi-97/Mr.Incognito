

#include "doorSystem.h"
#include "LCD.h"



void DoorOpen(void) //function  definition of Dooropen

{
	DATA_BUS =0x08;
	_delay_ms(100);
	DATA_BUS =0x02;
	_delay_ms(100);
	DATA_BUS =0x04;
	_delay_ms(100);
	DATA_BUS =0x01;
	_delay_ms(100);
}
void DoorClose(void) // function definition of Doorclose
{
	DATA_BUS =0x04;
	_delay_ms(100);
	DATA_BUS =0x02;
	_delay_ms(100);
	DATA_BUS =0x08;
	_delay_ms(100);
	DATA_BUS =0x01;
	_delay_ms(500);
}
