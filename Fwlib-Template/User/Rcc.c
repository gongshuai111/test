#include "Rcc.h"
void Set_HSE(uint32_t RCC_PLLMul_x)
{
			 
			ErrorStatus HSEStatus;
			RCC_DeInit();
	    RCC_HSEConfig(RCC_HSE_ON);
	   HSEStatus = RCC_WaitForHSEStartUp();
				if(HSEStatus ==SUCCESS)
				{
								FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//ʹ��Ԥȡֹ
				       	FLASH_SetLatency(FLASH_Latency_2);
					
							// ���ø������ߵķ�Ƶ����
								 RCC_HCLKConfig(RCC_SYSCLK_Div1);
								 RCC_PCLK1Config(RCC_HCLK_Div1);
								 RCC_PCLK2Config(RCC_HCLK_Div2);
					
									//����HSEΪPLLʱ��Ϊ72M��������PLLʱ��
								 RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_x);
                 RCC_PLLCmd(ENABLE);
									//�ȴ�PLL�ȶ�
					         while( RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);
					         RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
                   while(RCC_GetSYSCLKSource()!=0x08);
					
			}
				
				else{
				
						
				
				     }
		
}


