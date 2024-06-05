#ifndef __a4950_H
#define __a4950_H

#include "stm32f10x.h"
#include "pid.h"

// FREQ = 72000000/(TIM_PER*PULSE_MAX)
#define TIM_PER			5
#define PULSE_MAX		7200

// �������תһȦ��������
#define MOTOR_PULSE	11

// �ٶȲ������(ȡֵΪ0-65535 �Ե�ʱ��Ϊx*0.0001 ����ȡֵ2000 ��Ӧ��2000*0.0001=0.2 (s) ����ȡֵ�� 500-10000 )
#define SPEED_INTERVAL	2000

// ���ֵ�����ٱ�9.6 ���ת��620 ���տ���ת��620/9.6=64.6 ��������һȦ11������


void a4950_init(void);
void drv_motor1(uint16_t pulse,uint8_t DIR);
void drv_motor2(uint16_t pulse,uint8_t DIR);
float get_motor_speed(uint8_t motor);
void motor_test(void);
void motor_speed_test(pid_ctrl *ctrl,pid_ctrl *ctrl2);
void sampled_data_test(void);
void pidmotor_run(pid_ctrl *ctrl,pid_ctrl *ctrl2,float obj_speed1,float obj_speed2,_Bool x);

#endif
