#include "HC-SR04.h"
#include "delay.h"
void HCSR04_TRIG_Send(void)
{ 
    GPIO_ResetBits(GPIOB,GPIO_Pin_6);
    delay_us(20);     //��ʱ20US
    GPIO_SetBits(GPIOB,GPIO_Pin_6);
}
void HCSR04_TRIG_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //PC1��TRIG
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    //��Ϊ�������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                 
    GPIO_Init(GPIOB, &GPIO_InitStructure);              //��ʼ������GPIO
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}

TIM_ICInitTypeDef  TIM4_ICInitStructure;
void TIM4_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;     //PA1 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  //PA1 ��������  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);	
	
	//��ʼ����ʱ��5 TIM5	 
	 TIM_TimeBaseStructure.TIM_Period = arr;     //�趨�������Զ���װֵ 
	 TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	 TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	 TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM5���벶�����
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //ͨ��2
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 5;//�˲�ϵ��Ϊ5
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC2,ENABLE);//��������ж� ,����CC2IE�����ж�	
	
   	TIM_Cmd(TIM4,ENABLE ); 	//ʹ�ܶ�ʱ��5
   
}
u8  TIM4CH2_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM4CH2_CAPTURE_VAL;	//���벶��ֵ
 
//��ʱ��5�жϷ������	 
void TIM4_IRQHandler(void)
{ 
 	if((TIM4CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		{	    
			if(TIM4CH2_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM4CH2_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM4CH2_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM4CH2_CAPTURE_VAL=0XFFFF;
				}else TIM4CH2_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)//����2���������¼�
		{	
			if(TIM4CH2_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM4CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM4CH2_CAPTURE_VAL=TIM_GetCapture2(TIM4);
		   	TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC2P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM4CH2_CAPTURE_STA=0;			//���
				TIM4CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);
				TIM4CH2_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC2P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC2|TIM_IT_Update); //����жϱ�־λ
}
 float HCSR04(void)
{    
	       u32 temp=0;
         float distance = 0;	
	       HCSR04_TRIG_Send();
					if(TIM4CH2_CAPTURE_STA&0X80)//�ɹ�������һ��������
					temp=TIM4CH2_CAPTURE_STA&0X3F;
					temp*=65536;//���ʱ���ܺ�
					temp+=TIM4CH2_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
					distance = (float)temp * 170 / 10000;   
          TIM4CH2_CAPTURE_STA=0;//������һ�β���  			
	return distance;
	
}
