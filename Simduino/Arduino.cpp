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

#include "Arduino.h"

#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>
#include <signal.h>

void init(void) {
  debug(" init()");
}
  
void pinMode(uint8_t p, uint8_t v) {
  debugf(" pinMode(%d, %d)\n", p, v);
}

void digitalWrite(uint8_t p, uint8_t v) {
  debugf(" digitalWrite(%d, %d)\n", p, v);
}

int digitalRead(uint8_t p) {
  debugf(" digitalRead(%d)\n", p);
  return 0;
}

int analogRead(uint8_t p) {
  debugf(" analogRead(%d)\n", p);
  return 0;
}

void analogReference(uint8_t mode) {
  debugf(" analogReference(%d)\n", mode);
}

void analogWrite(uint8_t p, int v) {
  debugf(" analogWrite(%d, %d)\n", p, v);
}

unsigned long micros(void) {
  struct timeval tv;
  struct timezone tz;

  gettimeofday(&tv, &tz);

#ifdef DEBUG
  // struct tm *tm;
  // tm = localtime(&tv.tv_sec);
  // debugf(" %d:%02d:%02d %lu\n", tm->tm_hour,tm->tm_min,tm->tm_sec,tv.tv_usec);
#else
  localtime(&tv.tv_sec);
#endif

  return tv.tv_usec;
}

unsigned long millis(void) {
  debug(" millis()\n");
  return micros() * 1000;
}

void delay(unsigned long t) {
  debugf(" delay(%lu)\n", t);
  usleep(t * 1000);
}

void delayMicroseconds(unsigned int us) {
  debugf(" delayMicroseconds(%d)\n", us);
  usleep(us);
}

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout) {
  debugf(" pulseIn(%d, %d, %lu)\n", pin, state, timeout);
  return 0UL;
}

void shiftOut(uint8_t dataPin, uint8_t clockPin,
			  uint8_t bitOrder, uint8_t val) {
  debugf("shiftOut(%d, %d, %d, %d)\n", dataPin, clockPin, bitOrder, val);
}

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
  debugf(" shiftIn(%d, %d, %d)\n", dataPin, clockPin, bitOrder);
  return 0;
}

void attachInterrupt(uint8_t p, void (*)(void), int mode) {
  debugf(" attachInterrupt(%d, void*, %d)\n", p, mode);
}

void detachInterrupt(uint8_t p) {
  debugf(" detachInterrupt(%d)\n", p);
}

void beep(void) {
  debug(" beep()\n");
}

void shutdown(int signum)
{
  debugf(" shutdown(%d)\n", signum);
  exit(signum);
}

int main(int argc, char **argv) {
  signal(SIGINT, shutdown);
  signal(SIGQUIT, shutdown);

  debug("setup() begin\n");
  setup();
  debug("setup() end\n");

  debug("loop() enter\n");
  while(true) {
	loop();
  }
}
