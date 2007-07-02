#include "SDL_image.h"

void clean() {
  SDL_FreeSurface(gridBG);
  SDL_FreeSurface(nextBG);
  SDL_FreeSurface(placarBG);
  SDL_FreeSurface(screen);
  free(&grid);
  free(&current_block);
  free(&next_block);


  TTF_Quit();
  SDL_Quit();
}


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

int endgame(GRID *grid, PIECE *piece) {
  if (grid->layer[0][4] != 0 || grid->layer[1][4] != 0) {
    return 1;
  } else if (grid->layer[4][4] != 0 && piece->choice == 1) {
    return 1;
  } else if (grid->layer[3][4] !=0 && (piece->choice == 6 || piece->choice == 7)) {
    return 1;
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

  SDL_FreeSurface(text);
}

void game_over(SDL_Surface *screen) {
  SDL_Surface *text = NULL;
  TTF_Font *font;
  SDL_Color color = { 000, 000, 000 };

  font = TTF_OpenFont(".\\data\\lazy.ttf", 50);
  text = TTF_RenderText_Solid(font, "Game Over", color);
  blit_surface(screen, text, 50, 125);

  SDL_FreeSurface(text);
}

int paused(int pause) {
  SDL_Event event;

  while (pause) {
    while(SDL_PollEvent(&event)) {
      if( event.type == SDL_QUIT ) {
        clean();
        exit(0);
      }
      else if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
          case SDLK_p:
            pause = 0; break;
          case SDLK_ESCAPE:
            clean();
            exit(0);
          default:
            break;
        }
      }
    }
  }
  return pause;
}
