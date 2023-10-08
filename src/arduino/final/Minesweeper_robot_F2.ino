/*KEYS:
- V: servo up
- v: Servo stop
- X: servo down
- x: servo stop
*/
#define servoR_pin 3
#define servoL_pin 5
#include <Servo.h>

Servo servoR;
Servo servoL;

char val;

void setServosAngle(int servoR_pos, int servoL_pos){
  servoR.write(servoR_pos);
  servoL.write(servoL_pos);
}

void setup(){
  Serial.begin(9600);

  //servo initializations
  servoR.attach(servoR_pin);
  servoL.attach(servoL_pin);
  setServosAngle(90, 90);
  delay(15);
  
}

void loop(){
  while (Serial.available() > 0) val = Serial.read();
  Serial.println(val);
  if(val == 'F'){
    setServosAngle(110, 70);
    delay(600);
    setServosAngle(90, 90);
  }
  else if(val == 'B'){
    setServosAngle(70, 110);
    delay(600);
    setServosAngle(90, 90);
  }/*
  else if (val == 'v') 
  else if (val == 'x') setServosAngle(90, 90);*/
}
