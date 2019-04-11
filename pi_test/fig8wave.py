# Program to test VFD driver project on Raspberry Pi
# Run "sudo pigpiod" before launching

import pigpio
import time

pi = pigpio.pi()
p = pi.i2c_open(1,0x42)
pi.i2c_write_i2c_block_data(p,0x00,b'\x08\x0A\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00')

marquee_text = b'\x81\x01\x02\x01\x40\x02\x10\x02\x08\x04\x04\x04\x40\x02\x20\x02\x81\x01\x02\x01\x40\x02\x10\x02\x08\x04\x04\x04\x40\x02\x20\x02' # Figure 8 wave

scroll_range = range(0,len(marquee_text)-16,2)

while True:
    for position in scroll_range:
        pi.i2c_write_i2c_block_data(p,0x04,marquee_text[position:position+16])
        time.sleep(0.05)

pi.i2c_close(p)
pi.stop()