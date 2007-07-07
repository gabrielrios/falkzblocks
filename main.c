#include "SDL.h"
#include "SDL_ttf.h"
#include "globals.h"
#include "functions.c"
#include "block.c"
#include "piece.c"
#include "grid.c"
#include <time.h>


int init() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
    return 0;
  }

  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    return 0;
  }

  screen = SDL_SetVideoMode(460, 525, 0, SDL_ANYFORMAT);
  if (screen == NULL) {
    return 0;
  }
  SDL_WM_SetCaption("Falkz Blockz", NULL);

  SDL_WM_SetIcon(IMG_Load(".\\data\\imgs\\icon.png"), NULL);

  SDL_EnableKeyRepeat(500, 30);

  font = TTF_OpenFont(".\\data\\font\\ABSTRACT.ttf", 10);
  fontp = TTF_OpenFont(".\\data\\font\\ABSTRACT.ttf", 6);

  init_block_images();
  init_grid();

  return 1;
}


int main(int argc, char **argv) {
  SDL_Event event;
  int game = 1, pause = 0;
  srand(time(NULL));

  atexit(SDL_Quit);

  if (init() == 0) {
    return -1;
  }

  init_piece(&peca_atual, rand()%7+1);
  init_piece(&proxima_peca, rand()%7+1);

  background = surface(305, 515);
  fill_surface(background, 0xFF, 0xFF, 0xFF);
  blit_at_surface(background, 5, 5);
  next_background = surface(135, 200);
  fill_surface(next_background, 130, 130, 130);
  blit_at_surface(next_background, 315, 5);

  desenha_peca(proxima_peca, 0);


  start_time = SDL_GetTicks();

  while (game) {
    blit_at_surface(background, 5, 5);
    draw_grid();
    linefilled_grid();
    desenha_peca(peca_atual, 1);
//    placar(lvl, pnt);
    if (pause) {
      paused(pause);
      pause = 0;
    }

    SDL_Flip(screen);
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        game = 0;
      }
      if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE:
            game = 0;
            break;
          case SDLK_RIGHT:
            move_peca(&peca_atual, 1);
            break;
          case SDLK_LEFT:
            move_peca(&peca_atual, 2);
            break;
          case SDLK_UP:
            rotaciona_peca(&peca_atual); break;
          case SDLK_p:
            pause = 1;
            break;
          default:
            break;
        }
      }
    }
    if ((SDL_GetTicks() - start_time)/10 > (30 / (lvl*0.5))) {
      if (collision(&peca_atual, 1) == 1) {
        pnt += 1;
        adiciona_a_grid(peca_atual);
        peca_atual = proxima_peca;
        init_piece(&proxima_peca, rand()%7+1);
        blit_at_surface(next_background, 315, 5);
        desenha_peca(proxima_peca, 0);
      } else {
        desce_peca(&peca_atual);
      }
      start_time = SDL_GetTicks();
    }
  }
  return 1;
}
