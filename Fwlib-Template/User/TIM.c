#include "TIM.h"

// 中断优先级配置
static void ADVANCE_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef  NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = ADVANCE_TIM_IRQ ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


static void TIM_GPIO_Config(void)
{
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TIM_TimeBaseStructure.TIM_Period=ADVANCE_TIM_Period;//周期为1000us
	TIM_TimeBaseStructure.TIM_Prescaler=ADVANCE_TIM_Prescaler;//时钟预分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;//分频因子
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//重复计数没用到、
	TIM_TimeBaseInit(ADVANCE_TIM,&TIM_TimeBaseStructure);
			// 清除计数器中断标志位
    TIM_ClearFlag(ADVANCE_TIM, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(ADVANCE_TIM,TIM_IT_Update,ENABLE);
			// 使能计数器
    TIM_Cmd(ADVANCE_TIM, ENABLE);

}
void TIM1_Config(void)
{
	
	TIM_GPIO_Config();
	ADVANCE_TIM_NVIC_Config();
	
	
}

