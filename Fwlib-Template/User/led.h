#ifndef _LED_H

#define _LED_H

#include "stm32f10x.h"

#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态

#define LED1_TOGGLE		  digitalToggle(GPIOE,GPIO_Pin_5)
#define LED1_OFF		   digitalHi(GPIOE,GPIO_Pin_5)
#define LED1_ON			   digitalLo(GPIOE,GPIO_Pin_5)


void LED_GPIO_Config(void);







#endif

