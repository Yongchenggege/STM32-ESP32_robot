#include "usart.h"

#define usart2_buf_len		64
#define usart1_buf_len		64
uint8_t usart2_buf[usart2_buf_len] ={0};
uint8_t usart1_buf[usart1_buf_len] ={0};
uint32_t usart2_cnt=0;
uint32_t usart2_cnt_last=0;
uint32_t usart1_cnt=0;
uint32_t usart1_cnt_last=0;

#ifdef USART1_EN
#if USART1_EN

void usart1_init(uint32_t baud)
{
	RCC_APB2PeriphClockCmd(USART1_GPIO_CLOCK,ENABLE);
	RCC_APB2PeriphClockCmd(USART1_CLOCK,ENABLE);
	
	GPIO_InitTypeDef gpio_struct;
	
	gpio_struct.GPIO_Pin = USART1_TX_PIN;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(USART1_GPIO_PORT,&gpio_struct);
	
	gpio_struct.GPIO_Pin = USART1_RX_PIN;
	gpio_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(USART1_GPIO_PORT,&gpio_struct);
	
	USART_InitTypeDef usart_struct;
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);	
	usart_struct.USART_BaudRate = baud;
	usart_struct.USART_WordLength = USART_WordLength_8b;
	usart_struct.USART_StopBits = USART_StopBits_1;
	usart_struct.USART_Parity = USART_Parity_No;
	usart_struct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART1,&usart_struct);
	
	NVIC_InitTypeDef nvic_struct;
	
	nvic_struct.NVIC_IRQChannel = USART1_IRQn;
	nvic_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_struct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&nvic_struct);
	
	USART_Cmd(USART1,ENABLE);
	USART_ClearFlag(USART1,USART_IT_TC);
}

void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		USART_ReceiveData(USART1);
		usart2_buf[usart1_cnt++] = USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);

	}
}

#if USART1_PRINTF_EN
int fputc(int ch,FILE *p)
{
	USART_SendData(USART1,(uint8_t)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==0);
	return ch;
}
#endif

#endif
#endif


#ifdef USART2_EN
#if USART2_EN

void usart2_init(uint32_t baud)
{
	RCC_APB2PeriphClockCmd(USART2_GPIO_CLOCK,ENABLE);
	RCC_APB1PeriphClockCmd(USART2_CLOCK,ENABLE);
	
	GPIO_InitTypeDef gpio_struct;
	
	gpio_struct.GPIO_Pin = USART2_TX_PIN;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(USART2_GPIO_PORT,&gpio_struct);
	
	gpio_struct.GPIO_Pin = USART2_RX_PIN;
	gpio_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(USART2_GPIO_PORT,&gpio_struct);
	
	USART_InitTypeDef usart_struct;
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);	
	usart_struct.USART_BaudRate = baud;
	usart_struct.USART_WordLength = USART_WordLength_8b;
	usart_struct.USART_StopBits = USART_StopBits_1;
	usart_struct.USART_Parity = USART_Parity_No;
	usart_struct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART2,&usart_struct);
	
	NVIC_InitTypeDef nvic_struct;
	
	nvic_struct.NVIC_IRQChannel = USART2_IRQn;
	nvic_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_struct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&nvic_struct);
	
	USART_Cmd(USART2,ENABLE);
	USART_ClearFlag(USART2,USART_IT_TC);
}

void USART2_IRQHandler()
{
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET)
	{

		USART_ReceiveData(USART2);
		usart2_buf[usart2_cnt++] = USART_ReceiveData(USART2);
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}

#if USART2_PRINTF_EN
int fputc(int ch,FILE *p)
{
	USART_SendData(USART2,(uint8_t)ch);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==0);
	return ch;
}
#endif

#endif
#endif

#ifdef USART3_EN
#if USART3_EN

void usart3_init(uint32_t baud)
{
	RCC_APB2PeriphClockCmd(USART3_GPIO_CLOCK,ENABLE);
	RCC_APB1PeriphClockCmd(USART3_CLOCK,ENABLE);
	
	GPIO_InitTypeDef gpio_struct;
	
	gpio_struct.GPIO_Pin = USART3_TX_PIN;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(USART3_GPIO_PORT,&gpio_struct);
	
	gpio_struct.GPIO_Pin = USART3_RX_PIN;
	gpio_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(USART3_GPIO_PORT,&gpio_struct);
	
	USART_InitTypeDef usart_struct;
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);	
	usart_struct.USART_BaudRate = baud;
	usart_struct.USART_WordLength = USART_WordLength_8b;
	usart_struct.USART_StopBits = USART_StopBits_1;
	usart_struct.USART_Parity = USART_Parity_No;
	usart_struct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART3,&usart_struct);
	
	NVIC_InitTypeDef nvic_struct;
	
	nvic_struct.NVIC_IRQChannel = USART3_IRQn;
	nvic_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_struct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&nvic_struct);
	
	USART_Cmd(USART3,ENABLE);
	USART_ClearFlag(USART3,USART_IT_TC);
}

void USART3_IRQHandler()
{
	
	if(USART_GetITStatus(USART3,USART_IT_RXNE) == SET)
	{
		usart2_buf[usart2_cnt++] = USART_ReceiveData(USART3);
		
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
}

#if USART3_PRINTF_EN
int fputc(int ch,FILE *p)
{
	USART_SendData(USART3,(uint8_t)ch);
	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==0);
	return ch;
}
#endif

#endif
#endif

#ifdef UART4_EN
#if UART4_EN

void uart4_init(uint32_t baud)
{
	RCC_APB2PeriphClockCmd(UART4_GPIO_CLOCK,ENABLE);
	RCC_APB1PeriphClockCmd(UART4_CLOCK,ENABLE);
	
	GPIO_InitTypeDef gpio_struct;
	
	gpio_struct.GPIO_Pin = UART4_TX_PIN;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(UART4_GPIO_PORT,&gpio_struct);
	
	gpio_struct.GPIO_Pin = UART4_RX_PIN;
	gpio_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(UART4_GPIO_PORT,&gpio_struct);
	
	USART_InitTypeDef usart_struct;
	
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);	
	usart_struct.USART_BaudRate = baud;
	usart_struct.USART_WordLength = USART_WordLength_8b;
	usart_struct.USART_StopBits = USART_StopBits_1;
	usart_struct.USART_Parity = USART_Parity_No;
	usart_struct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(UART4,&usart_struct);
	
	NVIC_InitTypeDef nvic_struct;
	
	nvic_struct.NVIC_IRQChannel = UART4_IRQn;
	nvic_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_struct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&nvic_struct);
	
	USART_Cmd(UART4,ENABLE);
	USART_ClearFlag(UART4,USART_IT_TC);
}

void UART4_IRQHandler()
{
	
	if(USART_GetITStatus(UART4,USART_IT_RXNE) == SET)
	{
		USART_ReceiveData(UART4);
		
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
	}
}

#if UART4_PRINTF_EN
int fputc(int ch,FILE *p)
{
	USART_SendData(UART4,(uint8_t)ch);
	while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==0);
	return ch;
}
#endif

#endif
#endif

#ifdef UART5_EN
#if UART5_EN

void uart5_init(uint32_t baud)
{
	RCC_APB2PeriphClockCmd(UART5_GPIO_CLOCK,ENABLE);
	RCC_APB1PeriphClockCmd(UART5_CLOCK,ENABLE);
	
	GPIO_InitTypeDef gpio_struct;
	
	gpio_struct.GPIO_Pin = UART5_TX_PIN;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(UART5_TX_GPIO_PORT,&gpio_struct);
	
	gpio_struct.GPIO_Pin = UART5_RX_PIN;
	gpio_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	
	GPIO_Init(UART5_RX_GPIO_PORT,&gpio_struct);
	
	USART_InitTypeDef usart_struct;
	
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);	
	usart_struct.USART_BaudRate = baud;
	usart_struct.USART_WordLength = USART_WordLength_8b;
	usart_struct.USART_StopBits = USART_StopBits_1;
	usart_struct.USART_Parity = USART_Parity_No;
	usart_struct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(UART5,&usart_struct);
	
	NVIC_InitTypeDef nvic_struct;
	
	nvic_struct.NVIC_IRQChannel = UART5_IRQn;
	nvic_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_struct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&nvic_struct);
	
	USART_Cmd(UART5,ENABLE);
	USART_ClearFlag(UART5,USART_IT_TC);
}

void UART5_IRQHandler()
{
	
	if(USART_GetITStatus(UART5,USART_IT_RXNE) == SET)
	{
		uart5_buf[uart5_cnt++] = USART_ReceiveData(UART5);
		
		USART_ClearITPendingBit(UART5,USART_IT_RXNE);
	}
}

#if UART5_PRINTF_EN
int fputc(int ch,FILE *p)
{
	USART_SendData(UART5,(uint8_t)ch);
	while(USART_GetFlagStatus(UART5,USART_FLAG_TXE)==0);
	return ch;
}
#endif

#endif
#endif

uart_status uart_receive_status(uint8_t uart)
{
	uart_status status = USART_WAIT;
	
	switch(uart)
	{
		case 1:
			status = usart1_cnt == 0 ? USART_WAIT : (usart1_cnt == usart1_cnt_last ? USART_OK : USART_RECE);
			if(status == USART_OK) { usart1_cnt = 0; usart1_cnt_last = 0;}
			else { usart1_cnt_last = usart1_cnt;}			
			break;
		case 2:
			status = usart2_cnt == 0 ? USART_WAIT : (usart2_cnt == usart2_cnt_last ? USART_OK : USART_RECE);
			if(status == USART_OK) { usart2_cnt = 0; usart2_cnt_last = 0;}
			else { usart2_cnt_last = usart2_cnt;}
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			break;
	}
	
	return status;
}

uint8_t usart2_unpackage(void)
{
	uint8_t flag = 0;
	
	if(usart2_buf[0] == 0xaa && usart2_buf[2] == 0xbb)
	{
		if(usart2_buf[1] >=1 && usart2_buf[1] <= 14)
			flag = usart2_buf[1];
	}
	
	return flag;
}

uint8_t usart1_unpackage(void)
{
	uint8_t flag = 0;
	
	if(usart1_buf[0] == 0xaa && usart1_buf[2] == 0xbb)
	{
		if(usart1_buf[1] >=1 && usart1_buf[1] <= 14)
			flag = usart1_buf[1];
	}
	
	return flag;
}
