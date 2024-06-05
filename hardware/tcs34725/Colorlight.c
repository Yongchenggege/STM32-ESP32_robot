#include "stm32f10x.h"                  // Device header

#define  	Rpin   		GPIO_Pin_4
#define  	Gpin   		GPIO_Pin_5
#define  	Bpin   		GPIO_Pin_6


void Colorlight_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Rpin | Gpin | Bpin;//rgb引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//初始化为灭状态
	GPIO_SetBits(GPIOA,Rpin);
	GPIO_SetBits(GPIOA,Gpin);
	GPIO_SetBits(GPIOA,Bpin);

}

// 0x 0000 0rgb --- 0x01 蓝色 0x02 绿色 0x04 红色 0x03 蓝色+绿色 0x07 (蓝色+绿色+红色)(白色)
void RGB_SetColor(uint8_t rgb)
{

	   (rgb & 0x01) ? GPIO_ResetBits(GPIOA,Bpin) : GPIO_SetBits(GPIOA,Bpin);
	
	   (rgb & 0x02) ? GPIO_ResetBits(GPIOA,Gpin) : GPIO_SetBits(GPIOA,Gpin);
	
	   (rgb & 0x04) ? GPIO_ResetBits(GPIOA,Rpin) : GPIO_SetBits(GPIOA,Rpin);	
	



}
