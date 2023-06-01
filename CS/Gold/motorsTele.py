import RPi.GPIO as gpio
import time as t

m1a = 1
m1b = 7
m1 = 12
m2a = 8
m2b = 25
m2 = 13


speed1 = 20
speed2 = 20

gpio.setmode(gpio.BCM)
gpio.setup(m1, gpio.OUT)
gpio.setup(m2, gpio.OUT)
gpio.setup(m1a, gpio.OUT)
gpio.setup(m1b, gpio.OUT)
gpio.setup(m2a, gpio.OUT)
gpio.setup(m2b, gpio.OUT)
p1 = gpio.PWM(m1, 1000)
p2 = gpio.PWM(m2, 1000)
p1.start(50)
p2.start(50)

#Motor 1 and 2 forward
def forward(secs = 60):
#     start = t.time()
#     while t.time()-start<secs:
        p1.ChangeDutyCycle(50)
        p2.ChangeDutyCycle(50)
        gpio.output(m1a, gpio.HIGH)
        gpio.output(m1b, gpio.LOW)
        gpio.output(m2a, gpio.HIGH)
        gpio.output(m2b, gpio.LOW)
    
def reverse(secs = 60):
#     start = time.time()
#     while time.time()-start<secs:
        p1.ChangeDutyCycle(50)
        p2.ChangeDutyCycle(50)
        gpio.output(m1a, gpio.LOW)
        gpio.output(m1b, gpio.HIGH)
        gpio.output(m2a, gpio.LOW)
        gpio.output(m2b, gpio.HIGH)
 
def right(secs = 60):
#     start = t.time()
#     while t.time()-start<secs:
        p1.ChangeDutyCycle(70)
        p2.ChangeDutyCycle(70)
        gpio.output(m1a, gpio.HIGH)
        gpio.output(m1b, gpio.LOW)
        gpio.output(m2a, gpio.LOW)
        gpio.output(m2b, gpio.HIGH)

def left(secs = 60):
#     start = t.time()
#     while t.time()-start<secs:
        p1.ChangeDutyCycle(70)
        p2.ChangeDutyCycle(80)
        gpio.output(m1a, gpio.LOW)
        gpio.output(m1b, gpio.HIGH)
        gpio.output(m2a, gpio.HIGH)
        gpio.output(m2b, gpio.LOW)

def stop():
    gpio.output(m1a, gpio.LOW)
    gpio.output(m1b, gpio.LOW)
    gpio.output(m2a, gpio.LOW)
    gpio.output(m2b, gpio.LOW)
    

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
