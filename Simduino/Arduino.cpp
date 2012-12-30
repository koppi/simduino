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

__attribute__((weak)) void init(void) {
  debug(" init()");
}
  
__attribute__((weak)) void pinMode(uint8_t p, uint8_t v) {
  debugf(" pinMode(%d, %d)\n", p, v);
}

__attribute__((weak)) void digitalWrite(uint8_t p, uint8_t v) {
  debugf(" digitalWrite(%d, %d)\n", p, v);
}

__attribute__((weak)) int digitalRead(uint8_t p) {
  debugf(" digitalRead(%d)\n", p);
  return 0;
}

int analogRead(uint8_t p) {
  debugf(" analogRead(%d)\n", p);
  return 0;
}

__attribute__((weak)) void analogReference(uint8_t mode) {
  debugf(" analogReference(%d)\n", mode);
}

__attribute__((weak)) void analogWrite(uint8_t p, int v) {
  debugf(" analogWrite(%d, %d)\n", p, v);
}

__attribute__((weak)) unsigned long micros(void) {
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

__attribute__((weak)) unsigned long millis(void) {
  debug(" millis()\n");
  return micros() * 1000;
}

__attribute__((weak)) void delay(unsigned long t) {
  debugf(" delay(%lu)\n", t);
  usleep(t * 1000);
}

__attribute__((weak)) void delayMicroseconds(unsigned int us) {
  debugf(" delayMicroseconds(%d)\n", us);
  usleep(us);
}

__attribute__((weak)) unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout) {
  debugf(" pulseIn(%d, %d, %lu)\n", pin, state, timeout);
  return 0UL;
}

__attribute__((weak)) void shiftOut(uint8_t dataPin, uint8_t clockPin,
			  uint8_t bitOrder, uint8_t val) {
  debugf("shiftOut(%d, %d, %d, %d)\n", dataPin, clockPin, bitOrder, val);
}

__attribute__((weak)) uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
  debugf(" shiftIn(%d, %d, %d)\n", dataPin, clockPin, bitOrder);
  return 0;
}

__attribute__((weak)) void attachInterrupt(uint8_t p, void (*)(void), int mode) {
  debugf(" attachInterrupt(%d, void*, %d)\n", p, mode);
}

__attribute__((weak)) void detachInterrupt(uint8_t p) {
  debugf(" detachInterrupt(%d)\n", p);
}

__attribute__((weak)) void beep(void) {
  debug(" beep()\n");
}

__attribute__((weak)) void shutdown(int signum)
{
  debugf(" shutdown(%d)\n", signum);
  exit(signum);
}

__attribute__((weak)) int setupSim(int, char**)
{
  return 0;
}

__attribute__((weak)) int main(int argc, char **argv) {
  signal(SIGINT, shutdown);
  signal(SIGQUIT, shutdown);

  int i, res;

  if (res = setupSim(argc, argv) != 0) {
	debugf("setupSim(%d", argc);

	for (i = 1; i < argc ; i++) {
	  debugf(",%s", argv[i]);
	  if (i < argc - 2) debug(", ");
	}

	debugf(") returned %d. Exiting.\n", argc, argv, res);

	exit(res);
  }

  debug("setup() begin\n");
  setup();
  debug("setup() end\n");

  debug("loop() enter\n");
  while(true) {
	loop();
  }
}
