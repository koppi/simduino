#include <fcntl.h>  // For O_RDWR
#include <unistd.h> // For open(), close()
#include <assert.h> // For assert()

#include <I2CIO.h>  // I2C port expander access

/**
 * sim.cpp - Simulator specific functions.
 *
 * setupSim(argc, argv) - is called during the startup of the simulator.
 * pinMode(pin, mode)   - maps the Arduino pin 13 to I2C port expander pin 0.
 * digitalWrite(p, val) - maps the Arduino pin 13 to I2C port expander pin 0. 
 *
 * usage: 01-Blink.exe [/dev/i2c-?] [I2C address]
 *
 * Example:
 *
 * 01-Blink.exe /dev/i2c-9 0x38
 *
 */

I2CIO *io;

int setupSim(int argc, char** argv)
{
  int fd;

  if (!(argc > 2)) {
	fprintf(stderr,
			"usage: %s [/dev/i2c-?] [I2C address]\n",
			basename(argv[0]));
	return 1;
  }

  fd = open(argv[1], O_RDWR);

  if (!(fd >= 0)) {
	fprintf(stderr, "Error while opening %s. Exiting\n", argv[1]);
	return 2;
  }

  int i2c_addr = strtol(argv[2], NULL, 16);

  io = new I2CIO(fd);

  io->begin(i2c_addr);
  io->portMode(OUTPUT);
  io->write(0xff);

  return 0;
}

void pinMode(uint8_t p, uint8_t mode)
{
  if (p == 13) {
	io->pinMode(0, mode);
  }
}

void digitalWrite(uint8_t p, uint8_t v)
{
  debugf("my digitalWrite(%d, %d)\n", p, v);

  if (p == 13) {
	io->digitalWrite(0, !v);
  }
}
