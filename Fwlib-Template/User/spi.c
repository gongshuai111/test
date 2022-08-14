#include "spi.h"
static void NRF24L01_SPI_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1,ENABLE);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	SPI_InitStruct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;//9M
	SPI_InitStruct.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_CPOL=SPI_CPOL_Low;
	SPI_InitStruct.SPI_CRCPolynomial=7;
	SPI_InitStruct.SPI_DataSize=SPI_DataSize_8b;
	SPI_InitStruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_Mode=SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS=SPI_NSS_Soft;
	SPI_Init(SPI1, &SPI_InitStruct);
    SPI_Cmd(SPI1, ENABLE);
	
	
	
	
}
void NRF24L01_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// CE CSN Initialize
	GPIO_InitStruct.GPIO_Pin = NRF24L01_GPIO_CE | NRF24L01_GPIO_CSN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA , &GPIO_InitStruct);
	
	// IRQ Initialize
	GPIO_InitStruct.GPIO_Pin = NRF24L01_GPIO_IRQ;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
	NRF24L01_SPI_Init();
	 CSN_HIGH;//将片选线拉高
	 CE_LOW;
	
	
}
//读写函数，基本操作
uint8_t  SPI_NRF24L01_READ_Write(uint8_t data)
{
		    while(SPI_I2S_GetFlagStatus(SPI1 ,SPI_I2S_FLAG_TXE)==RESET );
			  SPI_I2S_SendData(SPI1,data);

	      while(SPI_I2S_GetFlagStatus(SPI1 ,SPI_I2S_FLAG_RXNE)==RESET);
	      return SPI_I2S_ReceiveData(SPI1);
}
//读 寄存器函数


