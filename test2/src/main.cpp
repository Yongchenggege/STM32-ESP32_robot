#include <Arduino.h>
// #include "uln2003.h"
#include <CheapStepper.h>
#include "a4988.h"
#include "uart.h"


usart_cmd_pack pack;
CheapStepper stepper (2,4,5,18); //IN1-4
a4988 motor2(1000);

void usart2();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin (115200);  
  motor2.a4988_en(1);
  motor2.a4988_mode(A4988_MODE_SIXTEENTH);
  stepper.setRpm(20);

}

void loop() {
  // put your main code here, to run repeatedly:

    
  usart2();
  delay(10);

}

void usart2()
{
  if(Serial2.available() >= 3) {
    Serial.println("usart2");
    pack.head = Serial2.read();
    if(pack.head == 0xAA) {
      pack.data[0] = Serial2.read();
      pack.end = Serial2.read();
      if(pack.end == 0xBB) {
        switch(pack.data[0]) {
          case 0x01://底座正转45度
          motor2.a4988_dir(1);
          motor2.a4988_angle_1(45);
            break;
          case 0x02://底座反转45度
          motor2.a4988_dir(0);
          motor2.a4988_angle_1(45);
            break;
          case 0x03:
          stepper.move(false,768);//开爪45°
            break;
          case 0x04:
          stepper.move(true,768);//收爪45°
            break;
          case 0x05://关节1正转45度
          motor2.a4988_dir(1);
          motor2.a4988_angle_2(45);
            break;
          case 0x06://关节1反转45度
          motor2.a4988_dir(0);
          motor2.a4988_angle_2(45);
            break;
          case 0x07://关节2正转45度
          motor2.a4988_dir(1);
          motor2.a4988_angle_3(45);
            break;
          case 0x08://关节2反转45度
          motor2.a4988_dir(0);
          motor2.a4988_angle_3(45);
            break;



          // case 0x05:
          // loop_stop();
          // break;


          default:
            break;
        }
      }else {
        Serial.println("无效包");
      }
    }
  }
}