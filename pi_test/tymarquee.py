# Program to test VFD driver project on Raspberry Pi
# Run "sudo pigpiod" before launching

import pigpio

pi = pigpio.pi()
p = pi.i2c_open(1,0x42)
pi.i2c_write_i2c_block_data(p,0x00,b'\x08\x0A\xF0\x00\x74\x00\x79\x00\x36\x00\x5c\x00\x77\x00\x74\x00\x5c\x00\x6e\x00')