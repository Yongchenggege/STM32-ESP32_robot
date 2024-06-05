#ifndef __encoder_H
#define __encoder_H

#include "stm32f10x.h"

void encoder1_init(uint16_t arr,uint16_t psc);
void encoder2_init(uint16_t arr,uint16_t psc);
int16_t get_encoder1_cnt(void);
int16_t get_encoder2_cnt(void);

#endif
