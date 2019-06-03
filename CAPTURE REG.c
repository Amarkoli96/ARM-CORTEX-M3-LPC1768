  #include "usrdef.h"
	#include <lpc17xx.h>
	uint32_t  Pwidth = 0 , Pint =  0 ,Low_Count = 0 , High_Count =  0, A = 0 , B = 0;
	void initTimer0(void);
	int main(void)
	{
		initTimer0();
		PinDir(1,29,OUTPUT);
		PinSelFunc(1,26,3);//selected CAP0.0
		LPC_TIM0->TCR |= 0x03; //Reset Timer to 0 and enable timer
		while(1)
		{
			Pwidth = (((High_Count)/(High_Count + Low_Count)) * 100 );
			Pint = A + B ;
		}
	}

	void initTimer0(void)
	{
			LPC_SC->PCONP |= (1<<1); //Power up TIM0. 
			LPC_SC->PCLKSEL0 &= ~(0x3<<2); //Set PCLK for timer = CCLK/4 = 72/4 = 18Mhz (default)
			LPC_TIM0->CTCR |= 0x0;// using timer mode
			LPC_TIM0->PR |= 0; //Increment TC at every clock cycles at 18MHz
			LPC_TIM0->TCR |= 0x03; //Reset Timer to 0 and enable timer
		  LPC_TIM0->CCR |= 1 << 0 | 1 << 1 | 1<< 2; 
			NVIC_EnableIRQ(TIMER0_IRQn);//enable timer 0 interrupt
	}
	
	
	void TIMER0_IRQHandler(void)
	{
		  LPC_TIM0->IR |= 1 << 4 ;// clear interrupt
			if((PinRead(1,26)) == 0)
			{
				  //PinWrite(1,29,1);
					B = LPC_TIM0->CR0; 
					High_Count = LPC_TIM0->CR0 - A ;  
			}
			else
			{
				  //PinWrite(1,29,0);
					A = LPC_TIM0->CR0;
					Low_Count = LPC_TIM0->CR0 - B ; 
			}
	}
	