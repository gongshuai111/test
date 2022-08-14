#include "L298N.h"


//��ʼ��L298N���õ��Ĺܽ�
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
	
	 TIM_TimeBaseInitStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
  	 TIM_TimeBaseInitStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
     TIM_TimeBaseInitStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	 TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	 TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
		//��ʼ��TIM2 Channel2 PWMģʽ	 
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը� 
	 TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�
	 TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	 
	 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM���
	 TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�
	 TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	 
	 TIM_ARRPreloadConfig(TIM1,ENABLE);
	
	//=�õ��߼���ʱ����Ҫ�����ʹ��
	  TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM3
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
