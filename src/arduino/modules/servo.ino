//Full round rotation (0->180->0 for two servos together (opposite directions))
#define servoR_pin 9
#define servoL_pin 10
#include <Servo.h>

Servo servoR;
Servo servoL;

void setServosAngle(int servoR_pos, int servoL_pos){
  servoR.write(servoR_pos);
  servoL.write(servoL_pos);
}

void setup() {
  servoR.attach(servoR_pin);
  servoL.attach(servoL_pin);
  delay(15);
  setServosAngle(70, 110);
  delay(15);
}
void loop(){}
/*
void loop() {
  //initial position
  int servoR_pos = 45;
  int servoL_pos = 90;
  setServosAngle(servoR_pos, servoL_pos);
  delay(150);

  //full rotation cw
  while (true){
    servoR_pos += 1;
    servoL_pos -= 1;
    if ((servoR_pos==90) or (servoL_pos==45)){
      break;
    }
    setServosAngle(servoR_pos, servoL_pos);
    delay(15); 
  }
  delay(150);

  //initial position
  servoR_pos = 90;
  servoL_pos = 45;
  setServosAngle(servoR_pos, servoL_pos);
  delay(150);

  //full rotation ccw
  while (true){
    servoR_pos -= 1;
    servoL_pos += 1;
    if ((servoR_pos==45) or (servoL_pos==90)){
      break;
    }
    setServosAngle(servoR_pos, servoL_pos);
    delay(15); 
  }
  delay(150);
}
*/