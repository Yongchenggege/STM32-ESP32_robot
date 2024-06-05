#include "a4950.h"
#include "pwm.h"
#include "encoder.h"
//#include "stdelay.h"
//#include "stdio.h"
#include "math.h"

static float motor1_speed = 0;
static float motor2_speed = 0;

void timer3_init(uint16_t arr,uint16_t psc)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); // �򿪶�ʱ��4
	
	// ���ö�ʱ��
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 				//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�	

 	NVIC_InitTypeDef NVIC_InitStructure;							//�ж����ȼ�NVIC����
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  				//TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  		//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  			//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//IRQͨ����ʹ��
	
	NVIC_Init(&NVIC_InitStructure);  								//��ʼ��NVIC�Ĵ���
	
	TIM_Cmd(TIM3, ENABLE);

}

void a4950_init(void)
{
	pwm1_init((PULSE_MAX-1),(TIM_PER-1)); // pwmƵ��10k
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); // ʹ��GPIOʱ��
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//ʹ��JTAGDisable��������JTAG�ӿ�
	
	// ����GPIO����
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_13);
	
	encoder1_init(65535,0);
	
	encoder2_init(65535,0);
	
	timer3_init((SPEED_INTERVAL-1),(7200-1)); // 200ms��һ���ٶ�
}

// PA8 PB3 ���Ƶĵ��1
// 0 --- ����
// 1 --- ����
void drv_motor1(uint16_t pulse,uint8_t DIR)
{
	if(pulse > PULSE_MAX)
		pulse = PULSE_MAX;
	
	switch(DIR)
	{
		case 0:
			GPIO_ResetBits(GPIOB,GPIO_Pin_3);
			TIM_SetCompare1(TIM1,pulse);
			break;
		default :
			GPIO_SetBits(GPIOB,GPIO_Pin_3);
			TIM_SetCompare1(TIM1,(PULSE_MAX-pulse));
			break;
	}
}

// PA11 PB13 ���Ƶĵ��2
// 0 --- ����
// 1 --- ����
void drv_motor2(uint16_t pulse,uint8_t DIR)
{
	if(pulse > PULSE_MAX)
		pulse = PULSE_MAX;
	
	switch(DIR)
	{
		case 0:
			GPIO_ResetBits(GPIOB,GPIO_Pin_13);
			TIM_SetCompare4(TIM1,pulse);
			break;
		default :
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			TIM_SetCompare4(TIM1,(PULSE_MAX-pulse));
			break;
	}
}

// ��ȡ���1�ٶ�
static float get_motor1_speed(void)
{
	int16_t cnt = get_encoder1_cnt();
	float circle,speed;

	
	circle = cnt/(MOTOR_PULSE*4.0);
	
	speed = circle*(1/(SPEED_INTERVAL*0.0001));
	
	return -speed;
}

static float get_motor2_speed(void)
{
	int16_t cnt = get_encoder2_cnt();
	float circle,speed;
	
	circle = cnt/(MOTOR_PULSE*4.0);
	
	speed = circle*(1/(SPEED_INTERVAL*0.0001));
	
	return speed;
}

float get_motor_speed(uint8_t motor)
{
	switch(motor)
	{
		case 1:return motor1_speed;
		
		default :return motor2_speed;
	}
}



/*
pidmotor_run(&pid_speed_ctrl,&pid_speed_ctrl2,10,10,1);//forward
pidmotor_run(&pid_speed_ctrl,&pid_speed_ctrl2,-10,-10,0);//back
pidmotor_run(&pid_speed_ctrl,&pid_speed_ctrl2,10,5,1);//left
pidmotor_run(&pid_speed_ctrl,&pid_speed_ctrl2,5,10,1);//right
pidmotor_run(&pid_speed_ctrl,&pid_speed_ctrl2,0,0,1);//stop

*/

void pidmotor_run(pid_ctrl *ctrl,pid_ctrl *ctrl2,float obj_speed1,float obj_speed2,_Bool x)
{
	pid_opt(ctrl,obj_speed1,fabs(motor1_speed)); // Ŀ��obj_speed1Ȧÿ��
	drv_motor1(ctrl->output,x); // ����	
	pid_opt(ctrl2,obj_speed2,fabs(motor2_speed)); // Ŀ��obj_speed2Ȧÿ��
	drv_motor2(ctrl2->output,x); // ����
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		/*д��ִ�еĲ���*/	
		motor1_speed = get_motor1_speed();
		motor2_speed = get_motor2_speed();
//		printf("speed1=%.1f speed2=%.1f\n",motor1_speed,motor2_speed); // ��Ҫ���ж���Ƕ��printf ̫��ʱ����
	}
}


