# Death Clock control program for Raspberry Pi
# Uses Pi GPIO library http://abyz.me.uk/rpi/pigpio
# Run "sudo pigpiod" before launching

import pigpio
import time
import keyboard
from datetime import datetime

all_black = b'\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF'

eye_open  = b'\xFF\x03\x9C\x03\xFF\x03\xFF\x03\xFF\x03\x9C\x03\xFF\x03\xFF\x03'
eye_smile = b'\xFF\x03\xDC\x03\xFF\x03\xFF\x03\xFF\x03\xDC\x03\xFF\x03\xFF\x03'
eye_sleep = b'\xFF\x03\x9D\x03\xFF\x03\xFF\x03\xFF\x03\x9D\x03\xFF\x03\xFF\x03'
eye_close = b'\xFF\x03\xBF\x03\xFF\x03\xFF\x03\xFF\x03\xBF\x03\xFF\x03\xFF\x03'

smile_l   = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xF7\x03\xFF\x03\xFF\x03\xFF\x03'
smile_r   = b'\xFF\x03\xFF\x03\xF7\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'

sun       = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x02\xFF\x03'
mon       = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x02\xFF\x03\xFF\x03'
tue       = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x02\xFF\x03\xFF\x03\xFF\x03'
wed       = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x02\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
thu       = b'\xFF\x03\xFF\x03\xFF\x02\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
fri       = b'\xFF\x03\xFF\x02\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
sat       = b'\xFF\x02\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'

weekday = (sun, mon, tue, wed, thu, fri, sat)

am        = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFB\x03\xFF\x03'
pm        = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xF7\x03\xFF\x03'

on        = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFB\x03'
off       = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xF7\x03'

otr       = b'\xFE\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
clock     = b'\xFD\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
ch        = b'\xFB\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
dot       = b'\xF7\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
w         = b'\x7F\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'

num1      = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\x7F\x03'
num2      = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\x7F\x03\xFF\x03'
num3      = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\x7F\x03\xFF\x03\xFF\x03'
num4      = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\x7F\x03\xFF\x03\xFF\x03\xFF\x03'
num5      = b'\xFF\x03\xFF\x03\xFF\x03\x7F\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
num6      = b'\xFF\x03\xFF\x03\x7F\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
num7      = b'\xFF\x03\x7F\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'

numbers = (all_black, num1, num2, num3, num4, num5, num6, num7)

rectr     = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFE\x03'
rectl     = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFD\x03'

def millis():
  """
  Arbitrary time scale used for timing. Intended to roughly approximate
  millis() in Arduino
  """
  return time.perf_counter_ns() // 1000000

def bytes_and(bytes1, bytes2):
  combined = bytearray()
  for b1,b2 in zip(bytes1, bytes2):
    combined.append(b1 & b2)
  return bytes(combined)

class touch:
  """
  Represents input from touch sensor. Substitute with key press when GPIO
  is absent.
  """
  def __init__(self, pi):
    self.pi = pi
    if self.pi.connected:
      print("Pi GPIO connected, will try to read GPIO21")
      self.pi.set_mode(21, pigpio.INPUT)
      self.pi.set_pull_up_down(21, pigpio.PUD_UP) # Internal pullup, look for ground
    else:
      print("Pi GPIO not connected, will read space bar")

  def detected(self):
    if self.pi.connected:
      # Touch detected when pin 21, set to internal pull-up, is low.
      return 0 == self.pi.read(21)
    else:
      return keyboard.is_pressed(' ')

class nyancat:
  frames = (
    b'\xFF\x02\xA3\x03\xB7\x03\x7F\x01\xBE\x03\xBE\x03\xFB\x03\xFB\x03',
    b'\xFF\x03\xA3\x02\xB7\x03\xFF\x01\x3E\x03\xBE\x03\xFB\x03\xFB\x03',
    b'\xFF\x03\xFF\x03\xA3\x02\xFF\x01\xB7\x03\x3E\x03\xFB\x03\xFB\x03',
    b'\xFF\x03\xFF\x03\xA3\x03\xFF\x00\xB7\x03\xB7\x03\x7B\x03\xFB\x03',
    b'\xFF\x03\xFF\x03\x9C\x03\xFF\x01\xB7\x02\xB7\x03\xF7\x03\x7B\x03',
    b'\x7F\x03\xFF\x03\x9C\x03\xFF\x01\xBE\x03\xB7\x02\xF7\x03\xF7\x03',
    b'\xFF\x03\x1C\x03\xBE\x03\xFF\x01\xBE\x03\xBE\x03\xF7\x02\xF7\x03',
    b'\xFF\x03\x9C\x03\x3E\x03\xFF\x01\xBE\x03\xBE\x03\xFB\x03\xF4\x03'
  ) 

  def __init__(self):
    self.reset()
    
  def reset(self):
    self.frame_index = 0
    self.next_frame_time = millis()

  def current_frame(self):
    if millis() > self.next_frame_time:
      self.next_frame_time = millis() + 100
      self.frame_index = self.frame_index + 1
      if self.frame_index >= len(self.frames):
        self.frame_index = 0
    return self.frames[self.frame_index]

class deathclock:
  def __init__(self):
    self.pi = pigpio.pi()
    if self.pi.connected:
      print("Pi GPIO connected, will send bytes via I2C")
      self.p = self.pi.i2c_open(1,0x42)
    else:
      print("Pi GPIO not connected, will print byte patterns")
    # Initialize screen to all black
    self.send(0x00,b'\x08\x0A\x20\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF')
    self.prev_frame = all_black

  def send(self, offset, pattern):
    """
    Send the given pattern at the given offset to I2C device.
    If no device, print out to stdout.
    """
    if self.pi.connected:
      self.pi.i2c_write_i2c_block_data(self.p,offset,pattern)
    else:
      #print("Offset {} Data {}".format(offset, ''.join('{:02x}'.format(x) for x in pattern)))
      print(''.join('{:02x}'.format(x) for x in pattern))

  def close(self):
    """
    If Pi GPIO objects are connected, disconnect and close.
    """
    if self.pi.connected:
      self.pi.i2c_close(self.p)
      self.pi.stop()

  def run(self):
    state = "start"
    touch_sensor = touch(self.pi)
    try:
      while True:
        if state == "start":
          nc = nyancat()
          nc.reset()
          prev_frame = all_black
          state = "attract"
        elif state == "attract":
          # No touch detected, continue running attract animation
          frame = nc.current_frame()
          if frame != prev_frame:
            self.send(0x04, frame)
            prev_frame = frame
          time.sleep(0.025)

          if touch_sensor.detected():
            # Touch detected, move on to next state.
            state = "thinking"
        elif state == "thinking":
          self.send(0x04, bytes_and(eye_open, smile_r))
          time.sleep(0.75)
          self.send(0x04, bytes_and(eye_close, smile_r))
          time.sleep(0.15)
          self.send(0x04, bytes_and(eye_open, smile_r))
          time.sleep(0.75)
          self.send(0x04, bytes_and(eye_close, smile_r))
          time.sleep(0.15)
          self.send(0x04, bytes_and(eye_smile, smile_r))
          time.sleep(1.00)
          while touch_sensor.detected():
            # Don't move on until finger has released
            state = "thinking"
          state = "display"
        elif state == "display":
          self.send(0x04, all_black)
          time.sleep(5)
          state = "attract"
        else:
          print("Error - state {} found no takers. Typo?".format(state))
          state = "start"
    except KeyboardInterrupt:
      self.close()

if __name__ == "__main__":
  dc = deathclock()
  dc.run()
