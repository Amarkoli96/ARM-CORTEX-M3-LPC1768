	#include "system_LPC17xx.h"
	#include "LPC17xx.h"
	
	enum ePinDir  { PULLUP=0,REPEATER,NOTHING,PULLDOWN};
	
void PinMode(uint8_t Port_number, uint8_t Pin_number, enum ePinDir pin_dir)
{
	   uint32_t *portaddr = (uint32_t*)(LPC_PINCON_BASE + 0x40 + 8 * Port_number);
		 if(Pin_number <= 15)
		 {
			*portaddr = *(portaddr ) | (0x0 << Pin_number*2);
			*portaddr = *(portaddr ) | (pin_dir << Pin_number*2);
		 }
	  else
		{
			 *portaddr = *(portaddr ) | (0x0 << (Pin_number - 16)*2);
			 *portaddr = *(portaddr ) | (pin_dir << (Pin_number - 16)*2);
		}
		
}	

int main (void)
{  
  SystemInit();

	PinMode(0,0,2);

}
