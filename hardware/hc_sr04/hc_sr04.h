#ifndef __HC_SR04_H_
#define __HC_SR04_H_

#include "stm32f10x.h"                  // Device header

#define HC_SR04_Tring_GPIO_Port GPIOB
#define HC_SR04_Tring_Pin GPIO_Pin_5
#define HC_SR04_Tring_PORT RCC_APB2Periph_GPIOB

#define HC_SR04_Echo_GPIO_Port GPIOA
#define HC_SR04_Echo_Pin GPIO_Pin_7
#define HC_SR04_Echo_PORT RCC_APB2Periph_GPIOA

#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET 1

float HC_SR04_Read(void);
void HC_SR04_init(void);



#endif
