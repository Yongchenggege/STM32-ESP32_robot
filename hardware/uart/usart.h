#ifndef __usart_H
#define __usart_H

#include "stm32f10x.h"
#include "stdio.h"

typedef enum uart_status_{
	USART_OK,
	USART_RECE,
	USART_WAIT,
}uart_status;

#define USART1_EN		1 // 编译串口1的代码
#ifdef USART1_EN
#if USART1_EN
	#define USART1_PRINTF_EN					1
	#define USART1_CLOCK							RCC_APB2Periph_USART1
	#define USART1_GPIO_CLOCK					RCC_APB2Periph_GPIOA
	#define USART1_GPIO_PORT					GPIOA
	#define USART1_TX_PIN							GPIO_Pin_9
	#define USART1_RX_PIN							GPIO_Pin_10
#endif
#endif

#define USART2_EN		1 // 编译串口2的代码
#ifdef USART2_EN
#if USART2_EN
	#define USART2_PRINTF_EN					0
	#define USART2_CLOCK							RCC_APB1Periph_USART2
	#define USART2_GPIO_CLOCK					RCC_APB2Periph_GPIOA
	#define USART2_GPIO_PORT					GPIOA
	#define USART2_TX_PIN							GPIO_Pin_2
	#define USART2_RX_PIN							GPIO_Pin_3
#endif
#endif

#define USART3_EN		0 // 编译串口3的代码
#ifdef USART3_EN
#if USART3_EN
	#define USART3_PRINTF_EN					0
	#define USART3_CLOCK							RCC_APB1Periph_USART3
	#define USART3_GPIO_CLOCK					RCC_APB2Periph_GPIOB
	#define USART3_GPIO_PORT					GPIOB
	#define USART3_TX_PIN							GPIO_Pin_10
	#define USART3_RX_PIN							GPIO_Pin_11
#endif
#endif

#define UART4_EN		0 // 编译串口4的代码
#ifdef UART4_EN
#if UART4_EN
	#define UART4_PRINTF_EN						0
	#define UART4_CLOCK								RCC_APB1Periph_UART4
	#define UART4_GPIO_CLOCK					RCC_APB2Periph_GPIOC
	#define UART4_GPIO_PORT						GPIOC
	#define UART4_TX_PIN							GPIO_Pin_10
	#define UART4_RX_PIN							GPIO_Pin_11
#endif
#endif

#define UART5_EN		0 // 编译串口5的代码
#ifdef UART5_EN
#if UART5_EN
	#define UART5_PRINTF_EN						0
	#define UART5_CLOCK								RCC_APB1Periph_UART5
	#define UART5_GPIO_CLOCK					RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD
	#define UART5_TX_GPIO_PORT				GPIOC
	#define UART5_RX_GPIO_PORT				GPIOD
	#define UART5_TX_PIN							GPIO_Pin_12
	#define UART5_RX_PIN							GPIO_Pin_2
#endif
#endif

void usart1_init(uint32_t baud);
void usart2_init(uint32_t baud);
void usart3_init(uint32_t baud);
void uart4_init(uint32_t baud);
void uart5_init(uint32_t baud);

uart_status uart_receive_status(uint8_t uart);
uint8_t usart2_unpackage(void);
uint8_t usart1_unpackage(void);

#endif
