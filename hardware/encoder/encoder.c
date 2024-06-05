#include "encoder.h"

// ���1�ı�����
void encoder1_init(uint16_t arr,uint16_t psc)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); // �򿪶�ʱ��4
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��GPIOʱ��
	
	// ����GPIO����
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// ���ö�ʱ��
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	// ������
	TIM_ICInitTypeDef TIM_ICStructure;
	
	TIM_ICStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICStructure.TIM_ICFilter = 0;
	
	TIM_ICInit(TIM4,&TIM_ICStructure);
	
	TIM_ICStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICStructure.TIM_ICFilter = 0;
	
	TIM_ICInit(TIM4,&TIM_ICStructure);
	
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //����TIM3����ж�
	
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; 
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	
//	NVIC_Init(&NVIC_InitStructure);
	
	TIM_SetCounter(TIM4,0); //TIM3->CNT=0
	TIM4->CNT = 0x7fff;
	
	TIM_Cmd(TIM4, ENABLE);
}

// ���2�ı�����
void encoder2_init(uint16_t arr,uint16_t psc)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); // �򿪶�ʱ��2
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // ʹ��GPIOʱ��
	
	// ����GPIO����
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// ���ö�ʱ��
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// ������
	TIM_ICInitTypeDef TIM_ICStructure;
	
	TIM_ICStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM2,&TIM_ICStructure);
	
	TIM_ICStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM2,&TIM_ICStructure);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����TIM3����ж�
	
	TIM_SetCounter(TIM2,0); //TIM3->CNT=0
	TIM2->CNT = 0x7fff;
	
	TIM_Cmd(TIM2, ENABLE);
}

int16_t get_encoder1_cnt(void)
{
	int16_t cnt;
	
	cnt = (TIM4->CNT-0x7fff);
	
	TIM4->CNT = 0x7fff;
	
	return cnt;
}

int16_t get_encoder2_cnt(void)
{
	int16_t cnt;
	
	cnt = (TIM2->CNT-0x7fff);
	
	TIM2->CNT = 0x7fff;
	
	return cnt;
}

void TIM2_IRQHandler(void)
{ 		    		  			    
	if(TIM2->SR&0X0001)//����ж�
	{
			
	}				   
	TIM2->SR&=~(1<<0);//����жϱ�־λ 	    
}

void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//����ж�
	{ 
			
	}				   
	TIM4->SR&=~(1<<0);//����жϱ�־λ 	    
}
