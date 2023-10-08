/*KEYS:
- F: Forward
- B: Backwards
- R: Right
- L: Left
- S: Stop
- W: Siren on
- w: Siren off
- U: Electromagnets Open
- u: Electromagnets Close
*/
#define mR 12
#define PWMR 11
#define mL 8
#define PWML 3
#define metal_detector_pin  A0
#define siren_pin 7
#define electromagnets_pin 6

char val;
int PWM_STRAIGHT = 120;
int PWM_TURNING_HIGH = 240;
int PWM_TURNING_LOW = 80;
int PWM_STOP = 0;
int metal_threshold = 920;
bool flag = false;

void motorCommand(int right_pwm, int left_pwm, bool right_dir, bool left_dir){
  if (right_dir) digitalWrite(mR, HIGH);
  else digitalWrite(mR, LOW);
  if (left_dir) digitalWrite(mL, HIGH);
  else digitalWrite(mL, LOW);
  analogWrite(PWMR, right_pwm);
  analogWrite(PWML, left_pwm);
}

void blink(){
  digitalWrite(siren_pin, HIGH);
  delay(3000);
  digitalWrite(siren_pin, LOW);
}

void setup(){
  Serial.begin(9600);
  
  //motor pin definitions
  pinMode(mR, OUTPUT);
  pinMode(mL, OUTPUT);
  pinMode(PWMR,OUTPUT);
  pinMode(PWML,OUTPUT);
  motorCommand(PWM_STOP, PWM_STOP, 0, 0);

  //metal detection system definitions
  pinMode(metal_detector_pin, INPUT);
  pinMode(siren_pin, OUTPUT);
  pinMode(electromagnets_pin, OUTPUT);
}

void loop(){
  while (Serial.available() > 0) val = Serial.read();

  if(val == 'F') motorCommand(PWM_STRAIGHT, PWM_STRAIGHT, 0, 0);
  else if(val == 'B') motorCommand(PWM_STRAIGHT, PWM_STRAIGHT, 1, 1);
  else if(val == 'L') motorCommand(PWM_TURNING_LOW, PWM_TURNING_HIGH, 0, 0);
  else if(val == 'R') motorCommand(PWM_TURNING_HIGH, PWM_TURNING_LOW, 0, 0);
  else if(val == 'S') motorCommand(PWM_STOP, PWM_STOP, 0, 0);
  if(val == 'W'){
    digitalWrite(siren_pin, HIGH);
    flag = true;
  }
  else if (val == 'w'){
    digitalWrite(siren_pin, LOW);
    flag = false;
  }
  else if(val == 'U') digitalWrite(electromagnets_pin, HIGH);
  else if(val == 'u') digitalWrite(electromagnets_pin, LOW);

  if (val == '1') PWM_STRAIGHT = 80;
  else if (val == '2') PWM_STRAIGHT = 100;
  else if (val == '3') PWM_STRAIGHT = 120;
  else if (val == '4') PWM_STRAIGHT = 140;
  else if (val == '5') PWM_STRAIGHT = 160;
  else if (val == '6') PWM_STRAIGHT = 180;
  else if (val == '7') PWM_STRAIGHT = 200;
  else if (val == '8') PWM_STRAIGHT = 220;
  else if (val == '9') PWM_STRAIGHT = 250;
  else if (val == 'q') PWM_STRAIGHT = 250;

  if (analogRead(metal_detector_pin)>metal_threshold) digitalWrite(siren_pin, HIGH);
  else if (!flag) digitalWrite(siren_pin, LOW);
}
