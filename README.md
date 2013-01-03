# Simduino - run an Arduino sketch from the command-line

![HelloWorld.gif](https://github.com/koppi/simduino/wiki/HelloWorld.gif)

Features

* Test out a sketch without the hardware, or prior to purchasing hardware.
* Simulated Hardware:
 * a Light bulb.
 * a 16x2 LCD HD44780 controller.
 
Included Libraries:

* Ultrasonic Sensors
 * [NewPing](http://code.google.com/p/arduino-new-ping)
 * [Dallas Temperature Control](http://www.milesburton.com/?title=Dallas_Temperature_Control_Library)

* LCD
 * [LiquidCrystal v2](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)
 
* Motion control
 * [Adafruit Motor Shield](https://github.com/adafruit/Adafruit-Motor-Shield-library)
 * [AccelStepper](http://www.open.com.au/mikem/arduino/AccelStepper)

Supported Arduinos

* Atmega8

## Documentation

Checkout the Simduino repository:

```bash
$ git clone git://github.com/koppi/simduino.git
```

Install the SDL library and gcc (tested with Ubuntu 12.10):

```bash
$ sudo apt-get -y install g++ gcc libsdl1.2-dev libsdl-ttf2.0-dev libsdl-image1.2-dev libsdl-gfx1.2-dev
```

Build the Simduino test sketches:

```bash
$ cd simduino
$ make all
 Building Tutorial/02-Blink
  cc main.cpp
  cc AFMotor.cpp
  cc AccelStepper.cpp
  cc Arduino.cpp
  cc HardwareSerial.cpp
  cc I2CIO.cpp
  cc LCD.cpp
  cc LCD_I2C.cpp
  cc Print.cpp
  cc Stream.cpp
  cc WString.cpp
  cc Wire.cpp
  ld libSimduino.a
 Built libSimduino.a
  ld 00-BareMinimum.exe
 Building Tutorial/02-Blink
  cc main.cpp
  cc sim.cpp
  ld 01-Blink.exe
[...]
```

Run a test sketch from the command-line:

![02-Blink.gif](https://github.com/koppi/simduino/wiki/02-Blink.gif)

Press CTRL+C to terminate the program. Have fun!

# Authors

* © 2012-2013 [Jakob Flierl](https://github.com/koppi)
