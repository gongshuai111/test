#ifndef _LED_H

#define _LED_H

#include "stm32f10x.h"

#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬

#define LED1_TOGGLE		  digitalToggle(GPIOE,GPIO_Pin_5)
#define LED1_OFF		   digitalHi(GPIOE,GPIO_Pin_5)
#define LED1_ON			   digitalLo(GPIOE,GPIO_Pin_5)


void LED_GPIO_Config(void);







#endif

