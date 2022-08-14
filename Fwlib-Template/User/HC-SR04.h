#ifndef _HCSR04_H

#define _HCSR04_H

#include "stm32f10x.h" 

void TIM4_Cap_Init(u16 arr,u16 psc);
void HCSR04_TRIG_Init(void);
void HCSR04_TRIG_Send(void);
float HCSR04(void);
#endif


