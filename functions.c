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

int endgame(PIECE *piece) {
  if (grid[0][4] != 0 || grid[1][4] != 0) {
    return 1;
  } else if (grid[4][4] != 0 && piece->choice == 1) {
    return 1;
  } else if (grid[3][4] !=0 && (piece->choice == 6 || piece->choice == 7)) {
    return 1;
  }
  return 0;

}

void game_over() {
  SDL_Surface *text = NULL;
  SDL_Color color = { 000, 000, 000 };

  text = TTF_RenderText_Solid(font, "Game Over", color);
  blit_at_surface(text, 30, 125);

  SDL_FreeSurface(text);
}

void init_placar() {
  SDL_Surface *text = NULL;
  SDL_Color color = { 135, 000, 135 };
  text = TTF_RenderText_Solid(font_placar, "Level", color);
  blit_at_surface(text, 345, 225);
  SDL_FreeSurface(text);
  text = TTF_RenderText_Solid(font_placar, "Pontos", color);
  blit_at_surface(text, 333, 335);

  SDL_FreeSurface(text);
}
void placar(int lvl, int pnt) {
  SDL_Surface *text = NULL;
  SDL_Color color = { 255, 255, 000 };
  char str[10];
  sprintf(str, "%d", lvl);

  text = TTF_RenderText_Solid(font_placar, str, color);
  blit_at_surface(text, 400, 280);
  SDL_FreeSurface(text);

  sprintf(str, "%06d", pnt);
  text = TTF_RenderText_Solid(font_placar, str, color);
  blit_at_surface(text, 335, 390);

  SDL_FreeSurface(text);
}

void quit_button(int opt) {
  SDL_Surface *button;

  if (opt == 1) {
    button = load_image(".\\data\\imgs\\quit_button.png");
  } else {
    button = load_image(".\\data\\imgs\\quit_button_over.png");
  }
  blit_at_surface(button, 330, 450);
  SDL_FreeSurface(button);
}
