# Test touch input for Death Clock control
# Uses Pi GPIO library http://abyz.me.uk/rpi/pigpio
# Run "sudo pigpiod" before launching

import pigpio
import time

pi = pigpio.pi()
if pi.connected:
  pi.set_mode(21, pigpio.INPUT)
  pi.set_pull_up_down(21, pigpio.PUD_UP)
  while True:
    print(pi.read(21))
    time.sleep(0.5)
else:
  print("Unable to connect to Pi GPIO Daemon.")