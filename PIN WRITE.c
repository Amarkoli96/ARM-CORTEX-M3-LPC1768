	#include "system_LPC17xx.h"
	#include "LPC17xx.h"
	
	
	
	
	
uint32_t PinWrite(uint32_t PORT,uint32_t PIN ,uint8_t sel)
{
	   uint32_t *portaddr = (uint32_t*)(LPC_GPIO0_BASE +0x14 + 0x20 * PORT);
		 if(sel == 1)
		 {
			 *portaddr = (*portaddr) | (1 << PIN);
				return 1;
		 }
	  else
		{
			 *portaddr = (*portaddr) & ~(1 << PIN);
				return 0;
		}
		
}	



int main (void)
{  int j,k;
  SystemInit();
	LPC_GPIO1->FIODIR = LPC_GPIO1->FIODIR | 1 << 29;
	LPC_GPIO2->FIODIR = LPC_GPIO1->FIODIR | 1 << 11;
  k=PinWrite(2,11,1);
 
  while(1)
  {
	  	if(k == 1)
		{	
			LPC_GPIO1->FIOSET = LPC_GPIO1->FIOSET | 1<<29;
		}
		else
		{
				LPC_GPIO1->FIOCLR = LPC_GPIO1->FIOCLR | 1<<29;
    }

  }
}
