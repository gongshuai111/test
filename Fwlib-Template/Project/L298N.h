#ifndef _L298N_H

#define _L298N_H
#include "stm32f10x.h"
#define L298N_GPIO_Clk   RCC_APB2Periph_GPIOB
#define L298N_PWM_GPIO_Clk    RCC_APB2Periph_GPIOA

#define L298N_PWM_Clk    RCC_APB2Periph_TIM1
#define L298N_TIM  TIM1
#define L298N1_GPIO_PORT  GPIOB
#define L298N1_GPIO_Pin   GPIO_Pin_13
#define L298N2_GPIO_PORT  GPIOB
#define L298N2_GPIO_Pin   GPIO_Pin_12
#define L298N3_GPIO_PORT  GPIOB
#define L298N3_GPIO_Pin   GPIO_Pin_1
#define L298N4_GPIO_PORT  GPIOB
#define L298N4_GPIO_Pin   GPIO_Pin_0


#define  L298N_PWM_1_PORT  GPIOA
#define  L298N_PWM_1_Pin   GPIO_Pin_11
#define  L298N_PWM_2_PORT  GPIOA
#define  L298N_PWM_2_Pin   GPIO_Pin_8



void L298N_PWM_TIM_Init(u16 arr,u16 psc);
void L298N_GPIO_Config(void);
void L298N_Forward(u16 speed);
void L298NDaotui(u16 speed);
void Motor_Light(u16 speed);
void Motor_Right(u16 speed);
void Motor_STOP(void);
#endif

