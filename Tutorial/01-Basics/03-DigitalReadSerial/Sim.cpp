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
 */

#ifdef HAVE_SDL

#include <sim_sdl.hpp>
#include <timer.h>

#define PIX_SIZE 256

#ifdef HAVE_SDL_IMAGE

#include <SDL/SDL_image.h>

#include "bulb-on.xpm"
#include "bulb-off.xpm"
SDL_Surface * sdl_bulb_on, * sdl_bulb_off;
#endif

void sdl_draw(SDL_Surface * sf, uint8_t port, uint8_t pin, uint8_t value)
{
  SDL_Color fg_black = { 0, 0, 0 };
  SDL_Color fg_white = { 255, 255, 255 };
  SDL_Rect rect;
  SDL_Surface *txt_sf;
  
  char buf[32];
  
  SDL_FillRect(sf, NULL, 0xFFFFFF);

#ifndef HAVE_SDL_IMAGE  
  sprintf(buf, "%d", value);
  txt_sf = TTF_RenderText_Blended(font, buf, fg_white);

  rect.w = txt_sf->w;
  rect.h = txt_sf->h;
  rect.x =  PIX_SIZE /  5.75 + PIX_SIZE * pin;
  rect.y = -PIX_SIZE / 12.00 + PIX_SIZE * port;

  SDL_BlitSurface(txt_sf, NULL, sf, &rect);
  SDL_FreeSurface(txt_sf);

#else

  rect.x = rect.y = 0;
  rect.w = sf->w;
  rect.h = sf->h;

  if (value == 0) {
	SDL_BlitSurface(sdl_bulb_off, NULL, sf, &rect);
  } else {
	SDL_BlitSurface(sdl_bulb_on,  NULL, sf, &rect);
  }

#endif
  
  SDL_Flip(sf);
}

int sdl_mouse_x, sdl_mouse_y;

uint8_t pin;

#endif

I2CIO *io;

int setupSim(int argc, char** argv)
{
  int fd;

  if (!(argc > 0)) {
	fprintf(stderr, YELLOW "usage: " GREEN "%s" YELLOW " [loops] [I2C device] [I2C address]" RESET "\n\n", basename(argv[0]));
	fprintf(stderr, YELLOW "  [loops] " RESET "      - number of loops to run the sim for.\n");
	fprintf(stderr, YELLOW "  [I2C device] " RESET " - the I2C device, e.g. '/dev/i2c-1'\n");
	fprintf(stderr, YELLOW "  [IC2 address] " RESET "- the I2C address in hex, e.g. '0x30'\n");
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
  } else {
	sim_loops = 0;
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

#ifdef HAVE_SDL
  sdl_screen = sdl_init(basename(argv[0]), PIX_SIZE, PIX_SIZE, PIX_SIZE);

#ifdef HAVE_SDL_IMAGE
  // sdl_bulb_on  = sdl_img_load("bulb-on.png");
  // sdl_bulb_off = sdl_img_load("bulb-off.png");
  
  sdl_bulb_on  = IMG_ReadXPMFromArray(bulb_on_xpm);
  sdl_bulb_off = IMG_ReadXPMFromArray(bulb_off_xpm);
#endif

  if (start_timer(100, &loopSim)) {
    printf("\n timer error\n");
    return 6;
  }
#endif

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

#ifdef HAVE_SDL
	sdl_draw(sdl_screen, 0, 0, v);
#endif
  }
}

int digitalRead(uint8_t p)
{
  debugf("%d", p);

  if (p == 2) {
	return pin;
  } else {
	return LOW;
  }
}

#ifdef HAVE_SDL

unsigned long _loop = 0;

void loopSim()
{
  // debug("");

  SDL_Event evt;

  SDL_GetMouseState(&sdl_mouse_x, &sdl_mouse_y);

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
	} else if(evt.type == SDL_MOUSEBUTTONDOWN){
	  if (evt.button.button == SDL_BUTTON_LEFT){
		if (pin == HIGH) {
		  pin = LOW;
		} else {
		  pin = HIGH;
		}
	  }
	}
  }
  
  if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) {
  }

  if (sdl_quit == 1 || (sim_loops > 0 && _loop >= sim_loops)) {
    shutdownSim(0);
  }
  
  if (sim_loops > 0) {
    debugf("%lu", _loop);
  }

  _loop++;
}
#endif

void shutdownSim(int signum) {

#ifdef HAVE_SDL
  stop_timer();
  SDL_Quit();
#endif

  if (signum != 0) {
    debugf(YELLOW "%d, %s" GREEN, signum, strsignal(signum));
  } else {
    debugf(YELLOW "%d" GREEN, signum);
  }

  exit(signum);
}
