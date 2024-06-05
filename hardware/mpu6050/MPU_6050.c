#include "MPU_6050.h"
#include "mpu_IIC.h"
#include "math.h"

float angle_pitch[8];
float angle_roll[8];
float angle_yaw[8];

//??????
static void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //????
      while(i--) ;    
   }
}


void MPU_6050_IIC_init(void)
{
	MPU_iic_init();
}

u8 MPU_6050_init(void)
{
	int ID=0x68;
	
	MPU_iic_init();
	
	delay_ms(1000);
	
	MPU_6050_send_byte(0x6B,0x80);
	delay_ms(1000);
	MPU_6050_send_byte(0x6B,0x00);
	delay_ms(1000);
	
//	MPU_6050_send_byte(0x6B,0x09);
	
	MPU_6050_send_byte(0x1B,(0x03<<3));
	
	MPU_6050_send_byte(0x1C,(0x03<<3));
	
//	MPU_6050_send_byte(0x19,0x19);
//	MPU_6050_send_byte(0x1A,0x04);
	
	MPU_6050_send_byte(0x23,0x00);
	
	MPU_6050_send_byte(0x37,0x80);
	
	MPU_6050_send_byte(0x38,0x00);
	
	MPU_6050_send_byte(0x6A,0x00);
	
	if(MPU_6050_Read_byte(0x75)==ID)
	{
		MPU_6050_send_byte(0x6B,0x01);
		MPU_6050_send_byte(0x6C,0x00);
		MPU_6050_send_byte(0x19,0x19);
	  MPU_6050_send_byte(0x1A,0x04);
	}
	else
		return 0;
	return 1;
}

void MPU_6050_send_byte(u8 addr,u8 data)
{
	MPU_iic_start();
	MPU_iic_send_byte(0xD0);
	MPU_iic_wait_ack();
	MPU_iic_send_byte(addr);
	MPU_iic_wait_ack();
	MPU_iic_send_byte(data);
	MPU_iic_wait_ack();
	MPU_iic_stop();
}

//
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    MPU_iic_start(); 
	MPU_iic_send_byte((addr<<1)|0);//发送器件地址+写命令	
	if(MPU_iic_wait_ack())	//等待应答
	{
		MPU_iic_stop();		 
		return 1;		
	}
    MPU_iic_send_byte(reg);	//写寄存器地址
    MPU_iic_wait_ack();		//等待应答
	for(i=0;i<len;i++)
	{
		MPU_iic_send_byte(buf[i]);	//发送数据
		if(MPU_iic_wait_ack())		//等待ACK
		{
			MPU_iic_stop();	 
			return 1;		 
		}		
	}    
    MPU_iic_stop();	 
	return 0;	
} 

u8 MPU_6050_Read_byte(u8 addr)
{
	u8 data;
	MPU_iic_start();
	MPU_iic_send_byte(0xD0);
	MPU_iic_wait_ack();
	MPU_iic_send_byte(addr);
	MPU_iic_wait_ack();
	MPU_iic_start();
	MPU_iic_send_byte(0xD1);
	MPU_iic_wait_ack();
	data=MPU_iic_read_byte(0);
	MPU_iic_stop();
	return data;
}

//
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	MPU_iic_start(); 
	MPU_iic_send_byte((addr<<1)|0);//发送器件地址+写命令	
	if(MPU_iic_wait_ack())	//等待应答
	{
		MPU_iic_stop();		 
		return 1;		
	}
    MPU_iic_send_byte(reg);	//写寄存器地址
    MPU_iic_wait_ack();		//等待应答
    MPU_iic_start();
	MPU_iic_send_byte((addr<<1)|1);//发送器件地址+读命令	
    MPU_iic_wait_ack();		//等待应答 
	while(len)
	{
		if(len==1)*buf=MPU_iic_read_byte(0);//读数据,发送nACK 
		else *buf=MPU_iic_read_byte(1);		//读数据,发送ACK  
		len--;
		buf++; 
	}    
    MPU_iic_stop();	//产生一个停止条件 
	return 0;	
}

void average(float *pitch,float *roll,float *yaw)
{
	int i;
	for(i=incise-1;i>0;i--)
	{
		angle_pitch[i]=angle_pitch[i-1];
		angle_roll[i]=angle_roll[i-1];
		angle_yaw[i]=angle_yaw[i-1];
	}
	angle_pitch[0]=*pitch;
	angle_roll[0]=*roll;
	angle_yaw[0]=*yaw;
	
	for(i=0;i<incise;i++)
	{
		*pitch=*pitch+angle_pitch[i];
		*roll=*roll+angle_roll[i];
		*yaw=*yaw+angle_yaw[i];
	}
	*pitch=*pitch/incise;
	*roll=*roll/incise;
	*yaw=*yaw/incise;
}
