#include"LPC17xx.h"
#include"system_LPC17xx.h"
enum ePinFun  { FUNCTION0=0,FUNCTION1,FUNCTION2,FUNCTION3};
void PinSelFunc(uint8_t Port_number , uint8_t Pin_number,enum ePinFun pin_func);
enum ePinDir{INPUT = 0 , OUTPUT};
 

void EINT_Handler(void);
uint8_t EINTInit(void);
void PinDir(uint32_t PORT,uint32_t PIN ,uint8_t dir);
uint32_t PinWrite(uint32_t PORT,uint32_t PIN ,uint8_t sel);

int main(void)
{
                EINTInit();
                while(1);
}
 

 

uint8_t EINTInit(void)
{
                PinSelFunc(2,11,FUNCTION1);
                LPC_SC->EXTMODE = 0X02;
                LPC_SC->EXTPOLAR = 0X02;
                LPC_PINCON->PINMODE4 |= 3<<22;
//            LPC_GPIOINT->IO2IntEnF = 0x200;
                NVIC->ISER[0] = 0x01 << 19 ;
                //NVIC->ICPR[0] = 0x01 << 18 ;
//            LPC_SC->EXTINT = 1;
                return (0);
}
 

 

void EINT1_IRQHandler(void)
{
//            uint32_t i=892800;
                static uint8_t flag =0;
                LPC_SC->EXTINT = 2;//clear the interrupt
                if(flag)
                {
                                flag=0;
                                PinWrite(1,29,0);
                }
                else
                {
                                flag=1;
                                PinWrite(1,29,1);
                }
                PinDir(1,29,OUTPUT);
               
//            while(i--);
//            PinWrite(1,29,1);
}             
 

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
                                                uint32_t *portaddr = (uint32_t*)(LPC_PINCON_BASE + 0x04 + 8*Port_number);
                                                *portaddr = *(portaddr ) | (0x00 << (Pin_number - 16)*2);
                                                *portaddr = *(portaddr) | (pin_func << (Pin_number - 16)*2);
                                }
}             
 

 

void PinDir(uint32_t PORT,uint32_t PIN ,uint8_t dir)
{
                   uint32_t *portaddr = (uint32_t*)(LPC_GPIO0_BASE + 0x20 * PORT);
                                if(dir == 1)
                                {
                                                  *portaddr = (*portaddr) | (1 << PIN);
                                               
                                }
                  else
                                {
                                                *portaddr = (*portaddr) & ~(1 << PIN);
                                               
                                }
                               
}             
 

uint32_t PinWrite(uint32_t PORT,uint32_t PIN ,uint8_t sel)
{
                   uint32_t *portaddr = (uint32_t*)(LPC_GPIO0_BASE +0x14 + 0x20 * PORT);
                                if(sel == 1)
                                {
                                                *portaddr = (*portaddr) | (1 << PIN);
                                                                return 1;
                                }
                  else
                                {
                                                *portaddr = (*portaddr) & ~(1 << PIN);
                                                                return 0;
                                }
                               
}             
