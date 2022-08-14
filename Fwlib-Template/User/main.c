#include "delay.h"
#include "sys.h"
#include "led.h"
#include "L298N.h"
#include "pwm.h"
#include "HC-SR04.h"
#include "usart.h"	 
#include "stdio.h"
#include "led.h"
#include "spi.h"
#include "nrf24l01.h"

extern u8  TIM4CH2_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM4CH2_CAPTURE_VAL;	//输入捕获值	


u16 C_TIM2_IT_Update = 0 ;		// TIM3的定时计次

u16 C_2G4_Command = 0 ;			// 2.4G指令计时

u8  F_2G4_Command_Valid = 0 ;	// 2.4G命令有效标志位
//---------------------------------------------------
int main(void)
{

    	u8  L_CNT = 0 ;				// 循环计数


	 USART_ADD();
	 printf("初始化成功");//打印到串口	
	  delay_init();	
	  L298N_GPIO_Config();
  	L298N_PWM_TIM_Init(1999,719);
	  Duoji_PWM_Config(999,1439);//20ms脉冲 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    TIM4_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数
	   HCSR04_TRIG_Init();
	   NRF24L01_RX_Mode();
	  NRF24L01_Init();
	
   if(!nrf24l01_check())
	 {
		 //进入表示初始化成功
		 
	 }
	 
	while(1)
	{  
		if(NRF24L01_RX_Packet(RF2G4_Receive_Data,14)==RX_SUCCESS)
		{
			
		}
		
			 

//          SG90_Front;
//		      delay_ms(300);
//         	
//					if(HCSR04()>65)
//					{
//							L298N_Forward();	
//							delay_ms(500);	
//					}
//					if(HCSR04()<65)
//					 {
//					  SG90_Left_90;
//						delay_ms(200);
//			  
//			  if(HCSR04()>65)
//				{
//					  Motor_Light();
//		        delay_ms(700);			
//			  }
//			else
//			{	
//				 SG90_Right_90;
//				 delay_ms(200);
//				
//				if(HCSR04()>65)
//				{
//						Motor_Right();
//						delay_ms(700);
//				}
//				else
//				{
//					L298NDaotui();
//					delay_ms(700);
//					Motor_Light();
//						delay_ms(700);
//				}
//				
//				
//			}
//		}

//	}
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 


