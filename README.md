# Simduino - run an Arduino sketch from the command-line

Features

* Test out a sketch without the hardware, or prior to purchasing hardware.

Supported Arduinos

* Atmega8

## Documentation

Build and run one of the sketches in tests/ sub-directory:

```
$ git clone git://github.com/koppi/simduino.git
$ cd simduino
$ ls
Simduino/ tests/ Makefile README.md
$ cd tests
$ ls
AccelStepper
$ cd AccelStepper/Bounce
$ make
$ ./Bounce
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
digitalWrite(5, 1)
digitalWrite(2, 1)
digitalWrite(3, 0)
digitalWrite(4, 1)
digitalWrite(5, 0)
digitalWrite(2, 0)
digitalWrite(3, 1)
digitalWrite(4, 1)
digitalWrite(5, 0)
digitalWrite(2, 0)
digitalWrite(3, 1)
digitalWrite(4, 0)
[...]
``` 

Have fun!

# Authors

* © 2012-2013 [Jakob Flierl](https://github.com/koppi)
