//Components: metal detection, metal siren & led, motors, servos, electromagnets
/*KEYS:
- F: Forward
- B: Backwards
- R: Right
- L: Left
- S: Stop
- E: Edits speeds
---- S: set straight (F & B) speeds
---- T: set turing (R & L) speeds
- U: Servos Up
- D: Servos Down
- O: Electromagnets Open
- C: Electromagnets Close
*/

#include <Servo.h>

#define m1 12
#define PWM1 9
#define m2 8
#define PWM2 10

#define metal_siren_pin 13
#define metal_detector_pin A0

#define electromagnet_control_pin 12
#define servoR_pin 6
#define servoL_pin 5

char val;
int PWM_STRAIGHT = 50;
int PWM_TURNING = 75;
int PWM_STOP = 0;

Servo servoR;
Servo servoL;

int servoR_pos = 0;
int servoL_pos = 180;

bool is_metal_detected(){
  if (analogRead(metal_detector_pin)>4.5) return true;
  else return false;
}

void forward(){
  analogWrite(PWM1, PWM_STRAIGHT);
  analogWrite(PWM2, PWM_STRAIGHT);  
  digitalWrite(m1, HIGH);
  digitalWrite(m2, HIGH);
}

void backward(){
  analogWrite(PWM1, PWM_STRAIGHT);
  analogWrite(PWM2, PWM_STRAIGHT); 
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
}

void stop(){
  analogWrite(PWM1, PWM_STOP);
  analogWrite(PWM2, PWM_STOP);
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
}

void left(){
  analogWrite(PWM1, PWM_TURNING);
  analogWrite(PWM2, PWM_TURNING); 
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
}

void right(){
  analogWrite(PWM1, PWM_TURNING);
  analogWrite(PWM2, PWM_TURNING); 
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
}

void up(){
  if ((servoR_pos>=180) or (servoL_pos<=0)){
      return;
  }
  else{
    servoR_pos += 1;
    servoL_pos -= 1;
    servoR.write(servoR_pos);
    servoL.write(servoL_pos);
    delay(15);
  }
}

void down(){
  if ((servoL_pos>=180) or (servoR_pos<=0)){
      return;
  }
  else{
    servoR_pos -= 1;
    servoL_pos += 1;
    servoR.write(servoR_pos);
    servoL.write(servoL_pos);
    delay(15);
  }
}

void open(){
  digitalWrite(electromagnet_control_pin, HIGH);
}

void close(){
  digitalWrite(electromagnet_control_pin, LOW);
}

void blink(){
  digitalWrite(metal_siren_pin, HIGH);
  delay(3000);
  digitalWrite(metal_siren_pin, LOW);
}

void setup(){
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  analogWrite(PWM1, PWM_STOP);
  analogWrite(PWM2, PWM_STOP);
  
  pinMode(metal_detector_pin, INPUT);
  pinMode(metal_siren_pin, OUTPUT);
  digitalWrite(metal_siren_pin, LOW);

  pinMode(electromagnet_control_pin, OUTPUT);
  digitalWrite(electromagnet_control_pin, LOW);

  servoR.attach(5);
  servoL.attach(6);
  servoR.write(servoR_pos);
  servoL.write(servoL_pos);
  delay(1000);
}

void loop(){
  while (Serial.available() > 0){
    val = Serial.read();
    Serial.println(val);
  }

  if(val == 'F') forward();
  else if(val == 'B') backward();
  else if(val == 'L') left();
  else if(val == 'R') right();
  else if(val == 'S') stop();
  else if(val == 'U') up();
  else if(val == 'D') down();
  else if(val == 'O') open();
  else if(val == 'C') close();
  //else if(val == 'E'){}

  if(is_metal_detected()){
    stop();
    blink();
    //update_map();
  }
  
}
