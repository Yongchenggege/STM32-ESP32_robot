#ifndef __a4988_H
#define __a4988_H

#include<Arduino.h>

#define A4988_EN        19
#define A4988_STEP_1    21//底盘
#define A4988_STEP_2    14//关节1
#define A4988_STEP_3    27//关节2
#define A4988_DIR       15
#define A4988_MS0       23
#define A4988_MS1       12
#define A4988_MS2       13

typedef enum a4988_mode_{
    A4988_MODE_FULL,
    A4988_MODE_HALF,
    A4988_MODE_QUARTER,
    A4988_MODE_EIGTH,
    A4988_MODE_SIXTEENTH,
}a4988_mode;//枚举为了定义一类的变量，枚举名就是类名

class a4988{
public:
    a4988(){
        pinMode(A4988_EN,OUTPUT);
        pinMode(A4988_STEP_1,OUTPUT);
        pinMode(A4988_STEP_2,OUTPUT);
        pinMode(A4988_STEP_3,OUTPUT);
        pinMode(A4988_DIR,OUTPUT);
        pinMode(A4988_MS0,OUTPUT);
        pinMode(A4988_MS1,OUTPUT);
        pinMode(A4988_MS2,OUTPUT);

        digitalWrite(A4988_EN,HIGH);
        digitalWrite(A4988_STEP_1,LOW);
        digitalWrite(A4988_STEP_2,LOW);
        digitalWrite(A4988_STEP_3,LOW);
        digitalWrite(A4988_DIR,LOW);
        digitalWrite(A4988_MS0,LOW);
        digitalWrite(A4988_MS1,LOW);
        digitalWrite(A4988_MS2,LOW);

        mode = A4988_MODE_FULL;
        init_mode = 0;
    };

    a4988(uint32_t freq){
        pinMode(A4988_EN,OUTPUT);
        pinMode(A4988_STEP_1,OUTPUT);
        pinMode(A4988_STEP_2,OUTPUT);
        pinMode(A4988_STEP_3,OUTPUT);
        pinMode(A4988_DIR,OUTPUT);
        pinMode(A4988_MS0,OUTPUT);
        pinMode(A4988_MS1,OUTPUT);
        pinMode(A4988_MS2,OUTPUT);

        digitalWrite(A4988_EN,HIGH);
        digitalWrite(A4988_STEP_1,LOW);
        digitalWrite(A4988_STEP_2,LOW);
        digitalWrite(A4988_STEP_3,LOW);
        digitalWrite(A4988_DIR,LOW);
        digitalWrite(A4988_MS0,LOW);
        digitalWrite(A4988_MS1,LOW);
        digitalWrite(A4988_MS2,LOW);

        ledcSetup(0,freq,10);
        ledcAttachPin(A4988_STEP_1,0);
        ledcWrite(0,0);

        ledcSetup(1,freq,10);
        ledcAttachPin(A4988_STEP_2,1);
        ledcWrite(1,0);

        ledcSetup(2,freq,10);
        ledcAttachPin(A4988_STEP_3,2);
        ledcWrite(2,0);

        mode = A4988_MODE_FULL;
        this->freq = freq;
        init_mode = 1;
    };

    void a4988_dir(bool mode);

    void a4988_mode(uint8_t mode);

    void a4988_en(bool status);

    void a4988_step_1(void);//底座步

    void a4988_step_2(void);//关节1步

    void a4988_step_3(void);//关节2步

    void a4988_angle_1(uint16_t angle);//底座角

    void a4988_angle_2(uint16_t angle);//关节1角

    void a4988_angle_3(uint16_t angle);//关节1角

    void a4988_delay(uint16_t angle);
    
private:
    uint8_t mode;
    uint8_t init_mode;
    uint32_t freq;
};

#endif
