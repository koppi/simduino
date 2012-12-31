/*
  wiring.h - Partial implementation of the Wiring API for the ATmega8.
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id$
*/

#ifndef Wiring_h
#define Wiring_h

#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C"{
#endif

#include "config.h"

#include <avr/sfr_defs.h>

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

#ifdef DEBUG

#include <stdio.h>
#include <stdarg.h>

# define debug(fmtstr) fprintf(stderr, fmtstr)
# define debugf(fmtstr, ...) fprintf(stderr, fmtstr, __VA_ARGS__)

#else

# define debug(fmtstr)
# define debugf(fmtstr, ...)

#endif

#define HIGH 0x1
#define LOW  0x0
  
#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
  
#define true 0x1
#define false 0x0

#define B(x) ( \
  (0##x >>  0 & 0x01) | \
  (0##x >>  2 & 0x02) |	\
  (0##x >>  4 & 0x04) | \
  (0##x >>  6 & 0x08) | \
  (0##x >>  8 & 0x10) |	\
  (0##x >> 10 & 0x20) | \
  (0##x >> 12 & 0x40) |	\
  (0##x >> 14 & 0x80) )
  
#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
  
#define SERIAL  0x0
#define DISPLAY 0x1
  
#define LSBFIRST 0
#define MSBFIRST 1
  
#define CHANGE 1
#define FALLING 2
#define RISING 3
  
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define INTERNAL1V1 2
#define INTERNAL2V56 3
#else
#define INTERNAL 3
#endif
#define DEFAULT 1
#define EXTERNAL 0
  
  // undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif
  
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))
  
#define interrupts() debug("sei()\n")
#define noInterrupts() debug("cli()\n")
  
#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )
  
#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
  
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))
  
  typedef unsigned int word;
  
#define bit(b) (1UL << (b))
  
  typedef uint8_t boolean;
  typedef uint8_t byte;
  
  void init(void);
  
  void pinMode(uint8_t p, uint8_t v);
  
  void digitalWrite(uint8_t p, uint8_t v);
  
  int digitalRead(uint8_t v);
  
  int analogRead(uint8_t);
  void analogReference(uint8_t mode);
  void analogWrite(uint8_t, int);
  
  unsigned long micros(void);
  unsigned long millis(void);

  void delay(unsigned long t);

  void delayMicroseconds(unsigned int us);

  unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
  
  void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
  uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
  
  void attachInterrupt(uint8_t, void (*)(void), int mode);
  void detachInterrupt(uint8_t);
  
  void setup(void);
  void loop(void);

  // On the ATmega1280, the addresses of some of the port registers are
  // greater than 255, so we can't store them in uint8_t's.
  extern const uint16_t PROGMEM port_to_mode_PGM[];
  extern const uint16_t PROGMEM port_to_input_PGM[];
  extern const uint16_t PROGMEM port_to_output_PGM[];

  extern const uint8_t PROGMEM digital_pin_to_port_PGM[];
  // extern const uint8_t PROGMEM digital_pin_to_bit_PGM[];
  extern const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[];
  extern const uint8_t PROGMEM digital_pin_to_timer_PGM[];

  // Get the bit location within the hardware port of the given virtual pin.
  // This comes from the pins_*.c file for the active board configuration.
  //
  // These perform slightly better as macros compared to inline functions
  //
#define digitalPinToPort(P) ( pgm_read_byte( digital_pin_to_port_PGM + (P) ) )
#define digitalPinToBitMask(P) ( pgm_read_byte( digital_pin_to_bit_mask_PGM + (P) ) )
#define digitalPinToTimer(P) ( pgm_read_byte( digital_pin_to_timer_PGM + (P) ) )
#define analogInPinToBit(P) (P)
#define portOutputRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_output_PGM + (P))) )
#define portInputRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_input_PGM + (P))) )
#define portModeRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_mode_PGM + (P))) )

#define NOT_A_PIN 0
#define NOT_A_PORT 0

  // Simulator prototypes
  void shutdownSim(int signum);
  int setupSim(int argc, char** argv);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#include "WCharacter.h"
#include "WString.h"
#include "HardwareSerial.h"

uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration = 0);
void noTone(uint8_t _pin);

// WMath prototypes                                                            
long random(long);
long random(long, long);
void randomSeed(unsigned int);
long map(long, long, long, long, long);

#endif

#include "pins_arduino.h"

#endif
