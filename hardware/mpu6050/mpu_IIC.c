#include "mpu_IIC.h"
#include "stm32f10x.h"                  // Device header
#include "stdio.h"

static void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //????
      while(i--) ;    
   }
}


static void delay_us(u16 us_time)
{    
  u16 i=0;  
  while(us_time--)
  {
     i=10;           // ??????????????
     while(i--) ;    // ?????,???
  }
}

//初始化
void MPU_iic_init(void)
{
	GPIO_InitTypeDef GPIO_Init_my;
	RCC_APB2PeriphClockCmd(MPU_IIC_SCL_PORT_RCC|MPU_IIC_SDA_PORT_RCC,ENABLE);
	
	GPIO_Init_my.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_my.GPIO_Pin=MPU_IIC_SCL_PIN;
	GPIO_Init_my.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(MPU_IIC_SCL_PORT,&GPIO_Init_my);
	
	GPIO_Init_my.GPIO_Pin=MPU_IIC_SDA_PIN;
	GPIO_Init(MPU_IIC_SDA_PORT,&GPIO_Init_my);
	
	MPU_IIC_SCL_High;
	MPU_IIC_SDA_OUT_High;
}
//SDA输出
void MPU_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_Init_my;
	GPIO_Init_my.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_my.GPIO_Pin=MPU_IIC_SDA_PIN;
	GPIO_Init_my.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(MPU_IIC_SDA_PORT,&GPIO_Init_my);
}
//SDA输入
void MPU_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_Init_my;
	GPIO_Init_my.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init_my.GPIO_Pin=MPU_IIC_SDA_PIN;
	GPIO_Init_my.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(MPU_IIC_SDA_PORT,&GPIO_Init_my);
}
//起始信号
void MPU_iic_start(void)
{
	MPU_SDA_OUT();
	MPU_IIC_SDA_OUT_High;
	MPU_IIC_SCL_High;
	delay_us(5);
	MPU_IIC_SDA_OUT_Low;
	delay_us(6);
	MPU_IIC_SCL_Low;
}
//停止信号
void MPU_iic_stop(void)
{
	MPU_SDA_OUT();
	MPU_IIC_SCL_Low;
	MPU_IIC_SDA_OUT_Low;
	MPU_IIC_SCL_High;
	delay_us(6);
	MPU_IIC_SDA_OUT_High;
	delay_us(6);
}
//等待应答
u8 MPU_iic_wait_ack(void)
{
	u8 temptime=0;
	MPU_SDA_IN();
	MPU_IIC_SDA_OUT_High;
	delay_us(1);
	MPU_IIC_SCL_High;
	delay_us(1);
	while(MPU_IIC_SDA_IN)
	{
		printf("error !");
		temptime++;
		if(temptime>250)
		{
			MPU_iic_stop();
			return 1;
		}
	}
	MPU_IIC_SCL_Low;
	return 0;
}
//应答
void MPU_iic_ack(void)
{
	MPU_IIC_SCL_Low;
	MPU_SDA_OUT();
	MPU_IIC_SDA_OUT_Low;
	delay_us(2);
	MPU_IIC_SCL_High;
	delay_us(5);
	MPU_IIC_SCL_Low;
}
//非应答
void MPU_iic_nack(void)
{
	MPU_IIC_SCL_Low;
	MPU_SDA_OUT();
	MPU_IIC_SDA_OUT_High;
	delay_us(2);
	MPU_IIC_SCL_High;
	delay_us(5);
	MPU_IIC_SCL_Low;
}
//数据发送
void MPU_iic_send_byte(u8 data)
{
	u8 t;
	MPU_SDA_OUT();
	MPU_IIC_SCL_Low;
	for(t=0;t<8;t++)
	{
		if((data&0x80)>0)
			MPU_IIC_SDA_OUT_High;
		else
			MPU_IIC_SDA_OUT_Low;
		data<<=1;
		delay_us(2);
		MPU_IIC_SCL_High;
		delay_us(2);
		MPU_IIC_SCL_Low;
		delay_us(2);
	}
}
//数据读取
u8 MPU_iic_read_byte(u8 ack)
{
	u8 i=0,data=0;
	MPU_SDA_IN();
	for(i=0;i<8;i++)
	{
		MPU_IIC_SCL_Low;
		delay_us(2);
		MPU_IIC_SCL_High;
		data<<=1;
		if(MPU_IIC_SDA_IN)
			data++;
		delay_us(1);
	}
	if(!ack)
		MPU_iic_nack();
	else
		MPU_iic_ack();
	return data;
}
