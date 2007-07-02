#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include "class.h"

SDL_Surface *screen = NULL;
SDL_Surface *gridBG = NULL, *nextBG = NULL, *placarBG = NULL;

GRID grid;

PIECE current_block;
PIECE next_block;


#include "surface.c"
#include "functions.c"
#include "Piece.c"
#include "Grid.c"

#endif // HEADER_H_INCLUDED
