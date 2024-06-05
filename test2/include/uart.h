#ifndef __usart_H
#define __usart_H

#include <Arduino.h>

typedef struct usart_cmd_pack_{

    uint8_t head;

    uint8_t data[1];

    uint8_t end;

}usart_cmd_pack;

#endif