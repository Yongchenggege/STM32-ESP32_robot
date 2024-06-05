#include "IIC.h"

static void delay_us(u16 time);

//鍒濆鍖?
void iic_init(void)
{
	GPIO_InitTypeDef GPIO_Init_my;
	RCC_APB2PeriphClockCmd(IIC_SCL_PORT_RCC|IIC_SDA_PORT_RCC,ENABLE);
	
	GPIO_Init_my.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_my.GPIO_Pin=IIC_SCL_PIN;
	GPIO_Init_my.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_SCL_PORT,&GPIO_Init_my);
	
	GPIO_Init_my.GPIO_Pin=IIC_SDA_PIN;
	GPIO_Init(IIC_SDA_PORT,&GPIO_Init_my);
	
	IIC_SCL_High();
	IIC_SDA_OUT_High();
}
//SDA杈撳嚭
void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_Init_my;
	GPIO_Init_my.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_my.GPIO_Pin=IIC_SDA_PIN;
	GPIO_Init_my.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_SDA_PORT,&GPIO_Init_my);
}
//SDA杈撳叆
void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_Init_my;
	GPIO_Init_my.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init_my.GPIO_Pin=IIC_SDA_PIN;
	GPIO_Init_my.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(IIC_SDA_PORT,&GPIO_Init_my);
}
//璧峰淇″彿
void iic_start(void)
{
	SDA_OUT();
	IIC_SDA_OUT_High();
	IIC_SCL_High();
	delay_us(5);
	IIC_SDA_OUT_Low();
	delay_us(6);
	IIC_SCL_Low();
}
//鍋滄淇″彿
void iic_stop(void)
{
	SDA_OUT();
	IIC_SCL_Low();
	IIC_SDA_OUT_Low();
	IIC_SCL_High();
	delay_us(6);
	IIC_SDA_OUT_High();
	delay_us(6);
}
//绛夊緟搴旂瓟
uint8_t iic_wait_ack(void)
{
	uint8_t temptime=0;
	SDA_IN();
	IIC_SDA_OUT_High();
	delay_us(1);
	IIC_SCL_High();
	delay_us(1);
	while(IIC_SDA_IN())
	{
		temptime++;
		if(temptime>250)
		{
			iic_stop();
			return 1;
		}
	}
	IIC_SCL_Low();
	return 0;
}
//搴旂瓟
void iic_ack(void)
{
	IIC_SCL_Low();
	SDA_OUT();
	IIC_SDA_OUT_Low();
	delay_us(2);
	IIC_SCL_High();
	delay_us(5);
	IIC_SCL_Low();
}
//闈炲簲绛?
void iic_nack(void)
{
	IIC_SCL_Low();
	SDA_OUT();
	IIC_SDA_OUT_High();
	delay_us(2);
	IIC_SCL_High();
	delay_us(5);
	IIC_SCL_Low();
}
//鏁版嵁鍙戦€?
void iic_send_byte(uint8_t data)
{
	uint8_t t;
	SDA_OUT();
	IIC_SCL_Low();
	for(t=0;t<8;t++)
	{
		if((data&0x80)>0)
			IIC_SDA_OUT_High();
		else
			IIC_SDA_OUT_Low();
		data<<=1;
		delay_us(2);
		IIC_SCL_High();
		delay_us(2);
		IIC_SCL_Low();
		delay_us(2);
	}
}
//鏁版嵁璇诲彇
uint8_t iic_read_byte(uint8_t ack)
{
	uint8_t i=0,data=0;
	SDA_IN();
	for(i=0;i<8;i++)
	{
		IIC_SCL_Low();
		delay_us(2);
		IIC_SCL_High();
		data<<=1;
		if(IIC_SDA_IN())
			data++;
		delay_us(1);
	}
	if(!ack)
		iic_nack();
	else
		iic_ack();
	return data;
}

//粗延时函数，微秒
static void delay_us(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=10;  //自己定义
      while(i--) ;    
   }
}
