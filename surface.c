#include "SDL_image.h"

// Carrega imagens e retorna um surface otimizado
SDL_Surface *load_image(char *filename) {
  SDL_Surface *loaded = NULL, *optimized = NULL;

  loaded = IMG_Load(filename);

  if (loaded != NULL) {
    optimized = SDL_DisplayFormat(loaded);
    SDL_FreeSurface(loaded);

    if (optimized != NULL) {
      Uint32 colorkey = SDL_MapRGB(optimized->format, 0xFF, 0, 0xFF);
      SDL_SetColorKey(optimized, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
    }
  }
  return optimized;
}

//Abstracao da funcao BlitSurface
void blit_at_surface(SDL_Surface *source, int x, int y) {
  SDL_Rect pos;

  pos.x = x;
  pos.y = y;

  SDL_BlitSurface(source, NULL, screen, &pos);
}

//Prenche uma surface com as cores R,G,B
void fill_surface(SDL_Surface *self, Uint8 r, Uint8 g, Uint8 b) {
  Uint32 color = SDL_MapRGB(self->format, r, g, b);
  SDL_FillRect(self, NULL, color);
}

//Cria uma nova surface
SDL_Surface* surface(int W, int H) {
  SDL_Surface *self, *opti;
  self = SDL_CreateRGBSurface(SDL_SWSURFACE, W, H, 32, 0, 0, 0, 0);
  if (self == NULL) {
    fprintf(stderr, "Falha ao criar a surface");
  }
  opti = SDL_DisplayFormat(self);
  SDL_FreeSurface(self);

  return opti;
}
