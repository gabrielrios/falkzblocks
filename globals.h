#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include "structures.h"

//Screen and Background Surfaces
SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Surface *next_background = NULL;
SDL_Surface *placar_background = NULL;

//Blocks Image Global Surface
SDL_Surface *anil_block = NULL;
SDL_Surface *azul_block = NULL;
SDL_Surface *green_block = NULL;
SDL_Surface *orange_block = NULL;
SDL_Surface *purple_block = NULL;
SDL_Surface *red_block = NULL;
SDL_Surface *yellow_block = NULL;

//Pieces Variables;
PIECE peca_atual;
PIECE proxima_peca;

//Grid
int grid[18][10];

//Level and Pontuation Thing
int lvl = 1;
int pnt = 0;
Uint32 start_time;

//Fonts
TTF_Font *font;
TTF_Font *font_placar;

#endif // GLOBALS_H_INCLUDED
