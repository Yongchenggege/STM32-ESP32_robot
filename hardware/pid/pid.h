#ifndef __PID_H_
#define __PID_H_

typedef struct {
	float kp;
	float ki;
	float kd;
	float err;
	float last_err;
	float integral;
	float output;
	float output_max;
}pid_ctrl;

void pid_ctrl_init(pid_ctrl *ctrl,float p,float i,float d,float output_max);
void pid_opt(pid_ctrl *ctrl,float tar,float now);

#endif
