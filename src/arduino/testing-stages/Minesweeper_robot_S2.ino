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
#define PWMR 9
#define mL 8
#define PWML 10
#define metal_detector_pin  A0
#define siren_pin 7
#define electromagnets_pin 6

char val;
int PWM_STRAIGHT = 120;
int PWM_TURNING = 150;
int PWM_STOP = 0;
int metal_threshold = 920;

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

  if(val == 'F') motorCommand(PWM_STRAIGHT, PWM_STRAIGHT, 1, 1);
  else if(val == 'B') motorCommand(PWM_STRAIGHT, PWM_STRAIGHT, 0, 0);
  else if(val == 'L') motorCommand(PWM_TURNING, PWM_TURNING, 0, 1);
  else if(val == 'R') motorCommand(PWM_TURNING, PWM_TURNING, 1, 0);
  else if(val == 'S') motorCommand(PWM_STOP, PWM_STOP, 0, 0);
  if(val == 'W') blink();
  else if(val == 'U') digitalWrite(electromagnets_pin, HIGH);
  else if(val == 'u') digitalWrite(electromagnets_pin, LOW);

  if (analogRead(metal_detector_pin)>metal_threshold) blink();
}
