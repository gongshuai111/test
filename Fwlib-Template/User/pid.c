#include "pid.h"



void PID_param_init()
{
	pid.target_val=0.0;
	pid.actual_val=0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.err_next = 0.0;
	pid.Kp = 0.21;
	pid.Ki = 0.80;
	pid.Kd = 0.01;
	
	
	
	
}
float PID_realize(float temp_val)
{
	pid.err=pid.target_val-temp_val;
	
	
	
	
}