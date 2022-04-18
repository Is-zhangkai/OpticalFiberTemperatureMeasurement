#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

void usart_Init(void);
void USART1_Send_String(u8 *Data)   ;
void USART1_Send_String_By_Lens(u8 *Data, int Len);
void USART1_Send_Byte(u8 Data)    ;

#endif


