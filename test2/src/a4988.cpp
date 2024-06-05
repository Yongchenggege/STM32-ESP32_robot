#include "a4988.h"

void a4988::a4988_dir(bool mode)
{
    if(mode){
        digitalWrite(A4988_DIR,LOW);
    }else {
        digitalWrite(A4988_DIR,HIGH);
    }
}

void a4988::a4988_mode(uint8_t mode)
{
    this->mode = mode;

    switch(mode)
    {
        case A4988_MODE_FULL:
            digitalWrite(A4988_MS0,LOW);
            digitalWrite(A4988_MS1,LOW);
            digitalWrite(A4988_MS2,LOW);
            break;
        case A4988_MODE_HALF:
            digitalWrite(A4988_MS0,HIGH);
            digitalWrite(A4988_MS1,LOW);
            digitalWrite(A4988_MS2,LOW);
            break;
        case A4988_MODE_QUARTER:
            digitalWrite(A4988_MS0,LOW);
            digitalWrite(A4988_MS1,HIGH);
            digitalWrite(A4988_MS2,LOW);
            break;
        case A4988_MODE_EIGTH:
            digitalWrite(A4988_MS0,HIGH);
            digitalWrite(A4988_MS1,HIGH);
            digitalWrite(A4988_MS2,LOW);
            break;
        case A4988_MODE_SIXTEENTH:
            digitalWrite(A4988_MS0,HIGH);
            digitalWrite(A4988_MS1,HIGH);
            digitalWrite(A4988_MS2,HIGH);
            break;
    }
}

void a4988::a4988_en(bool status)
{
    if(status)
    {
        digitalWrite(A4988_EN,LOW);
    }else {
        digitalWrite(A4988_EN,HIGH);
    }
}

void a4988::a4988_step_1()
{
   // digitalWrite(A4988_STEP,LOW);
   if(init_mode == 0)
   {
        delay(2);
        digitalWrite(A4988_STEP_1,HIGH);
        delay(2);
        digitalWrite(A4988_STEP_1,LOW);
   }else {
        ledcWrite(0,512);
        delayMicroseconds((uint32_t)(1000*1000/freq));
        ledcWrite(0,0);
   }
}

void a4988::a4988_step_2()
{
   // digitalWrite(A4988_STEP,LOW);
   if(init_mode == 0)
   {
        delay(2);
        digitalWrite(A4988_STEP_2,HIGH);
        delay(2);
        digitalWrite(A4988_STEP_2,LOW);
   }else {
        ledcWrite(1,512);
        delayMicroseconds((uint32_t)(1000*1000/freq));
        ledcWrite(1,0);
   }
}

void a4988::a4988_step_3()
{
   // digitalWrite(A4988_STEP,LOW);
   if(init_mode == 0)
   {
        delay(2);
        digitalWrite(A4988_STEP_3,HIGH);
        delay(2);
        digitalWrite(A4988_STEP_3,LOW);
   }else {
        ledcWrite(2,512);
        delayMicroseconds((uint32_t)(1000*1000/freq));
        ledcWrite(2,0);
   }
}

void a4988::a4988_angle_1(uint16_t angle)
{
    float step_angle;

    switch(mode)
    {
        case A4988_MODE_FULL:
            step_angle = 1.8;
            break;
        case A4988_MODE_HALF:
            step_angle = 0.9;
            break;
        case A4988_MODE_QUARTER:
            step_angle = 0.45;
            break;
        case A4988_MODE_EIGTH:
            step_angle = 0.225;
            break;
        case A4988_MODE_SIXTEENTH:
            step_angle = 0.1125;
            break;
    }

    for(int i=0;i<(uint16_t)(angle/step_angle);i++)
    {
        a4988_step_1();
    }
}

void a4988::a4988_angle_2(uint16_t angle)
{
    float step_angle;

    switch(mode)
    {
        case A4988_MODE_FULL:
            step_angle = 1.8;
            break;
        case A4988_MODE_HALF:
            step_angle = 0.9;
            break;
        case A4988_MODE_QUARTER:
            step_angle = 0.45;
            break;
        case A4988_MODE_EIGTH:
            step_angle = 0.225;
            break;
        case A4988_MODE_SIXTEENTH:
            step_angle = 0.1125;
            break;
    }

    for(int i=0;i<(uint16_t)(angle/step_angle);i++)
    {
        a4988_step_2();
    }
}

void a4988::a4988_angle_3(uint16_t angle)
{
    float step_angle;

    switch(mode)
    {
        case A4988_MODE_FULL:
            step_angle = 1.8;
            break;
        case A4988_MODE_HALF:
            step_angle = 0.9;
            break;
        case A4988_MODE_QUARTER:
            step_angle = 0.45;
            break;
        case A4988_MODE_EIGTH:
            step_angle = 0.225;
            break;
        case A4988_MODE_SIXTEENTH:
            step_angle = 0.1125;
            break;
    }

    for(int i=0;i<(uint16_t)(angle/step_angle);i++)
    {
        a4988_step_3();
    }
}


void a4988::a4988_delay(uint16_t angle)
{

    float step_angle;
    switch (mode)
    {
    case A4988_MODE_FULL:
        step_angle = 1.8;
        break;
    case A4988_MODE_HALF:
        step_angle = 0.9;
        break;
    case A4988_MODE_QUARTER:
        step_angle = 0.45;
        break;
    case A4988_MODE_EIGTH:
        step_angle = 0.225;
        break;
    case A4988_MODE_SIXTEENTH:
        step_angle = 0.1125;
        break;

    default:
        break;
    }

    delay((uint32_t)(angle/(freq*step_angle)*1000)+50);

}