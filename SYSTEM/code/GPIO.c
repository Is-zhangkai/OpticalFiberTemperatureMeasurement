#include "GPIO.h"
#include "delay.h"

void gpio_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_Init(GPIOC, &GPIO_InitStructure);		
	
	
}
void led13(void)		
{
	 delay_ms(500);
    GPIO_SetBits(GPIOC,GPIO_Pin_13);
    delay_ms(500);
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}
