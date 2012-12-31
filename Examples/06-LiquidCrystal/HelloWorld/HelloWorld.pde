#include <stddef.h>

#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "LiquidCrystal_I2C.h"

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t cclock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {0x1,0x1,0x5,0x9,0x1f,0x8,0x4};

int fd;
LiquidCrystal_I2C* lcd;

int setupSim(int argc, char **argv) {

  if (argc > 2)  {
	fd = open(argv[1], O_RDWR);
	
	if (fd < 0) {
	  printf("error: unable to open I2C device. Exiting.\n");
	  exit(1);
	}

	int i2c_addr = strtol(argv[2], NULL, 16);

	lcd = new LiquidCrystal_I2C(fd, i2c_addr, 6, 5, 4, 3, 2, 1, 0);
  } else {
	printf("usage: %s [/dev/i2c-?] [I2C address]\n", basename(argv[0]));
	return 1;
  }

  return 0;
}

void setup() {
  lcd->begin (16,2);  // initialize the lcd 
  
  lcd->createChar(0, bell);
  lcd->createChar(1, note);
  lcd->createChar(2, cclock);
  lcd->createChar(3, heart);
  lcd->createChar(4, duck);
  lcd->createChar(5, check);
  lcd->createChar(6, cross);
  lcd->createChar(7, retarrow);
}

void loop() {
  printf("clear\n");
  lcd->clear();
  usleep(2000);
  
  printf("home\n");
  lcd->home();
  usleep(2000);
  
  printf("setCursor\n");
  lcd->setCursor(0, 0);
  usleep(2000);
  
  printf("Hello World\n");
  lcd->print("   Hello world    ");
  usleep(2000);
}

void shutdownSim(int signum) {
  debugf("%d", signum);

  if (lcd) delete lcd;
  if (fd > 0) close(fd);

  exit(signum);
}
