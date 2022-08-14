#include "usart.h"
#include "stdio.h"
extern int g_USART_FLAG;
//static void NVIC_Configuration(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	
//}
static void usart_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = USART_TX_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_GPIO_PORT,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin =USART_RX_GPIO_Pin;
	GPIO_Init(USART_RX_GPIO_PORT,&GPIO_InitStructure);
}

static void USART_Config(void)
{
	
	USART_InitTypeDef   USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	
	USART_InitStructure.USART_Mode=USART_Mode_Rx  |USART_Mode_Tx ;
	USART_InitStructure.USART_Parity=USART_Parity_No;//ะฃั้
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1 ,&USART_InitStructure);
//	NVIC_Configuration();
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1,ENABLE);
	
	
	
}
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx,ch);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	
}
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
	do {
		Usart_SendByte( USART1, *(str + k) );
		k++;
		} while (*(str + k)!='\0');
	while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET) {
	}
}
void USART_ADD(void)
{
	usart_GPIO_Config();
	USART_Config();

	
	
	
}
//void USART1_IRQHandler(void)
//{
//	
//	uint8_t ucTemp;
//	if (USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
//		{
//			ucTemp = USART_ReceiveData( USART1 );
//		 if(ucTemp=='A')g_USART_FLAG=1;
//		 if(ucTemp=='B')g_USART_FLAG=2;
//	 	 if(ucTemp=='C')g_USART_FLAG=3;
//		}
//	
//}
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return (ch);
	
}
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(USART1);
	
	
}
