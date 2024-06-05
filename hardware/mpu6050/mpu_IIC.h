#ifndef _MPU_IIC_H
#define _MPU_IIC_H

#include "stm32f10x.h"                  // Device header

#define MPU_IIC_SCL_PORT   					GPIOA
#define MPU_IIC_SCL_PIN        				GPIO_Pin_15
#define MPU_IIC_SCL_PORT_RCC				RCC_APB2Periph_GPIOA

#define MPU_IIC_SDA_PORT  					GPIOB
#define MPU_IIC_SDA_PIN        				GPIO_Pin_12
#define MPU_IIC_SDA_PORT_RCC				RCC_APB2Periph_GPIOB

#define MPU_IIC_SCL_High							GPIO_SetBits(MPU_IIC_SCL_PORT,MPU_IIC_SCL_PIN)
#define MPU_IIC_SCL_Low 							GPIO_ResetBits(MPU_IIC_SCL_PORT,MPU_IIC_SCL_PIN)
#define MPU_IIC_SDA_IN								GPIO_ReadInputDataBit(MPU_IIC_SDA_PORT,MPU_IIC_SDA_PIN)
#define MPU_IIC_SDA_OUT_High						GPIO_SetBits(MPU_IIC_SDA_PORT,MPU_IIC_SDA_PIN)
#define MPU_IIC_SDA_OUT_Low			   			    GPIO_ResetBits(MPU_IIC_SDA_PORT,MPU_IIC_SDA_PIN)

void MPU_iic_init(void);
void MPU_SDA_OUT(void);
void MPU_SDA_IN(void);
void MPU_iic_start(void);
void MPU_iic_stop(void);
u8 MPU_iic_wait_ack(void);
void MPU_iic_ack(void);
void MPU_iic_nack(void);
void MPU_iic_send_byte(u8 data);
u8 MPU_iic_read_byte(u8 ack);
u8 MPU_iic_read_byte(u8 ack);

#endif
