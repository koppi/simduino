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

#ifdef debugs
# undef debugs
# define debugs(fmtstr) fprintf(stderr, YELLOW fmtstr RESET)
#endif

#ifdef debugsf
# undef debugsf
# define debugsf(fmtstr, ...) fprintf(stderr, YELLOW fmtstr RESET, __VA_ARGS__)
#endif

__attribute__((weak)) void init(void) {
  debug("init");
}
  
__attribute__((weak)) void pinMode(uint8_t p, uint8_t v) {
  debugf("%d, %d", p, v);
}

__attribute__((weak)) void digitalWrite(uint8_t p, uint8_t v) {
  debugf("%d, %d", p, v);
}

__attribute__((weak)) int digitalRead(uint8_t p) {
  debugf("%d", p);
  return 0;
}

int analogRead(uint8_t p) {
  debugf("%d", p);
  return 0;
}

__attribute__((weak)) void analogReference(uint8_t mode) {
  debugf("%d", mode);
}

__attribute__((weak)) void analogWrite(uint8_t p, int v) {
  debugf("%d, %d", p, v);
}

__attribute__((weak)) unsigned long micros(void) {
  struct timeval tv;
  struct timezone tz;

  gettimeofday(&tv, &tz);

#ifdef DEBUG
  // struct tm *tm;
  // tm = localtime(&tv.tv_sec);
  // debugf("%d:%02d:%02d %lu", tm->tm_hour,tm->tm_min,tm->tm_sec,tv.tv_usec);
#else
  localtime(&tv.tv_sec);
#endif

  return tv.tv_usec;
}

__attribute__((weak)) unsigned long millis(void) {
  // debug("");
  return micros() * 1000;
}

__attribute__((weak)) void delay(unsigned long t) {
  debugf("%lu", t);
  usleep(t * 1000);
}

__attribute__((weak)) void delayMicroseconds(unsigned int us) {
  debugf("%d", us);
  usleep(us);
}

__attribute__((weak)) unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout) {
  debugf("%d, %d, %lu", pin, state, timeout);
  return 0UL;
}

__attribute__((weak)) void shiftOut(uint8_t dataPin, uint8_t clockPin,
			  uint8_t bitOrder, uint8_t val) {
  debugf("%d, %d, %d, %d", dataPin, clockPin, bitOrder, val);
}

__attribute__((weak)) uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
  debugf("%d, %d, %d", dataPin, clockPin, bitOrder);
  return 0;
}

__attribute__((weak)) void attachInterrupt(uint8_t p, void (*)(void), int mode) {
  debugf("%d, void*, %d", p, mode);
}

__attribute__((weak)) void detachInterrupt(uint8_t p) {
  debugf("%d", p);
}

__attribute__((weak)) void beep(void) {
  debug("");
}

__attribute__((weak)) void shutdownSim(int signum)
{
  debugsf("\nshutdownSim(%d)\n", signum);
  exit(signum);
}

__attribute__((weak)) int setupSim(int, char**)
{
  return 0;
}

__attribute__((weak)) int main(int argc, char **argv) {
  signal(SIGINT, shutdownSim);
  signal(SIGQUIT, shutdownSim);

  int i, res;

  if (res = setupSim(argc, argv) != 0) {
	debugsf("setupSim(%d", argc);

	for (i = 1; i < argc ; i++) {
	  debugsf(",%s", argv[i]);
	  if (i < argc - 2) debug(", ");
	}

	debugsf(") returned %d. Exiting.\n", argc, argv, res);

	exit(res);
  }

  debugs("setup() begin\n");
  setup();
  debugs("setup() end\n");

  debugs("loop()  enter\n");
  while(true) {
	loop();
  }
}

void randomSeed(unsigned int seed)
{
  if (seed != 0) {
    srandom(seed);
  }
}

long random(long howbig)
{
  if (howbig == 0) {
    return 0;
  }
  return random() % howbig;
}

long random(long howsmall, long howbig)
{
  if (howsmall >= howbig) {
    return howsmall;
  }
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t makeWord(unsigned int w) { return w; }
uint16_t makeWord(unsigned char h, unsigned char l) { return (h << 8) | l; }
