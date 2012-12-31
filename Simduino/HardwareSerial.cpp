/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

#include "wiring_private.h"

// this next line disables the entire HardwareSerial.cpp, 
// this is so I can support Attiny series and any other chip without a uart
#if defined(UBRRH) || defined(UBRR0H) || defined(UBRR1H) || defined(UBRR2H) || defined(UBRR3H)

#include "HardwareSerial.h"

// Constructors ////////////////////////////////////////////////////////////////

HardwareSerial::HardwareSerial(int port) {
  _port = port;
  _baud = 0;
}

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(unsigned long baud)
{
  debugf("%lu", baud);
  _baud = baud;
}

void HardwareSerial::begin(unsigned long baud, byte config)
{
  debugf("%lu, %d\n", baud, config);
  _baud = baud;
}

void HardwareSerial::end()
{
  debugf("%d", _port);
}

int HardwareSerial::available(void)
{
  debugf("%d", _port);
  return 0;
}

int HardwareSerial::peek(void)
{
  debugf("%d", _port);
  return -1;
}

int HardwareSerial::read(void)
{
  debugf("%d", _port);
  usleep( 1000 / ((_baud / 1000 / 10)) );
}

void HardwareSerial::flush()
{
  debugf("%d", _port);
}

size_t HardwareSerial::write(uint8_t c)
{
  printf("%c", c);
  fflush(stdout);
  usleep( 10 * 1000 * (10000 / (_baud / 10.0)) );
  return 1;
}

HardwareSerial::operator bool() {
  return true;
}

// Preinstantiate Objects //////////////////////////////////////////////////////

#if defined(UBRRH) && defined(UBRRL)
  HardwareSerial Serial(0);
#elif defined(UBRR0H) && defined(UBRR0L)
  HardwareSerial Serial(0);
#elif defined(USBCON)
  // do nothing - Serial object and buffers are initialized in CDC code
#else
  #error no serial port defined  (port 0)
#endif

#if defined(UBRR1H)
  HardwareSerial Serial1(1);
#endif
#if defined(UBRR2H)
  HardwareSerial Serial2(2);
#endif
#if defined(UBRR3H)
  HardwareSerial Serial3(3);
#endif

#endif // whole file

