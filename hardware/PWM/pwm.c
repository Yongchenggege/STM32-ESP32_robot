#include "pwm.h"

void pwm1_init(uint16_t arr,uint16_t psc)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); // �򿪶�ʱ��1
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ʹ��GPIOʱ��
	
	// ����GPIO����
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// ���ö�ʱ��
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	// ����PWM
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ��ģʽ1 ����ֵС�ڱȽ�ֵλ�ߵ�ƽ��֮Ϊ��
	TIM_OCInitStructure.TIM_Pulse = 0; //ռ�ձ�
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //����״̬�ߵ�ƽ
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	
	// ʹ��pwmͨ��1  4
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE); // �߼���ʱ����Ҫʹ�����PWM
	
//	TIM_ARRPreloadConfig(TIM1,ENABLE);  //�Զ���װ��Ԥװ������
	
	TIM_Cmd(TIM1, ENABLE); // ʹ�ܶ�ʱ��
}
