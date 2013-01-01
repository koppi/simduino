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
#include <SDL/SDL.h>
#include <timer.h>

#ifdef HAVE_SDL_GFX
#include <SDL_gfxPrimitives.h>
#endif

#ifdef HAVE_SDL_IMAGE
#include <SDL_image.h>
#endif

#ifdef HAVE_SDL_TTF
#include <SDL_ttf.h>
#endif

static TTF_Font *font = NULL;

#define PIX_SIZE 128

SDL_Surface *sdl_init(const char *title)
{
  Uint8 video_bpp;
  Uint32 videoflags;
  SDL_Surface *screen;
  int w = PIX_SIZE, h = PIX_SIZE;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	fprintf(stderr, "can't initialize SDL video\n");
	exit(1);
  }

  // atexit(SDL_Quit);
  
  TTF_Init();
  font =
	TTF_OpenFont
	("/usr/share/fonts/truetype/ttf-dejavu/DejaVuSansMono.ttf", PIX_SIZE);

  assert(font);
  
  video_bpp = 32;
  videoflags = SDL_HWSURFACE | SDL_DOUBLEBUF /*| SDL_FULLSCREEN */ ;
  
  if ((screen = SDL_SetVideoMode(w, h, video_bpp, videoflags)) == NULL) {
	fprintf(stderr, "Error: Can't set video mode %dx%d\n", w, h);
	exit(2);
  }
  
  SDL_WM_SetCaption(title, title);
  
  return screen;
}

#ifdef HAVE_SDL_IMAGE

SDL_Surface *sdl_img_load(const char* filename)
{
  // Image loaded
  SDL_Surface* loadedimage = NULL;

  // Image to be used
  SDL_Surface* usedimage = NULL;

  //Loads Image
  loadedimage = IMG_Load(filename);

  //Creates image to be used
  if(loadedimage != NULL)
	{
	  //Puts the file in a SDL acceptable format
	  usedimage = SDL_DisplayFormat(loadedimage);
	  //Frees the old surface
	  SDL_FreeSurface(loadedimage);
	}

  //Returns the final image
  return usedimage;
}

SDL_Surface * sdl_led_on, * sdl_led_off;

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
	SDL_BlitSurface(sdl_led_off, NULL, sf, &rect);
  } else {
	SDL_BlitSurface(sdl_led_on,  NULL, sf, &rect);
  }
#endif
  
  SDL_Flip(sf);
}

#endif


#define dbgf(fmt, ...) fprintf(stderr, YELLOW "%s(" fmt ")" RESET "\n", __FUNCTION__, __VA_ARGS__)
#define dbg(fmt) fprintf(stderr, YELLOW fmt "%s()" RESET "\n", __FUNCTION__)

I2CIO *io;

#ifdef HAVE_SDL
int quit = 0;
SDL_Surface *screen;
int sdl_mouse_x, sdl_mouse_y;
#endif

int setupSim(int argc, char** argv)
{
  int fd;

  if (!(argc > 1)) {
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
  screen = sdl_init(basename(argv[0]));

#ifdef HAVE_SDL_IMAGE
  sdl_led_on = sdl_img_load("red-led-on.png");
  sdl_led_off = sdl_img_load("red-led-off.png");
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
	sdl_draw(screen, 0, 0, v);
#endif
  }
}

#ifdef HAVE_SDL
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
		quit = 1;
		break;
	  default:
		break;
	  }
	} else if (evt.type == SDL_QUIT) {
	  quit = 1;
	}
  }
  
  if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
	printf("Mouse Button 1 (left) is pressed.\n");

  if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3))
	printf("Mouse Button 3 (right) is pressed.\n");

  if (quit == 1) {
	shutdownSim(0);
  }
}
#endif

void shutdownSim(int signum) {
  stop_timer();

  if (signum != 0) {
    debugf(YELLOW "%d, %s" GREEN, signum, strsignal(signum));
  } else {
    debugf(YELLOW "%d" GREEN, signum);
  }

  SDL_Quit();

  exit(signum);
}
