# Simduino

Run an unmodified [Arduino sketch](https://docs.arduino.cc/learn/programming/sketches) from the Linux™ command-line.

Features:

* Test out a sketch without the hardware, or prior to purchasing hardware.
* Simulated Hardware:
  * Blink virtual LED on pin 13.
  * Display text on a virtual display using the [16x2 LCD HD44780 controller](https://www.google.com/?q=16x2%20LCD%20HD44780%20controller) or via Linux™ [I2C](https://docs.arduino.cc/learn/communication/wire).
 
Included Libraries:

* Utrasonic Sensors
  * [NewPing](http://code.google.com/p/arduino-new-ping)
  * [Dallas Temperature Control](http://www.milesburton.com/?title=Dallas_Temperature_Control_Library)
  * LCD
  * [LiquidCrystal v2](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)
* Motion control
  * [Adafruit Motor Shield](https://github.com/adafruit/Adafruit-Motor-Shield-library)
  * [AccelStepper](http://www.open.com.au/mikem/arduino/AccelStepper)

Supported Arduinos:

* [Arduino Uno](https://www.google.com/search?q=arduino+uno)

## Documentation

Clone the Simduino repository:

```bash
git clone git://github.com/koppi/simduino.git
```

Install some software (tested with Ubuntu 25.04):

```bash
sudo apt -y install g++ gcc libsdl1.2-dev libsdl-ttf2.0-dev libsdl-image1.2-dev libsdl-gfx1.2-dev
```

Build the Simduino test sketches:

```bash
$ cd simduino
$ make all
 Tutorial/02-Blink
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
 Tutorial/02-Blink
  cc main.cpp
  cc sim.cpp
  ld 01-Blink.exe
[...]
```

Next, run the [Blink.pde](https://github.com/koppi/simduino/blob/master/Tutorial/01-Basics/02-Blink/Blink.pde) sketch from the Linux™ command-line:

```bash
Tutorial/01-Basics/02-Blink/02-Blink.exe 10 # number of loops
```

Press ```CTRL+C``` to terminate the program. Have fun!

# Authors

* © 2012-2025 **Jakob Flierl** - [koppi](https://github.com/koppi)
