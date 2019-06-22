# Death Clock control program for Raspberry Pi
# Uses Pi GPIO library http://abyz.me.uk/rpi/pigpio
# Run "sudo pigpiod" before launching

import pigpio
import keyboard

import time
from datetime import datetime

import random

all_black = b'\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF'

eye_open  = b'\xFF\x03\x9C\x03\xFF\x03\xFF\x03\xFF\x03\x9C\x03\xFF\x03\xFF\x03'
eye_smile = b'\xFF\x03\xDC\x03\xFF\x03\xFF\x03\xFF\x03\xDC\x03\xFF\x03\xFF\x03'
eye_sleep = b'\xFF\x03\x9D\x03\xFF\x03\xFF\x03\xFF\x03\x9D\x03\xFF\x03\xFF\x03'
eye_close = b'\xFF\x03\xBF\x03\xFF\x03\xFF\x03\xFF\x03\xBF\x03\xFF\x03\xFF\x03'

smile_l   = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xF7\x03\xFF\x03\xFF\x03\xFF\x03'
smile_r   = b'\xFF\x03\xFF\x03\xF7\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'

on        = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFB\x03'
off       = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xF7\x03'

otr       = b'\xFE\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
clock     = b'\xFD\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
ch        = b'\xFB\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
dot       = b'\xF7\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
w         = b'\x7F\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'

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
    self.frame_index = 0
    self.next_frame_time = millis()

  def current_frame(self):
    if millis() > self.next_frame_time:
      self.next_frame_time = millis() + 100
      self.frame_index = self.frame_index + 1
      if self.frame_index >= len(self.frames):
        self.frame_index = 0
    return self.frames[self.frame_index]

class thinkingface:
  frames = (
    (1000, eye_open, smile_r),
    (150, eye_close, smile_r),
    (500, eye_open, smile_r),
    (100, eye_close, smile_r),
    (1000, eye_smile, smile_r)
  )

  def __init__(self):
    self.complete = False
    self.frame_index = 0
    self.next_frame_time = millis()

  def completed(self):
    return self.complete

  def current_frame(self):
    if not self.complete:
      if millis() > self.next_frame_time:
        new_frame_index = self.frame_index + 1
        if new_frame_index >= len(self.frames):
          # We are done - do not increment frame count
          self.complete = True
        else:
          self.next_frame_time = millis() + self.frames[new_frame_index][0]
          self.frame_index = new_frame_index
    
    frame = all_black

    for element in self.frames[self.frame_index][1:]:
      frame = bytes_and(frame, element)

    return frame

class deathtime:
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
  ampm = (am, pm)

  digit0    = 0xC0
  digit1    = 0xF9
  digit2    = 0xA4
  digit3    = 0xB0
  digit4    = 0x99
  digit5    = 0x92
  digit6    = 0x82
  digit7    = 0xF8
  digit8    = 0x80
  digit9    = 0x90
  digits = (digit0,digit1,digit2,digit3,digit4,digit5,digit6,digit7,digit8,digit9)

  colon     = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x01\xFF\x03\xFF\x03\xFF\x03\xFF\x03'

  num1      = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\x7F\x03'
  num2      = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\x7F\x03\xFF\x03'
  num3      = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\x7F\x03\xFF\x03\xFF\x03'
  num4      = b'\xFF\x03\xFF\x03\xFF\x03\xFF\x03\x7F\x03\xFF\x03\xFF\x03\xFF\x03'
  num5      = b'\xFF\x03\xFF\x03\xFF\x03\x7F\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
  num6      = b'\xFF\x03\xFF\x03\x7F\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'
  num7      = b'\xFF\x03\x7F\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03\xFF\x03'

  numbers = (all_black, num1, num2, num3, num4, num5, num6, num7)

  def __init__(self):
    # Start with a day of the week combined with AM or PM
    self.frame = bytes_and(self.weekday[random.randint(0,6)], self.ampm[random.randint(0,1)])

    timedigits = bytearray(all_black)
    # Fill in digits
    deathhour = random.randint(1,12)
    if deathhour >= 10:
      timedigits[10] = self.digit1
    timedigits[8] = self.digits[deathhour%10]

    deathminute = random.randint(0,59)
    if deathminute < 10:
      timedigits[4] = self.digit0
    else:
      timedigits[4] = self.digits[deathminute // 10]
    timedigits[2] = self.digits[deathminute % 10]

    self.frame = bytes_and(self.frame, timedigits)

    self.countdown = len(self.numbers)
    self.complete = False
    self.next_frame_time = 0

  def completed(self):
    return self.complete

  def current_frame(self):
    if not self.complete:
      if millis() > self.next_frame_time:
        self.countdown = self.countdown - 1
        self.next_frame_time = millis() + 1000
        if self.countdown == 0:
          self.complete = True

    displayframe = bytes_and(self.frame, self.numbers[self.countdown])

    if self.countdown % 2 == 1:
      displayframe = bytes_and(displayframe, self.colon)

    return displayframe

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
          # Set things up for the attraction loop
          nc = nyancat()
          prev_frame = all_black
          state = "attract"
        elif state == "attract":
          # Attraction state has to run in a non-blocking loop
          # so we could check touch sensor in between animating
          # frames.
          frame = nc.current_frame()
          if frame != prev_frame:
            self.send(0x04, frame)
            prev_frame = frame
          time.sleep(0.025)

          if touch_sensor.detected():
            # Touch detected, move on to next state.
            face = thinkingface()
            state = "thinking"
        elif state == "thinking":
          frame = face.current_frame()
          if frame != prev_frame:
            self.send(0x04, frame)
            prev_frame = frame
          time.sleep(0.025)

          # Don't move on until we have both of the following:
          # 1: Animation has completed
          # 2: Touch has released
          if face.completed() and not touch_sensor.detected():
            dt = deathtime()
            state = "display"
        elif state == "display":
          frame = dt.current_frame()
          if frame != prev_frame:
            self.send(0x04, frame)
            prev_frame = frame
          time.sleep(0.25)
          if dt.completed():
            state = "conclude"
        elif state == "conclude":
          self.send(0x04, all_black)
          prev_frame = all_black
          time.sleep(1)
          state = "attract"
        else:
          print("Error - state {} found no takers. Typo?".format(state))
          state = "start"
    except KeyboardInterrupt:
      self.close()

if __name__ == "__main__":
  dc = deathclock()
  dc.run()
