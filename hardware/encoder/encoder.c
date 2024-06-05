#include "encoder.h"

// 电机1的编码器
void encoder1_init(uint16_t arr,uint16_t psc)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); // 打开定时器4
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIO时钟
	
	// 配置GPIO引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// 配置定时器
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	// 编码器
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
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许TIM3溢出中断
	
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

// 电机2的编码器
void encoder2_init(uint16_t arr,uint16_t psc)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); // 打开定时器2
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIO时钟
	
	// 配置GPIO引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置定时器
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	// 编码器
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
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许TIM3溢出中断
	
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
	if(TIM2->SR&0X0001)//溢出中断
	{
			
	}				   
	TIM2->SR&=~(1<<0);//清除中断标志位 	    
}

void TIM4_IRQHandler(void)
{ 		    		  			    
	if(TIM4->SR&0X0001)//溢出中断
	{ 
			
	}				   
	TIM4->SR&=~(1<<0);//清除中断标志位 	    
}
