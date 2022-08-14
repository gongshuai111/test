#ifndef _SPI_H

#define _SPI_H  
#include "stm32f10x.h"
void NRF24L01_Init(void);
uint8_t  SPI_NRF24L01_READ_Write(uint8_t data);
#define NRF24L01_GPIO_CE      GPIO_Pin_3
#define NRF24L01_GPIO_CSN     GPIO_Pin_4

#define NRF24L01_GPIO_IRQ     GPIO_Pin_1
#define  CSN_HIGH             GPIO_SetBits(GPIOA,NRF24L01_GPIO_CSN)//将片选线拉高
#define  CSN_LOW              GPIO_ResetBits(GPIOA,NRF24L01_GPIO_CSN)//将片选线拉高

#define  CE_HIGH              GPIO_SetBits(GPIOA,NRF24L01_GPIO_CE)//将片选线拉高
#define  CE_LOW               GPIO_ResetBits(GPIOA,NRF24L01_GPIO_CE)//将片选线拉高

uint8_t  SPI_NRF24L01_READ_Write(uint8_t data);
#endif



