#ifndef _USART_H

#define _USART_H
#include "stdio.h"
#define USART_TX_GPIO_PORT GPIOA
#define USART_RX_GPIO_PORT GPIOA
#define USART_TX_GPIO_Pin   GPIO_Pin_9
#define USART_RX_GPIO_Pin   GPIO_Pin_10


#include "stm32f10x.h"
void USART_ADD(void);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
//void Usart_SendString( USART_TypeDef * pUSARTx, char *str);


#endif
