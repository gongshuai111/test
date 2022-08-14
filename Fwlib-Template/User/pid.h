#ifndef _PID_H

#define _PID_H
#include "stm32f10x.h"
typedef struct
{
			float target_val; //Ŀ��ֵ
			float actual_val; //ʵ��ֵ
			float err; //���嵱ǰƫ��ֵ
			float err_next; //������һ��ƫ��ֵ
			float err_last; //�������һ��ƫ��ֵ
			float Kp, Ki, Kd; //������������֡�΢��ϵ��
	
	
	
}pid;

void PID_param_init();

#endif