import i2cdriver
import time

i2c =  i2cdriver.I2CDriver('COM4')

while True:
    time0 = time.time()

    i2c.start(0x35,0)
    i2c.write([0x69])
    i2c.stop()

    i2c.start(0x35,1)
    command = i2c.read(2)
    print(command)

    time1 = time.time()
    total = time1 - time0
    print(total)
