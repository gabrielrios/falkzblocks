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

int collision(PIECE *piece, GRID *grid, int direction) {
  int i, x, y;

  if (direction == 1) { //down
    for (i=0; i<4; i++) {
      x = piece->format[i][0] + piece->xPos;
      y = piece->format[i][1] + piece->yPos;
      if (grid->layer[y+1][x] > 0) {
        return 1;
      }
    }
  }

  if (direction == 2) { //right
    for (i=0; i<4; i++) {
      x = piece->format[i][0] + piece->xPos;
      y = piece->format[i][1] + piece->yPos;
      if (grid->layer[y][x+1] > 0)
        return 1;
    }
  }
  if (direction == 3) { //left
    for (i=0; i<4; i++) {
      x = piece->format[i][0] + piece->xPos;
      y = piece->format[i][1] + piece->yPos;
      if (grid->layer[y][x-1] > 0)
        return 1;
    }
  }

  return 0;
}

int endgame(GRID *grid) {
  int x;
  for (x=0; x<10; x++) {
    if (grid->layer[0][x] != 0) {
      return 1;
    }
  }
  return 0;

}

void placar(SDL_Surface *screen, int lvl, int pnt) {
  SDL_Surface *text = NULL;
  TTF_Font *font;
  SDL_Color color = { 135, 000, 135 };
  char str[10];
  sprintf(str, "%d", lvl);

  font = TTF_OpenFont(".\\data\\lazy.ttf", 30);
  text = TTF_RenderText_Solid(font, "Level", color);
  blit_surface(screen, text, 355, 225);
  text = TTF_RenderText_Solid(font, "Pontos", color);
  blit_surface(screen, text, 343, 335);
  color.r = 255; color.g = 255; color.b = 000;
  text = TTF_RenderText_Solid(font, str, color);
  blit_surface(screen, text, 410, 280);
  sprintf(str, "%08d", pnt);
  text = TTF_RenderText_Solid(font, str, color);
  blit_surface(screen, text, 330, 390);
}
