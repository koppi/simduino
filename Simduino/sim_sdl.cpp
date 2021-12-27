#include <assert.h>

#ifdef HAVE_SDL

#include <SDL.h>

#ifdef HAVE_SDL_GFX
#include <SDL_gfxPrimitives.h>
#endif

#ifdef HAVE_SDL_IMAGE
#include <SDL_image.h>
#endif

#ifdef HAVE_SDL_TTF
#include <SDL_ttf.h>
#endif

TTF_Font *sdl_font = NULL;

int sdl_quit = 0;
SDL_Surface *sdl_screen;

SDL_Surface *sdl_init(const char *title, int width, int height, int sdl_font_size)
{
  Uint8 video_bpp;
  Uint32 videoflags;
  SDL_Surface *screen;

  int w = width, h = height;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "can't initialize SDL video\n");
    exit(1);
  }

  TTF_Init();

  sdl_font =
    TTF_OpenFont
    ("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", sdl_font_size);

  assert(sdl_font);

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
  SDL_Surface* loadedimage = NULL;
  SDL_Surface* usedimage = NULL;

  loadedimage = IMG_Load(filename);

  if (loadedimage != NULL) {
    usedimage = SDL_DisplayFormat(loadedimage);
    SDL_FreeSurface(loadedimage);
  }

  return usedimage;
}

SDL_Surface *sdl_img_load(const char * buff, const int size) 
{
  SDL_RWops *rw = SDL_RWFromMem((void*)buff,size);
  SDL_Surface *temp = IMG_Load_RW(rw, 1);
  
  if (temp == NULL) 
    {
	  printf("IMG_Load_RW: %s\n", IMG_GetError());
	  exit(1);
    }
  
  SDL_Surface *myimage;
  myimage = SDL_DisplayFormat(temp);
  
  //Free the temporary surface
  SDL_FreeSurface(temp);
  
  //Return our loaded image
  return myimage;
} 

#endif

void sdl_text(SDL_Surface *sf, const char* txt, int x, int y)
{
  SDL_Color fg_black = { 0, 0, 0 };
  SDL_Color fg_white = { 255, 255, 255 };
  SDL_Rect rect;
  SDL_Surface *txt_sf;

  char buf[1024];

  sprintf(buf, "%s", txt);

  txt_sf = TTF_RenderText_Blended(sdl_font, buf, fg_white);
  
  rect.w = txt_sf->w;
  rect.h = txt_sf->h;
  rect.x = x;
  rect.y = y;
  
  SDL_BlitSurface(txt_sf, NULL, sf, &rect);
  SDL_FreeSurface(txt_sf);
}

#endif
