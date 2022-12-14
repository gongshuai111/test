#ifndef _PID_H

#define _PID_H
#include "stm32f10x.h"
typedef struct
{
			float target_val; //目标值
			float actual_val; //实际值
			float err; //定义当前偏差值
			float err_next; //定义下一个偏差值
			float err_last; //定义最后一个偏差值
			float Kp, Ki, Kd; //定义比例、积分、微分系数
	
	
	
}pid;

void PID_param_init();

#endif