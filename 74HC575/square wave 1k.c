#include "squarewave.h"
void PinWrite(uint32_t PORT,uint32_t PIN ,uint8_t sel)
{
	   uint32_t *portaddr = (uint32_t*)(LPC_GPIO0_BASE +0x14 + 0x20 * PORT);
		 if(sel == 1)
		 {
			 *portaddr = (*portaddr) | (1 << PIN);
		 }
	  else
		{
			 *portaddr = (*portaddr) & ~(1 << PIN);
		}
		
}	

enum ePinDir{INPUT = 0 , OUTPUT};
void PinDir(uint32_t PORT,uint32_t PIN ,uint8_t dir)
{
	   uint32_t *portaddr = (uint32_t*)(LPC_GPIO0_BASE + 0x20 * PORT);
		 if(dir == 1)
		 {
			  *portaddr = (*portaddr) | (1 << PIN);
			
		 }
	  else
		{
			 *portaddr = (*portaddr) & ~(1 << PIN);
			
		}
		
}

enum ePinFun  { FUNCTION0=0,FUNCTION1,FUNCTION2,FUNCTION3};


void PinSelFunc(uint8_t Port_number , uint8_t Pin_number, uint8_t pin_func)
{
	   uint32_t *portaddr = (uint32_t*)(LPC_PINCON_BASE + 8*Port_number);
		 if(Pin_number <= 15)
		 {
			*portaddr = *(portaddr) | (0x0 << (Pin_number*2));
			*portaddr = *(portaddr) | (pin_func << Pin_number*2);
		 }
	  else
		{
			 *portaddr = *(portaddr ) | (0x00 << (Pin_number - 16)*2);
			 *portaddr = *(portaddr) | (pin_func << (Pin_number - 16)*2);
		}
}	


uint32_t main (void)
{	    		
	
  uint32_t i=2;
  SystemInit();
  
  PinSelFunc(1,29,0);
  PinDir(1,29,OUTPUT);
  
   while(1)
  {
		i=8928;
		LPC_GPIO1->FIOSET |= 1<<29;
		while(i--);
	  LPC_GPIO1->FIOCLR  |= 1<<29;
		i=8928;
		while(i--);
  }
}
