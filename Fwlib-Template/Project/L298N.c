#include "L298N.h"


//初始化L298N所用到的管脚
void L298N_GPIO_Config(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(L298N_GPIO_Clk,ENABLE);
	
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	
	 GPIO_InitStructure.GPIO_Pin = L298N1_GPIO_Pin;
	 GPIO_Init(L298N1_GPIO_PORT,&GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = L298N2_GPIO_Pin;
	 GPIO_Init(L298N2_GPIO_PORT,&GPIO_InitStructure);

 	 GPIO_InitStructure.GPIO_Pin = L298N3_GPIO_Pin;
	 GPIO_Init(L298N3_GPIO_PORT,&GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = L298N4_GPIO_Pin;
	 GPIO_Init(L298N4_GPIO_PORT,&GPIO_InitStructure);
	
	
	
	GPIO_ResetBits(L298N1_GPIO_PORT,L298N1_GPIO_Pin);
	GPIO_ResetBits(L298N2_GPIO_PORT,L298N2_GPIO_Pin);
	GPIO_ResetBits(L298N3_GPIO_PORT,L298N3_GPIO_Pin);
	GPIO_ResetBits(L298N4_GPIO_PORT,L298N4_GPIO_Pin);
}
void L298N_PWM_TIM_Init(u16 arr,u16 psc)
{
	 TIM_TimeBaseInitTypeDef   TIM_TimeBaseInitStructure;
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 TIM_OCInitTypeDef    TIM_OCInitStructure;
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	 TIM_TimeBaseInitStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
  	 TIM_TimeBaseInitStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
     TIM_TimeBaseInitStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	 TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	 TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
		//初始化TIM2 Channel2 PWM模式	 
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高 
	 TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参
	 TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	 
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出
	 TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参
	 TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	 
	 TIM_ARRPreloadConfig(TIM1,ENABLE);
	
	//=用到高级定时器需要主输出使能
	  TIM_Cmd(TIM1, ENABLE);  //使能TIM3
	   TIM_CtrlPWMOutputs(TIM1,ENABLE);
}
void L298N_Forward(void)
{
	GPIO_SetBits(L298N1_GPIO_PORT,L298N1_GPIO_Pin);
	GPIO_ResetBits(L298N2_GPIO_PORT,L298N2_GPIO_Pin);
	GPIO_SetBits(L298N3_GPIO_PORT,L298N3_GPIO_Pin);
	GPIO_ResetBits(L298N4_GPIO_PORT,L298N4_GPIO_Pin);
	TIM_SetCompare1(TIM1,800);
	TIM_SetCompare4(TIM1,800);
}
void L298NDaotui(void)
{
	GPIO_SetBits(L298N2_GPIO_PORT,L298N2_GPIO_Pin);
	GPIO_ResetBits(L298N1_GPIO_PORT,L298N1_GPIO_Pin);
	GPIO_SetBits(L298N4_GPIO_PORT,L298N4_GPIO_Pin);
	GPIO_ResetBits(L298N3_GPIO_PORT,L298N3_GPIO_Pin);
	TIM_SetCompare1(L298N_TIM,700);
	TIM_SetCompare4(L298N_TIM,700);
}

void Motor_STOP(void)
{
	GPIO_SetBits(L298N1_GPIO_PORT,L298N1_GPIO_Pin);
	GPIO_SetBits(L298N2_GPIO_PORT,L298N2_GPIO_Pin);
	GPIO_SetBits(L298N3_GPIO_PORT,L298N3_GPIO_Pin);
	GPIO_SetBits(L298N4_GPIO_PORT,L298N4_GPIO_Pin);

//	
}
void Motor_Light(void)
{
	GPIO_SetBits(L298N1_GPIO_PORT,L298N1_GPIO_Pin);
	GPIO_SetBits(L298N2_GPIO_PORT,L298N2_GPIO_Pin);
	GPIO_SetBits(L298N3_GPIO_PORT,L298N3_GPIO_Pin);
	GPIO_ResetBits(L298N4_GPIO_PORT,L298N4_GPIO_Pin);
	TIM_SetCompare1(L298N_TIM,700);
	TIM_SetCompare4(L298N_TIM,700);
}
void Motor_Right(void)
{
	GPIO_SetBits(L298N1_GPIO_PORT,L298N1_GPIO_Pin);
	GPIO_ResetBits(L298N2_GPIO_PORT,L298N2_GPIO_Pin);
	GPIO_SetBits(L298N3_GPIO_PORT,L298N3_GPIO_Pin);
	GPIO_SetBits(L298N4_GPIO_PORT,L298N4_GPIO_Pin);
	TIM_SetCompare1(L298N_TIM,700);
	TIM_SetCompare4(L298N_TIM,700);
}
