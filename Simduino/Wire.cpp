/*
  TwoWire.cpp - TWI/I2C library for Wiring & Arduino
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
*/

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stddef.h>
#include <unistd.h>
}

#include "Wire.h"

// Initialize Class Variables //////////////////////////////////////////////////

uint8_t TwoWire::txAddress = 0;

uint8_t TwoWire::transmitting = 0;

const char *byte_to_binary(int x)
{
  static char b[9];
  b[0] = '\0';

  int z;
  for (z = 128; z > 0; z >>= 1)
    {
	  strcat(b, ((x & z) == z) ? "1" : "0");
    }

  return b;
}

void hexdump(const uint8_t *d, int l) {
  int i;
  // printf("00 01 02 03 04 05 06 07 08\n");
  for(i=0;i<l;i++, d++) {
	printf("0x%02x ",*d);
	printf("%s", byte_to_binary(*d));
  }
  printf("\n");
}

// Constructors ////////////////////////////////////////////////////////////////

TwoWire::TwoWire(int _fd)
{
  fd = _fd;
}

// Public Methods //////////////////////////////////////////////////////////////

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(uint8_t data)
{
  uint8_t buf[1] = { data };
  write(fd, buf, 1);

  hexdump(buf, 1);
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(uint8_t* data, uint8_t quantity)
{
  write(fd, data, quantity);
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(char* data)
{
  send((uint8_t*)data, strlen(data));
}

// must be called in:
// slave tx event callback
// or after beginTransmission(address)
void TwoWire::send(int data)
{
  send((uint8_t)data);
}

// must be called in:
// slave rx event callback
// or after requestFrom(address, numBytes)
uint8_t TwoWire::receive(void)
{
  // default to returning null char
  // for people using with char strings
  uint8_t value = '\0';

  value = write(fd, &value, 1);
  
  return value;
}
