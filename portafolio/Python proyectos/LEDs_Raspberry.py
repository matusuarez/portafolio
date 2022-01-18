import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
PIN_LEDS = [11, 13, 15, 19]
for i in PIN_LEDS:
    GPIO.setup(i, GPIO.OUT, initial=GPIO.LOW)
    PIN_BOTON = 22
GPIO.setup(PIN_BOTON, GPIO.IN, pull_up_down=GPIO.PUD_UP)
def binario(n):
    resultado = []
    for i in range(4):
        resultado.append(n & 1)
        n >>= 1
    return resultado
    contador = 0
try:
    while True:
        if GPIO.input(PIN_BOTON) == GPIO.LOW:
            contador += 1
            if contador == 11:
                contador = 0
            for pin, bit in zip(PIN_LEDS, binario(contador)):
                GPIO.output(pin, bit)
            time.sleep(0.3)
finally:
    GPIO.cleanup()