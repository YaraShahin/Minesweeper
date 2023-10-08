#define mR 12
#define PWMR 9
#define mL 8
#define PWML 10

char val;
int PWM_STRAIGHT = 255;
int PWM_TURNING = 255;
int PWM_STOP = 0;

void motorCommand(int right_pwm, int left_pwm, bool right_dir, bool left_dir){
  analogWrite(PWMR, right_pwm);
  analogWrite(PWML, left_pwm);
  digitalWrite(mR, right_dir);
  digitalWrite(mR, left_dir);
}

void setup(){
  Serial.begin(9600);
  
  //motor pin definitions
  pinMode(mR, OUTPUT);
  pinMode(mL, OUTPUT);
  pinMode(PWMR,OUTPUT);
  pinMode(PWML,OUTPUT);
  motorCommand(PWM_STOP, PWM_STOP, 0, 0);
}

void loop(){
  //**BLUETOOTH + LOCOMOTION**//
  while (Serial.available() > 0){
    val = Serial.read();
    Serial.println(val);
  }

  if(val == 'F') motorCommand(PWM_STRAIGHT, PWM_STRAIGHT, 1, 1);
  else if(val == 'B') motorCommand(PWM_STRAIGHT, PWM_STRAIGHT, 0, 0);
  else if(val == 'L') motorCommand(PWM_TURNING, PWM_TURNING, 0, 1);
  else if(val == 'R') motorCommand(PWM_TURNING, PWM_TURNING, 1, 0);
  else if(val == 'S') motorCommand(PWM_STOP, PWM_STOP, 0, 0);
}
