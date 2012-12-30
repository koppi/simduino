# Simduino - run an Arduino sketch from the command-line

Features

* Test out a sketch without the hardware, or prior to purchasing hardware.

Supported Arduinos

* Atmega8

## Documentation

Checkout the Simduino repository:

```
$ git clone git://github.com/koppi/simduino.git
```

Build Simduino the test sketches:

```
$ cd simduino
$ make
 Building tests/Tutorial/00-BareMinimum
  cc main.cpp
  cc AccelStepper.cpp
  cc AFMotor.cpp
  cc Arduino.cpp
  cc HardwareSerial.cpp
  cc I2CIO.cpp
  cc LCD.cpp
  cc LCD_I2C.cpp
  cc Print.cpp
  cc Stream.cpp
  cc Wire.cpp
  cc WString.cpp
  ld libSimduino.a
 Built libSimduino.a
  ld 00-BareMinimum.exe
 Building tests/Tutorial/01-Blink
  cc main.cpp
  ld 01-Blink.exe
 Building tests/Tutorial/02-DigitalReadSerial
  cc main.cpp
  ld 02-DigitalReadSerial.exe
[...]
```

Run a test sketch from the command-line:

```
$ tests/AccelStepper/Bounce/Bounce.exe
 pinMode(2, 1)
 pinMode(3, 1)
 pinMode(4, 1)
 pinMode(5, 1)
setup() begin
setup() end
loop() enter
 digitalWrite(2, 0)
 digitalWrite(3, 1)
 digitalWrite(4, 1)
 digitalWrite(5, 0)
 digitalWrite(2, 0)
 digitalWrite(3, 1)
 digitalWrite(4, 0)
 digitalWrite(5, 1)
[...]
^C shutdown(2)
```

Press CTRL+C to terminate the program. Have fun!

# Authors

* © 2012-2013 [Jakob Flierl](https://github.com/koppi)
