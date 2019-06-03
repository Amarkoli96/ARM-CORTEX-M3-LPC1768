#include "system_LPC17xx.h"
#include "LPC17xx.h"

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
enum ePinDir{INPUT = 0 , OUTPUT};
int main (void)
{	    		

  
  SystemClockUpdate();
  PinDir(2,11,INPUT);
  LPC_GPIO1->FIODIR = LPC_GPIO1->FIODIR | 1 << 29;
  while(1)
  {
	  	if((0x01<<11) & LPC_GPIO2->FIOPIN )
		{	
			LPC_GPIO1->FIOSET = LPC_GPIO1->FIOSET | 1<<29;
		}
		else
		{
				LPC_GPIO1->FIOCLR = LPC_GPIO1->FIOCLR | 1<<29;
    }

  }
}
