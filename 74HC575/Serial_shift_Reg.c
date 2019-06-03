	#include "squarewave.h"
	
			


	void delay(void)
	{
		uint32_t i=8928;//it will generate 0.5ms of delay for one call
		while(i--);
	}


	void clock(enum eSTATE choice)
	{
		if(choice == HIGH)
		{
			PinWrite(1,29,HIGH);
		}
		else
		{
			PinWrite(1,29,LOW);
		}
	}

	void pull_latch(enum eSTATE choice)
	{
		if(choice == HIGH)
		{
			PinWrite(1,27,HIGH);
		}
		else
		{
			PinWrite(1,27,LOW);
		}  
	}
	
	void bit_write(uint8_t* data)
	{
		PinWrite(1,28,(*data & 0x01));
		*data = *data >> 1;
	}

		void serial_write(uint8_t data) 
	{
		  uint8_t count=8;
	    while(count) 
	    {
				bit_write(&data); // port 1 pin 28 for data (DATA)
				clock(HIGH);//port 1 pin 29 for serial clock	(SRCLK)			
				delay();// 0.5ms time period 
				clock(LOW);
				delay();
				count--;
			}
		  pull_latch(HIGH);//port 1 pin 27 for latch(RCLK)
		  delay();
		  pull_latch(LOW);
	}
	  
	  
	int main (void)
	{
		SystemInit();
		
		PinSelFunc(1,29,FUNCTION0);
		PinDir(1,29,OUTPUT);
		
		PinSelFunc(1,28,FUNCTION0);
		PinDir(1,28,OUTPUT);
		
		PinSelFunc(1,27,FUNCTION0);
		PinDir(1,27,OUTPUT);
		
		while(1)
		{
				serial_write(0xaa);
		}
	}
