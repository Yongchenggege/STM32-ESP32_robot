#include "uln2003.h"

void uln2003::run_x_1(uint16_t x,bool mode)//1正转 2反转
{
    uint16_t i;
    if(mode)
    {
        for(i=0;i<(uint16_t)(x/ANGLE);i++)
        {
            run1_1();
        }
    }else {
        for(i=0;i<(uint16_t)(x/ANGLE);i++)
        {
            run2_1();
        }
    }
    stop_1();
}

void uln2003::run1_1()
{
    digitalWrite(ULN2003_A_1,HIGH);
    digitalWrite(ULN2003_B_1,HIGH);
    delay(2);
    digitalWrite(ULN2003_A_1,LOW);
    digitalWrite(ULN2003_B_1,LOW);
    delay(2);

    digitalWrite(ULN2003_B_1,HIGH);
    digitalWrite(ULN2003_C_1,HIGH);
    delay(2);
    digitalWrite(ULN2003_B_1,LOW);
    digitalWrite(ULN2003_C_1,LOW);
    delay(2);

    digitalWrite(ULN2003_C_1,HIGH);
    digitalWrite(ULN2003_D_1,HIGH);
    delay(2);
    digitalWrite(ULN2003_C_1,LOW);
    digitalWrite(ULN2003_D_1,LOW);
    delay(2);

    digitalWrite(ULN2003_D_1,HIGH);
    digitalWrite(ULN2003_A_1,HIGH);
    delay(2);
    digitalWrite(ULN2003_D_1,LOW);
    digitalWrite(ULN2003_A_1,LOW);
    delay(2);

    // digitalWrite(ULN2003_D_1,LOW);
    // digitalWrite(ULN2003_A_1,HIGH);
    // delay(4);
    // digitalWrite(ULN2003_A_1,LOW);
    // digitalWrite(ULN2003_B_1,HIGH);
    // delay(4);
    // digitalWrite(ULN2003_B_1,LOW);
    // digitalWrite(ULN2003_C_1,HIGH);
    // delay(4);
    // digitalWrite(ULN2003_C_1,LOW);
    // digitalWrite(ULN2003_D_1,HIGH);
    // delay(4);
}

void uln2003::run2_1(){

    digitalWrite(ULN2003_A_1,HIGH);
    digitalWrite(ULN2003_B_1,HIGH);
    delay(2);
    digitalWrite(ULN2003_A_1,LOW);
    digitalWrite(ULN2003_B_1,LOW);
    delay(2);

    digitalWrite(ULN2003_A_1,HIGH);  
    digitalWrite(ULN2003_D_1,HIGH); 
    delay(2); 
    digitalWrite(ULN2003_A_1,LOW);
    digitalWrite(ULN2003_D_1,LOW);
    delay(2);

    digitalWrite(ULN2003_C_1,HIGH);  
    digitalWrite(ULN2003_D_1,HIGH); 
    delay(2); 
    digitalWrite(ULN2003_C_1,LOW);
    digitalWrite(ULN2003_D_1,LOW);
    delay(2);

    digitalWrite(ULN2003_C_1,HIGH);  
    digitalWrite(ULN2003_B_1,HIGH); 
    delay(2); 
    digitalWrite(ULN2003_C_1,LOW);
    digitalWrite(ULN2003_B_1,LOW);
    delay(2);

        // digitalWrite(ULN2003_A_1,LOW);
        // digitalWrite(ULN2003_D_1,HIGH);
        // delay(4);
        // digitalWrite(ULN2003_D_1,LOW);
        // digitalWrite(ULN2003_C_1,HIGH);
        // delay(4);
        // digitalWrite(ULN2003_C_1,LOW);
        // digitalWrite(ULN2003_B_1,HIGH);
        // delay(4);
        // digitalWrite(ULN2003_B_1,LOW);
        // digitalWrite(ULN2003_A_1,HIGH);
        // delay(4);
    }

void uln2003::stop_1(){
        digitalWrite(ULN2003_A_1,LOW);
        digitalWrite(ULN2003_B_1,LOW);
        digitalWrite(ULN2003_C_1,LOW);
        digitalWrite(ULN2003_D_1,LOW);
    }

void uln2003::uln2003_delay(uint16_t angle)
{
    delay(angle/ANGLE*12+50);


}