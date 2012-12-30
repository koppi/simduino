# Simduino - run an Arduino sketch from the command-line

Features

* Test out a sketch without the hardware, or prior to purchasing hardware.

Supported Arduinos

* Atmega8

## Documentation

Checkout the simduino repository:

```
$ git clone git://github.com/koppi/simduino.git
```

Build simduino the test sketches:

```
$ cd simduino
$ make
 Building tests/AccelStepper/Bounce
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
 Built Simduino
  ld Bounce
 Building tests/AccelStepper/AFMotor_ConstantSpeed
  cc main.cpp
  ld AFMotor_ConstantSpeed
 Building tests/AccelStepper/AFMotor_MultiStepper
  cc main.cpp
  ld AFMotor_MultiStepper
```

Run a test sketch from the command-line:

```
$ tests/AccelStepper/Bounce/Bounce
pinMode(2, 1)
pinMode(3, 1)
pinMode(4, 1)
pinMode(5, 1)
digitalWrite(2, 0)
digitalWrite(3, 1)
digitalWrite(4, 1)
digitalWrite(5, 0)
digitalWrite(2, 0)
digitalWrite(3, 1)
digitalWrite(4, 0)
digitalWrite(5, 1)
digitalWrite(2, 1)
digitalWrite(3, 0)
digitalWrite(4, 0)
[...]
```

Press CTRL+C to terminate the program. Have fun!

# Authors

* © 2012-2013 [Jakob Flierl](https://github.com/koppi)
