/*---including header file--------*/
#include "system_LPC17xx.h"
#include "LPC17xx.h"

/*---------function proto type--------*/
void SerialWrite(uint32_t Uart_no,uint8_t *p);
void Uart_Config(uint32_t Uart_no,uint32_t Baud_rate);
	
/*------------execution begins from the main -----------*/
int main()
{
	SystemInit();
	uint8_t string[100]="hi";
	Uart_Config(0,9600);
	SerialWrite(0,string);
}



void Uart_Config(uint32_t Uart_no,uint32_t Baud_rate)
{
	
	
	
}

void SerialWrite(uint32_t Uart_no,uint8_t *p)
{
	if(Uart_no == 0)
	{
	}
	else if(Uart_no == 1)
	{
	}
	else if(Uart_no == 2)
	{
	}
	else if(Uart_no == 3)
	{
	}
	else
	{
		/*---Do nothing-----*/
	}
}

/*---------EOF(end of the file)-------*/
