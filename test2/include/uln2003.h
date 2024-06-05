#ifndef __uln2003_H
#define __uln2003_H

#include<Arduino.h>
#include<stdint.h>

#define ANGLE       0.703125
// #define ANGLE       0.087891
#define ULN2003_A_1   2
#define ULN2003_B_1   4
#define ULN2003_C_1   5
#define ULN2003_D_1   18


class uln2003{

public:
    uln2003(){
        pinMode(ULN2003_A_1,OUTPUT);
        pinMode(ULN2003_B_1,OUTPUT);
        pinMode(ULN2003_C_1,OUTPUT);
        pinMode(ULN2003_D_1,OUTPUT);
        digitalWrite(ULN2003_A_1,LOW);
        digitalWrite(ULN2003_B_1,LOW);
        digitalWrite(ULN2003_C_1,LOW);
        digitalWrite(ULN2003_D_1,LOW);

    };

    void run_x_1(uint16_t x,bool mode);

    void run1_1();

    void run2_1();
    
    void stop_1();

    void uln2003_delay(uint16_t angle);
};

#endif
