#include "pid.h"

// pid_ctrl ³õÊ¼»¯
void pid_ctrl_init(pid_ctrl *ctrl,float kp,float ki,float kd,float output_max)
{
	ctrl->kp = kp;
	ctrl->ki = ki;
	ctrl->kd = kd;
	ctrl->err = 0;
	ctrl->last_err = 0;
	ctrl->integral = 0;
	ctrl->output = 0;
	ctrl->output_max = output_max;
}

// pid ¼ÆËã
void pid_opt(pid_ctrl *ctrl,float tar,float now)
{
	ctrl->last_err = ctrl->err;
	
	ctrl->err = tar - now;
	
	float pout = ctrl->kp*ctrl->err;
	
	float dout = ctrl->kd*(ctrl->err - ctrl->last_err);
	
	if(ctrl->output == ctrl->output_max)
	{
		if(ctrl->err <= 0)
			ctrl->integral += ctrl->ki*ctrl->err;
	}else if(ctrl->output == 0)
	{
		if(ctrl->err >= 0)
			ctrl->integral += ctrl->ki*ctrl->err;
	}else
	{
		ctrl->integral += ctrl->ki*ctrl->err;
	}
	
	ctrl->output = pout + ctrl->integral + dout;
	
	if(ctrl->output > ctrl->output_max)
		ctrl->output = ctrl->output_max;
	else if(ctrl->output<0)
	{
		ctrl->output = 0;	
	}

}
