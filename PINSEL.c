#include "system_LPC17xx.h"
#include "LPC17xx.h"
	
enum ePinFun  { FUNCTION0=0,FUNCTION1,FUNCTION2,FUNCTION3};

void PinSelFunc(uint8_t Port_number , uint8_t Pin_number,enum ePinFun pin_func)
{
	  
		 if(Pin_number <= 15)
		 {
			 uint32_t *portaddr = (uint32_t*)(LPC_PINCON_BASE + 8*Port_number);
			*portaddr = *(portaddr) | (0x0 << (Pin_number*2));
			*portaddr = *(portaddr) | (pin_func << Pin_number*2);
		 }
	  else
		{
			Pin_number -=16;
			 uint32_t *portaddr = (uint32_t*)(LPC_PINCON_BASE + 0x04 + 8*Port_number);
			 *portaddr = *(portaddr ) | (0x00 << (Pin_number)*2);
			 *portaddr = *(portaddr) | (pin_func << (Pin_number)*2);
		}
}	

int main (void)
{  
  SystemInit();
	//LPC_GPIO1->FIODIR = LPC_GPIO1->FIODIR | 1 << 29;
	LPC_GPIO1->FIODIR |= 1<<29;
	PinSelFunc(0,23,2);
 /*
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
	*/
}
