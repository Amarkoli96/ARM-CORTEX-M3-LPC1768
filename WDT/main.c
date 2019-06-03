#include"LPC17xx.h"
#include"system_LPC17xx.h"
void watch_dog_inti(void)
{
	LPC_WDT->WDCLKSEL=LPC_WDT->WDCLKSEL | 1<<0;
	LPC_WDT->WDMOD=0x3;
	LPC_WDT->WDTC=0xDD36B;
	LPC_WDT->WDFEED=0xAA;
	LPC_WDT->WDFEED=0x55;
	}

	void short_delay(void)//this function gives me 0.5ms delay at cclk[cpu clock 72MHz]
{
	int i=8928;
	while(i--);
}

int main()
{
	SystemInit();
	watch_dog_inti(); //system clock initilization
	
	LPC_GPIO2->FIODIR=LPC_GPIO2->FIODIR | 1<<0;  //Port two pin zero
	LPC_GPIO2->FIOSET=LPC_GPIO2->FIOSET | 1<<0;  //Port two pin zero is made to HIGH
	short_delay();
	
	LPC_GPIO2->FIOCLR=LPC_GPIO2->FIOCLR | 1<<0;
	while(1);
}
