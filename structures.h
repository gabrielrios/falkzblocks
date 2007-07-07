#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct PIECE {
  int xPos, yPos;
  int hit, choice;
  int state, vel;
  int format[4][2];
  SDL_Surface *img;
} PIECE;

#endif // STRUCTURES_H_INCLUDED
