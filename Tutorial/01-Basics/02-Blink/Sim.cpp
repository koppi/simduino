#include <fcntl.h>  // For O_RDWR
#include <unistd.h> // For open(), close()
#include <assert.h> // For assert()
#include <errno.h>  // For errno

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

#define dbgf(fmt, ...) fprintf(stderr, YELLOW "%s(" fmt ")" RESET "\n", __FUNCTION__, __VA_ARGS__)
#define dbg(fmt) fprintf(stderr, YELLOW fmt "%s()" RESET "\n", __FUNCTION__)

I2CIO *io;

int setupSim(int argc, char** argv)
{
  int fd;

  if (!(argc > 1)) {
	fprintf(stderr, "usage: %s [loops] [I2C device] [I2C address]\n\n", basename(argv[0]));
	fprintf(stderr, "  [loops]       - number of loops to run the sim for.\n");
	fprintf(stderr, "  [I2C device]  - the I2C device, e.g. '/dev/i2c-1'\n");
	fprintf(stderr, "  [IC2 address] - the I2C address in hex, e.g. '0x30'\n");
	fprintf(stderr, "\n");
	return 1;
  }

  if (argc > 1) {
	char * tmp;
	sim_loops = strtol(argv[1], &tmp, 10);
	
	if (errno != 0 || argv[1] == tmp || !(*tmp == '\0')) {
	  fprintf(stderr, "Error parsing [loops] - '%s' is not a numerical value.\n", argv[1]);
	  return 2;
	}
  }

  if (argc > 2) {
	fd = open(argv[2], O_RDWR);

	if (!(fd >= 0)) {
	  fprintf(stderr, "Error opening [I2C device] - '%s'.\n", argv[2]);
	  return 3;
	}
  }

  int i2c_addr = -1;

  if (argc > 3) {
	char * tmp;
	i2c_addr = strtol(argv[3], &tmp, 16);

	if (errno != 0 || argv[3] == tmp || !(*tmp == '\0')) {
	  fprintf(stderr, "Error parsing [I2C address] - '%s' is not a hex value.\n", argv[3]);
	  return 5;
	}
  }

  io = new I2CIO(fd);

  if (i2c_addr != -1) {
	io->begin(i2c_addr);
  }

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
  debugf("%d, %d", p, v);

  if (p == 13) {
	io->digitalWrite(0, v);
  }
}
