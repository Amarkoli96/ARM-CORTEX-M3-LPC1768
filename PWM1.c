	#include "usrdef.h"
	#include <lpc17xx.h>
	uint32_t  Pwidth = 10 , Pint =  18000 ;// 0.1ms/0.005us = 200000 
	void initTimer0(void);
	int main(void)
	{
		initTimer0();
		PinSelFunc(1,28,3);// selected MAT0.0 
		LPC_TIM0->MR0 =((Pwidth * Pint)/ 100);
		LPC_TIM0->TCR |= 0x01; //Reset Timer to 0 and enable timer
		while(1)
		{
		}
	}

	void initTimer0(void)
	{
			LPC_SC->PCONP |= (1<<1); //Power up TIM0. 
			LPC_SC->PCLKSEL0 &= ~(0x3<<2); //Set PCLK for timer = CCLK/4 = 72/4 = 18Mhz (default)
			LPC_TIM0->CTCR |= 0x0;// using timer mode
			LPC_TIM0->MCR |= 0x03;//when TC matchs with MR0 generate interrupt and reset TC
		  LPC_TIM0->EMR |= 0X03 << 4;//toggle pin when TC match with MR0
			LPC_TIM0->PR = 0; //Increment TC at every clock cycles at 18MHz
		//	LPC_TIM0->TCR |= 0x03; //Reset Timer to 0 and enable timer
			NVIC_EnableIRQ(TIMER0_IRQn);//enable timer 0 interrupt
	}
	
	
	void TIMER0_IRQHandler(void)
	{
		  LPC_TIM0->IR |= 1 << 0 ;// clear interrupt
			if((PinRead(1,28)) == 0)
			{
				LPC_TIM0->MR0 = (((100 - Pwidth) * Pint)/100);
			}
			else
			{
				LPC_TIM0->MR0 = ((Pwidth * Pint)/100);
			}
	}
		
		
