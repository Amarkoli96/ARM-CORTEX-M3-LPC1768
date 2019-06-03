#include "system_LPC17xx.h"
#include "lpc17xx.h"
//#include "type.h"
/*
#define SBIT_PDN      21u
#define SBIT_CLKDIV   8u
#define SBIT_START    24u
#define SBIT_EDGE     27u
#define SBIT_DONE     31u
#define SBIT_RESULT   4u
//#define GET_status(x,bit) ((x & bit)!=0u)



void delay(void)
{
	uint32_t i = 8968;
	while(i--);
}

int main()
{
uint32_t adc_result;

LPC_SC->PCONP |=(0x1<<12);

LPC_ADC->ADCR =(0x1<<SBIT_PDN) | (0x10<<SBIT_CLKDIV);

LPC_PINCON->PINSEL1= (0x01<<14);
LPC_PINCON->PINMODE1= (0x02<<14);

	while(1)
	{
		//uint32_t adc_result;
		LPC_ADC->ADCR |= 0x01;
//		delay();
		LPC_ADC->ADCR |= (1<<SBIT_START);
		while((LPC_ADC->ADGDR & (0x1<<SBIT_DONE))!=0);
		//while(GET_status(LPC_ADC->ADGDR,SBIT_DONE)==0);
		adc_result= (LPC_ADC->ADGDR >> SBIT_RESULT)& 0xffff;
	}


}*/
uint32_t adc_result;
int main()
{
uint32_t i;
LPC_SC->PCONP |=(0x1<<12);
LPC_ADC->ADCR =(0x1<<21) | (0x2<<8);
LPC_PINCON->PINSEL1= 0x00004000;
LPC_PINCON->PINMODE1 |= 0x2 << 14; 
	while(1)
	{
		LPC_ADC->ADCR |= 1<<24;//Start the ADC conversion

		do
		{
				i = LPC_ADC->ADGDR;
		}
		while((i & 0x80000000) == 0 );
		adc_result = ( i >> 6 ) & 0x3FF;
	}
}
