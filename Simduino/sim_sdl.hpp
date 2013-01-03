#ifndef SIM_SDL_H
#define SIM_SDL_H

#if defined(HAVE_SDL)

#include <SDL.h>

#if defined(HAVE_SDL_IMAGE) && defined(HAVE_SDL)
SDL_Surface *sdl_img_load(const char *filename);
SDL_Surface *sdl_img_load(const char * buff, const int size);
#endif
#if defined(HAVE_SDL)
SDL_Surface *sdl_init(const char *title,int width,int height,int sdl_font_size);
void sdl_text(SDL_Surface *sf, const char* txt, int x, int y);
extern SDL_Surface *sdl_screen;
extern int sdl_quit;

#ifdef HAVE_SDL_TTF

#include <SDL_ttf.h>

#endif

#endif

#endif

#endif
