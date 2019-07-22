import i2cdriver
import time

i2c = i2cdriver.I2CDriver("COM21")

while True:


    t0 = int(round(time.time() * 1000))

    i2c.start(0x35, 0)
    i2c.write([0x69])
    i2c.stop()

    value = i2c.read(2)

    t1 = int(round(time.time() * 1000))
    total = t1-t0
    print('value: ' + str(value) + 'time: ' + str(time)
