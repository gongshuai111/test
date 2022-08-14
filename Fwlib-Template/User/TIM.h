#ifndef _TIM_H

#define _TIM_H
#include "stm32f10x.h"
#define  ADVANCE_TIM_IRQ               TIM1_UP_IRQn
#define            ADVANCE_TIM_Period            (1000-1)

#define            ADVANCE_TIM_Prescaler         71
#define            ADVANCE_TIM                   TIM1
void TIM1_Config(void);
#endif

