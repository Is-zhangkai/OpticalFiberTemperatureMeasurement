
#include "stm32f10x.h"
#include "usart.h"
#include "string.h"
#include "pwm.h"
#include "OLED.h"
void usart_Init(void)
{
    USART_DeInit(USART1);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);	//开启时钟
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
	
	//初始化GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
    
	
	
	//初始化串口
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;	//波特率
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//读写模式
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
    USART_InitStruct.USART_Parity = USART_Parity_No;	//无奇偶校验位
    USART_InitStruct.USART_StopBits = USART_StopBits_1;	//一个停止位
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;    //字长8位数据格式
    USART_Init(USART1,&USART_InitStruct);		//初始化串口
    
    USART_Cmd(USART1,ENABLE);		//使能串口


//设置中断
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);

    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

   

}

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
    {
		 uint8_t Res;
		 USART_ClearITPendingBit(USART1,USART_IT_RXNE); 
		//   USART_ReceiveData(USART1);//读取数据注意：这句必须要，否则不能够清除中断标志位。
		 
		  Res =USART_ReceiveData(USART1);
		  char str1[5];
		 sprintf(str1, "%.2f",(float )Res );
		   OLED_ShowString(2 , 1 ,str1);
		 if(Res=='1'){
			   
			 moter_tLeft();
		   
		 }
		  if(Res=='2'){
			   
			 moter_tRight();
		   
		 }
		   if(Res=='0'){
			   
			moter_straight();
		   
		 }
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除中断
    }
}





void USART1_Send_Byte(u8 Data)                     
{
    USART_GetFlagStatus(USART1, USART_FLAG_TC);
    USART_SendData(USART1,Data);
    while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
}


//发送字符串，遇到字符串结尾标志'\0'结束
void USART1_Send_String(u8 *Data)                 
{
    while(*Data)
        USART1_Send_Byte(*Data++);
}


//按长度发送字符串，这种方法可以发送含0x00的字符串
void USART1_Send_String_By_Lens(u8 *Data, int Len)
{
    int i;
    for(i=0; i<Len; i++)
    {
        USART_SendData(USART1, Data[i]);          
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);      //串口1发送数据
    }
}






//接收完数据之后，在main函数中对接收到的数据进行处理。
/*
if(USART_RX_STA&0x8000)
{
    //得到此次接收到的数据长度，即USART_RX_BUF数组中的有效数据长度
    uart1Len=USART_RX_STA&0x3f;                   
 
    //对接收到的数据进行数据处理，接收的数据暂存在USART_RX_BUF数组中   
    //... ... 
 
    USART_RX_STA=0;   
    memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF));        //清空数组  
}
*/

