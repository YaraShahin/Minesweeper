import RPi.GPIO as gpio
import time as t

m1 = 25
m1_pwm = 8
m2 = 7
m2_pwm = 1

speed1 = 20
off_speed1 = 20
speed2 = 20
off_speed2 = 20

gpio.setmode(gpio.BCM)
gpio.setup(m1, gpio.OUT)
gpio.setup(m1_pwm, gpio.OUT)
gpio.setup(m2, gpio.OUT)
gpio.setup(m2_pwm, gpio.OUT)

p1 = gpio.PWM(m1_pwm, 1000)
p2 = gpio.PWM(m2_pwm, 1000)

p1.start(0)
p2.start(0)

"""
for cytron:

--------  m1   m1_pwm   m2   m2_pwm 
Forward   1       1      1      1
Right     1       1      0      1
Left      0       1      1      1
Stop      x       0      x      0
Reverse   0       1      0      1
"""


#Motor 1 and 2 forward
def forward(secs = 60):
#     start = t.time()
#     while t.time()-start<secs:
        p1.ChangeDutyCycle(speed1)
        p2.ChangeDutyCycle(speed2)
        gpio.output(m1, gpio.HIGH)
        gpio.output(m2, gpio.HIGH)
        
def reverse(secs = 60):
#     start = time.time()
#     while time.time()-start<secs:
        p1.ChangeDutyCycle(speed1)
        p2.ChangeDutyCycle(speed2)
        gpio.output(m1, gpio.LOW)
        gpio.output(m2, gpio.LOW)
 
def right(secs = 60):
#     start = t.time()
#     while t.time()-start<secs:
        p1.ChangeDutyCycle(speed1+off_speed1)
        p2.ChangeDutyCycle(speed2+off_speed2)
        gpio.output(m1, gpio.HIGH)
        gpio.output(m2, gpio.LOW)

def left(secs = 60):
#     start = t.time()
#     while t.time()-start<secs:
        p1.ChangeDutyCycle(speed1+off_speed1)
        p2.ChangeDutyCycle(speed2+off_speed2)
        gpio.output(m1, gpio.LOW)
        gpio.output(m2, gpio.HIGH)
        
def stop():
    p1.ChangeDutyCycle(0)
    p2.ChangeDutyCycle(0)

def init():
    gpio.setmode(gpio.BCM)
    gpio.setup(m1, gpio.OUT)
    gpio.setup(m1_pwm, gpio.OUT)
    gpio.setup(m2, gpio.OUT)
    gpio.setup(m2_pwm, gpio.OUT)

    p1 = gpio.PWM(m1_pwm, 1000)
    p2 = gpio.PWM(m2_pwm, 1000)

    p1.start(50)
    p2.start(50)

    t.sleep(3)

    p1.ChangeDutyCycle(0)
    p2.ChangeDutyCycle(0)



if __name__ == '__main__':
    #init()
    while True:
        v = input("enter direction: f, rev, ri, l, s: ")
        if (v=='f'):
            forward()
        elif (v=="rev"):
            reverse()
        elif (v=="ri"):
            right()
        elif (v=='l'):
            left()
        else:
            stop()
