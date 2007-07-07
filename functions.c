#include "SDL_image.h"


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

void blit_at_surface(SDL_Surface *source, int x, int y) {
  SDL_Rect pos;

  pos.x = x;
  pos.y = y;

  SDL_BlitSurface(source, NULL, screen, &pos);
}

void fill_surface(SDL_Surface *self, Uint8 r, Uint8 g, Uint8 b) {
  Uint32 color = SDL_MapRGB(self->format, r, g, b);
  SDL_FillRect(self, NULL, color);
}

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

int collision(PIECE *piece, int direction) {
  int i, x, y;

  if (direction == 1) { //down
    for (i=0; i<4; i++) {
      x = piece->format[i][0] + piece->xPos;
      y = piece->format[i][1] + piece->yPos;
      if (grid[y+1][x] > 0) {
        return 1;
      }
    }
  }

  if (direction == 2) { //right
    for (i=0; i<4; i++) {
      x = piece->format[i][0] + piece->xPos;
      y = piece->format[i][1] + piece->yPos;
      if (grid[y][x+1] > 0)
        return 1;
    }
  }
  if (direction == 3) { //left
    for (i=0; i<4; i++) {
      x = piece->format[i][0] + piece->xPos;
      y = piece->format[i][1] + piece->yPos;
      if (grid[y][x-1] > 0)
        return 1;
    }
  }
  return 0;
}

int paused(int pause) {
  SDL_Event event;

  SDL_Surface *text = NULL;
  SDL_Color color = { 000, 000, 000 };

  text = TTF_RenderText_Solid(font, "PAUSED", color);
  blit_at_surface(text, 70, 125);
  SDL_Flip(screen);

  while (pause) {
    while(SDL_PollEvent(&event)) {
      if( event.type == SDL_QUIT ) {
        exit(0);
      }
      else if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
          case SDLK_p:
            pause = 0; break;
          case SDLK_ESCAPE:
            exit(0);
          default:
            break;
        }
      }
    }
  }
  free(&color);
  SDL_FreeSurface(text);

  return pause;
}



