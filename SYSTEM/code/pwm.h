#ifndef __PWM_H
#define __PWM_H
#include "sys.h"



void TIM3_PWM_Init(u16 arr,u16 psc);
void moter_tRight(void);
void moter_tLeft(void);
void moter_straight(void);
void moter_stop(void);

#endif

