#include <stddef.h>

#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

#include <LCD_SIM.h>

#ifdef HAVE_SDL
#include <sim_sdl.hpp>
#include <timer.h>
#endif

extern LCD* sim_lcd;

int fd;

LCD_SIM *sim;

int setupSim(int argc, char **argv) {
  debug("");

  if (argc == 3)  {
	fd = open(argv[1], O_RDWR);
	
	if (fd < 0) {
	  printf("error: unable to open I2C device. Exiting.\n");
	  exit(1);
	}

	int i2c_addr = strtol(argv[2], NULL, 16);

	sim_lcd = new LiquidCrystal_I2C(fd, i2c_addr);

  } else {
	sim_lcd = new LiquidCrystal(8, 9, 10, 0, 1, 2, 3, 4, 5, 6, 7);
  }

  sim = new LCD_SIM();

#ifdef HAVE_SDL

  sdl_screen = sdl_init(basename(argv[0]), 320, 240, 11);

  sim->sdl_init();

  if (start_timer(367, &loopSim)) {
    printf("\n timer error\n");
    return 6;
  }

#endif

  return 0;
}

var enState = LOW;
var rwState = LOW;
var rsState = LOW;

uint8_t port  = 0x0;

void digitalWrite(uint8_t p, uint8_t v) {

  // debugf("%d, %d", p, v);

  static var eGoLow = 0;

  if (sim) {

	if (p == 10) { // EN

	  if (v == HIGH && enState == LOW) {
		eGoLow = 0;
	  } else if (v == LOW && enState == HIGH) {
		eGoLow = 1;
	  }
	  enState = v;
	} else if (p == 9) { // RW
	  rwState = v;
	} else if (p == 8) { // RS
	  rsState = v;
	} else if (p >= 0 && p <= 7) {
	  if (v == HIGH) {
		port |=   1 << (p);
	  } else if (v == LOW) {
		port &= ~(1 << (p));
	  }
	}

	if (eGoLow) {
	  sim->lcd(port, eGoLow, rwState, rsState);
	  eGoLow = 0;
	}
  }
}

#ifdef HAVE_SDL

unsigned long _loop = 0;

void loopSim()
{
  // debug("");

  SDL_Event evt;

  if (sim) {
	sim->blink_callback();
	sim->sdl_draw(sdl_screen, 15, 15);
  }

  while (SDL_PollEvent(&evt)) {
    if (evt.type == SDL_KEYDOWN) {
      switch (evt.key.keysym.sym) {
      case SDLK_q:
      case SDLK_ESCAPE:
        sdl_quit = 1;
        break;
      default:
        break;
      }
    } else if (evt.type == SDL_QUIT) {
      sdl_quit = 1;
    }
  }

  if (sdl_quit == 1 || (sim_loops > 0 && _loop >= sim_loops)) {
    shutdownSim(0);
  }

  if (sim_loops > 0) {
    debugf("%lu", _loop);
  }

  _loop++;

  SDL_Flip(sdl_screen);
}
#endif

void shutdownSim(int signum) {
  debugf("%d", signum);

#ifdef HAVE_SDL
  stop_timer();
  SDL_Quit();
#endif

  if (fd > 0) close(fd);
  if (sim) delete sim;

  if (signum != 0) {
    debugf(YELLOW "%d, %s" GREEN, signum, strsignal(signum));
  } else {
    debugf(YELLOW "%d" GREEN, signum);
  }

  exit(signum);
}
