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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); // 打开定时器4
	
	// 配置定时器
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 				//设置NVIC中断分组2:2位抢占优先级，2位响应优先级	

 	NVIC_InitTypeDef NVIC_InitStructure;							//中断优先级NVIC设置
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  				//TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  		//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  			//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//IRQ通道被使能
	
	NVIC_Init(&NVIC_InitStructure);  								//初始化NVIC寄存器
	
	TIM_Cmd(TIM3, ENABLE);

}

void a4950_init(void)
{
	pwm1_init((PULSE_MAX-1),(TIM_PER-1)); // pwm频率10k
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); // 使能GPIO时钟
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//使能JTAGDisable，即禁用JTAG接口
	
	// 配置GPIO引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_13);
	
	encoder1_init(65535,0);
	
	encoder2_init(65535,0);
	
	timer3_init((SPEED_INTERVAL-1),(7200-1)); // 200ms测一次速度
}

// PA8 PB3 控制的电机1
// 0 --- 反向
// 1 --- 正向
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

// PA11 PB13 控制的电机2
// 0 --- 反向
// 1 --- 正向
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

// 获取电机1速度
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
	pid_opt(ctrl,obj_speed1,fabs(motor1_speed)); // 目标obj_speed1圈每秒
	drv_motor1(ctrl->output,x); // 正向	
	pid_opt(ctrl2,obj_speed2,fabs(motor2_speed)); // 目标obj_speed2圈每秒
	drv_motor2(ctrl2->output,x); // 正向
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
		/*写入执行的操作*/	
		motor1_speed = get_motor1_speed();
		motor2_speed = get_motor2_speed();
//		printf("speed1=%.1f speed2=%.1f\n",motor1_speed,motor2_speed); // 不要在中断里嵌套printf 太费时间了
	}
}


