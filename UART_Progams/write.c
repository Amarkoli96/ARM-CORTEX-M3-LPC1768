#include "LPC17xx.h"
#include "system_LPC17xx.h"

void UART0int(void);

int main()
{
	SystemInit();
	UART0int();
	static uint32_t i=0;
	uint8_t s[]="ABCDEFGHI";
	while(1)
	{
		while((LPC_UART0->LSR & 0x20) == 0x20)
		{

			if(i<10)
				{
				LPC_UART0->THR=s[i];
				i++;
				}
				/*else // uncomment this for continous priinting of the data in serial monitor
					{
						i=0;
						break;
					}*/
			}
		}
	}
void UART0int(void)
{
	LPC_SC->PCONP |= (1 << 3);			 //power on the uart0 module
	//LPC_SC->PCLKSEL0 |= (3 << 6);		 //pclk=cclk/8  ie 9MHz
	LPC_PINCON->PINSEL0 |= (1 << 4); 	//TXD0 as P0.2 pin
	LPC_PINCON->PINSEL0 |= (1 << 6); 	//RXD0 as P0.3 pin
	
	LPC_UART0->LCR |=(1 << 7);				//Enable access to Divisor Latches.
	LPC_UART0->LCR |=(3 << 0);				//Word Length Select 8-bit character length
	/*LPC_UART0->FDR |=(0 << 0);				//Baud-rate generation pre-scaler divisor value
	LPC_UART0->FDR =(1 << 4);			//Baud-rate pre-scaler multiplier value*/
	LPC_UART0->FDR = 0x10;
	
	LPC_UART0->DLL = 117;							//DLLSB estimated using the algorithm
	LPC_UART0->DLM =0x0;
	LPC_UART0->FCR = 0x07;				/* 0 bit FIFO enable,1 bit Rx fifo enable,2 bit Tx Fifo Enable*/
	LPC_UART0->LCR &=~(1 << 7);				//Dis-able access to Divisor Latches.
}

