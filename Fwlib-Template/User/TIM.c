#include "TIM.h"

// �ж����ȼ�����
static void ADVANCE_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef  NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQ ;	
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


static void TIM_GPIO_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TIM_TimeBaseStructure.TIM_Period=ADVANCE_TIM_Period;//����Ϊ1000us
	TIM_TimeBaseStructure.TIM_Prescaler=ADVANCE_TIM_Prescaler;//ʱ��Ԥ��Ƶϵ��
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//��Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//�ظ�����û�õ���
	TIM_TimeBaseInit(ADVANCE_TIM,&TIM_TimeBaseStructure);
			// ����������жϱ�־λ
    TIM_ClearFlag(ADVANCE_TIM, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(ADVANCE_TIM,TIM_IT_Update,ENABLE);
			// ʹ�ܼ�����
    TIM_Cmd(ADVANCE_TIM, ENABLE);

}
void TIM1_Config(void)
{
	
	TIM_GPIO_Config();
	ADVANCE_TIM_NVIC_Config();
	
	
}

