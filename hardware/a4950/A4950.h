#ifndef __a4950_H
#define __a4950_H

#include "stm32f10x.h"
#include "pid.h"

// FREQ = 72000000/(TIM_PER*PULSE_MAX)
#define TIM_PER			5
#define PULSE_MAX		7200

// 电机的旋转一圈的脉冲数
#define MOTOR_PULSE	11

// 速度测量间隔(取值为0-65535 对的时间为x*0.0001 这里取值2000 对应是2000*0.0001=0.2 (s) 建议取值在 500-10000 )
#define SPEED_INTERVAL	2000

// 齿轮电机减速比9.6 电机转速620 最终空载转速620/9.6=64.6 霍尔反馈一圈11个脉冲


void a4950_init(void);
void drv_motor1(uint16_t pulse,uint8_t DIR);
void drv_motor2(uint16_t pulse,uint8_t DIR);
float get_motor_speed(uint8_t motor);
void motor_test(void);
void motor_speed_test(pid_ctrl *ctrl,pid_ctrl *ctrl2);
void sampled_data_test(void);
void pidmotor_run(pid_ctrl *ctrl,pid_ctrl *ctrl2,float obj_speed1,float obj_speed2,_Bool x);

#endif
