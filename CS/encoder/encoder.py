import RPi.GPIO as gpio
import time as t

encoder1 = 23
encoder2 = 24

lastEncoded = 0
encoderValue = 0

def encoder_isr():
    MSB = gpio.input(encoder1)
    LSB = gpio.input(encoder2)

    encoded = (MSB<<1) | LSB
    sum = (lastEncoded << 2) | encoded

    if(sum == 0b1101 or sum == 0b0100 or sum == 0b0010 or sum == 0b1011):
        encoderValue -= 1
    if(sum == 0b1110 or sum == 0b0111 or sum == 0b0001 or sum == 0b1000):
        encoderValue += 1

    lastEncoded = encoded

if __name__ == '__main__':
    gpio.setmode(gpio.BCM)
    gpio.setup(encoder1, gpio.IN, pull_up_down=gpio.PUD_UP)
    gpio.setup(encoder2, gpio.IN, pull_up_down=gpio.PUD_UP)

    gpio.add_event_detect(encoder1, gpio.BOTH, callback=encoder_isr, bouncetime=100)
    gpio.add_event_detect(encoder2, gpio.BOTH, callback=encoder_isr, bouncetime=100)

    while (True):
        print(encoderValue)
    