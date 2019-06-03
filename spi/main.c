#include"LPC17xx.h"
#include"system_LPC17xx.h"

void SPIint(void);
void pinsel(void);
void spiconfig(void);

int main()
{
	SystemInit();
	SPIint();
	pinsel();
	spiconfig();
	while(1)
		{
			LPC_SPI->SPDR =0xaa;								//the data 0xAA is transfering
			while(!(((LPC_SPI->SPSR) >> 7) & 1));
			LPC_SPI->SPDR =0xaa;
			
		}
	
	
}
void SPIint(void)
{
	LPC_SC->PCONP |= (1 << 8);				//to power on the SPI block
	LPC_SC->PCLKSEL0 &=~(0x03 << 16);		//to select the pclk as cclk/4 that is 18MHz(pclk)
	LPC_SPI->SPCCR =0x12;								//to select the counter value to 18 ie pre scaler then we will get 1Mb/s transfer rate
}
void pinsel(void)
{
		LPC_PINCON->PINSEL0 |=(0x3 << 30);	//Selecting the pin P0.15 as function SCK
	LPC_GPIO0->FIODIR |=(1 << 15);			//selecting p0.15 as output
	
	LPC_PINCON->PINSEL1 |=(0x3 << 0);   //SSEL
	LPC_GPIO0->FIODIR |=(1 << 16);			//selecting p0.15 as output
	
	LPC_PINCON->PINSEL1 |=(0x3 << 2);		//MISO
	LPC_GPIO0->FIODIR |=(0 << 17);			//selecting p0.15 as input
	
	LPC_PINCON->PINSEL1 |=(0x3 << 4);   //MOSI data is transfered through this pin
	LPC_GPIO0->FIODIR |=(1 << 18);			//selecting p0.15 as output
}
void spiconfig(void)
{
	LPC_SPI->SPCR |=(1 << 2);						//SPI controller sends and recives 8bits dat per transfer
	LPC_SPI->SPCR &=~(1 << 3);					//data is samlped on the first clock edge of sck
	LPC_SPI->SPCR &=~(1 << 4);					//clock polarity control
	LPC_SPI->SPCR &=~(1 << 5);					//SPI is in master mode
	LPC_SPI->SPCR |=(1 << 6);						//SPI data is transferred MSB (bit 7) first.
	
}
