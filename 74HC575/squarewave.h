	#include "system_LPC17xx.h"
	#include "LPC17xx.h"
	enum eSTATE { LOW=0,HIGH};
	enum ePinDir { INPUT = 0 , OUTPUT};
	enum ePinFun { FUNCTION0=0,FUNCTION1,FUNCTION2,FUNCTION3};
	
	
	void PinWrite(uint8_t PORT,uint8_t PIN ,uint8_t sel);
	void PinDir(uint8_t PORT,uint8_t PIN ,uint8_t dir);
	void PinSelFunc(uint8_t Port_number , uint8_t Pin_number,uint8_t pin_func);
	void clock(enum eSTATE choice);
	void pull_latch(enum eSTATE choice);
	void bit_write(uint8_t* data);
	void serial_write(uint8_t data);

		void PinWrite(uint8_t PORT,uint8_t PIN ,enum eSTATE choice)
	{	
		uint32_t *portaddr = (uint32_t*)(LPC_GPIO0_BASE +0x14 + 0x20 * PORT);
		if(choice == HIGH)
		{
			*portaddr = (*portaddr) | (1 << PIN);
	  }
		else
		{
		    *portaddr = (*portaddr) & ~(1 << PIN);
		}
	
	}	

	void PinDir(uint8_t PORT,uint8_t PIN ,enum ePinDir Dir)
	{
		uint32_t *portaddr = (uint32_t*)(LPC_GPIO0_BASE + 0x20 * PORT);
		if(Dir == OUTPUT)
		{
			*portaddr = (*portaddr) | (1 << PIN);
	    }
		else
		{
		    *portaddr = (*portaddr) & ~(1 << PIN);
		}	
	}

	void PinSelFunc(uint8_t Port_number , uint8_t Pin_number, uint8_t pin_func)
	{
		uint32_t *portaddr = (uint32_t*)(LPC_PINCON_BASE + 8*Port_number);
		if(Pin_number > 15)
		{
			portaddr += 4;
			Pin_number -= 16;
		}
		*portaddr = *(portaddr) & ~(0x3 << (Pin_number*2));
		*portaddr = *(portaddr) | (pin_func << Pin_number*2);
	}
	
