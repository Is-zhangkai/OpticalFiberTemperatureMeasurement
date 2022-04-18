#include "stm32f10x.h"
#include "GPIO.h"
#include "delay.h"
#include "pwm.h"
#include "usart.h"
#include "stm32f10x.h"
#include "OLED.h"
#include "adc.h"


 void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }
 int main(void)
 {	
	 
	 
	 	u16 adcx;
	 short te; 
	float temp;
 	u8 t=0;	 
	 char str[5];
	 OLED_Init();
	 gpio_Init();
	 delay_init();	
	 usart_Init();
	 Adc_Init();	
	 TIM3_PWM_Init(400,71);	 //ADC初始化
	OLED_Clear();
	  OLED_ShowString(2 , 1 , "hello zhangkai!");
	  
  while(1)
	{
		
		
		delay_ms(100);
		
		adcx=Get_Adc(ADC_Channel_1);		//得到ADC转换值	  
		//	temp=(float)adcx*(3.3/4096);			//得到ADC电压值
		// te=Get_Temprate();
		//sprintf(str, "%.2f",(float )adcx );
		
		temp=(float)adcx *(3.3/4096);
		sprintf(str, "%.2f",temp );
		OLED_ShowString(1,1,str);
		

		


   
	}
	


	
 }
 
