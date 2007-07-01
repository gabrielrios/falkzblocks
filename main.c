#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "time.h"
#include "header.h"

int main(int argc, char **argv) {
  SDL_Surface *screen = NULL;
  SDL_Surface *gridBG = NULL, *nextBG = NULL, *placarBG = NULL;
  SDL_Event event;
  Uint32 start_time;

  int quit = 0;
  srand(time(NULL));

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    fprintf(stderr, "Impossivel Inicializar a SDL");
    return -1;
  }
  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }

  screen = SDL_SetVideoMode(463, 503, 32, SDL_SWSURFACE);
  if (screen == NULL) {
    fprintf(stderr, "Impossivel criar a 'tela'");
    return -1;
  }

  SDL_WM_SetCaption("Falkz Blocks", NULL);
  SDL_WM_SetIcon(IMG_Load(".\\img\\icon.png"), NULL);

  SDL_EnableKeyRepeat(500, 30);

  //Cria a surface q ficara ao fundo do jogo
  gridBG = surface(313, 493);
  fill_surface(gridBG, 0xFF, 0xFF, 0xFF);
  blit_surface(screen, gridBG, 5, 5);
  nextBG = surface(135, 200);
  fill_surface(nextBG, 66, 125, 66);
  blit_surface(screen, nextBG, 323,5);
  placarBG = surface(135, 288);
  fill_surface(placarBG, 00, 66, 82);
  blit_surface(screen, placarBG, 323, 210);

  placar(screen, lvl, pnt);

  PIECE current_block;
  init_piece(&current_block, rand()%7+1);
  PIECE next_block;
  init_piece(&next_block, rand()%7+1);
  draw_piece(&next_block, screen, 1);

  GRID grid;
  init_grid(&grid);
  start_time = SDL_GetTicks();
  while(quit == 0){
    blit_surface(screen, gridBG, 5, 5);
    draw_piece(&current_block, screen, 0);
    draw_grid(&grid, screen);
    linefilled_grid(&grid);
    blit_surface(screen, placarBG, 323, 210);
    placar(screen, lvl, pnt);
    SDL_Flip(screen);
    if (endgame(&grid)) {
      quit = 1;
    }

    while(SDL_PollEvent(&event)) {
      if( event.type == SDL_QUIT ) {
        quit = 1;
      }
      else if (event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE:
            quit=1; break;
          case SDLK_RIGHT:
          case SDLK_LEFT:
            move_piece(&current_block, event.key.keysym.sym, &grid); break;
          case SDLK_SPACE:
            rotate_piece(&current_block); break;
          default:
            break;
        }
      }
    }
    if ((SDL_GetTicks() - start_time)/10 > 30) {
      if (collision(&current_block, &grid, 1) == 1) {
        pnt += 50;
        add_grid(&grid, &current_block);
        current_block = next_block;
        init_piece(&next_block, rand()%7+1);
        blit_surface(screen, nextBG, 323,5);
        draw_piece(&next_block, screen, 1);
      } else {
         fall_piece(&current_block);
      }

      start_time = SDL_GetTicks();
    }
  }

  SDL_FreeSurface(gridBG);

  TTF_Quit();
  SDL_Quit();

  return 0;
}
