	#include "system_LPC17xx.h"
	#include "LPC17xx.h"
   uint32_t* portaddr;
	 uint32_t PinRead(uint32_t portno,uint32_t pinno)
	 {
		 portaddr = (uint32_t*)(LPC_GPIO0_BASE+0x14 + 0x20 * portno);
		 uint32_t ret_val;
		 ret_val = (*portaddr >> pinno) & 0x01 ;
		 return ret_val;
		 
	 }
	 int main(void)
		{
			uint32_t k;
			SystemInit();
			LPC_GPIO1->FIODIR = LPC_GPIO1->FIODIR | 1 << 29;
			
			  
			while(1)
			{
				k = PinRead(2,11);
				
				if(k==0x1)
				{	
					LPC_GPIO1->FIOSET = LPC_GPIO1->FIOSET | 1<<29;
				
				}
				else
				{
						LPC_GPIO1->FIOCLR = LPC_GPIO1->FIOCLR | 1<<29;
				
				}

			}
			return 0;
					
		}
		