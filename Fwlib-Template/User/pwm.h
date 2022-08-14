#ifndef _PWM_H

#define _PWM_H                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
#include "stm32f10x.h"

#define Duoji_PWM_TIM  TIM3
#define Duoji_CLK RCC_APB1Periph_TIM3 
#define Duoji_PWM_PORT GPIOA	
#define Duoji_PWM_Pin GPIO_Pin_2	

#define   SG90_Right_90     TIM_SetCompare1(TIM3, 32)	
//#define   SG90_Right_45		TIM_SetCompare4(TIM3, 10)		
#define   SG90_Front		TIM_SetCompare1(TIM3, 70)		
//#define   SG90_Left_45		TIM_SetCompare4(TIM3, 20)		
#define   SG90_Left_90		TIM_SetCompare1(TIM3, 100)
 void Duoji_PWM_Config(u16 arr,u16 psc);

#endif
