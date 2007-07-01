#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED

typedef struct PIECE {
  int xPos, yPos;
  int hit, choice;
  int state;
  SDL_Surface *block;
  //SDL_Rect rect;
  int format[4][2];
} PIECE;

typedef struct GRID {
  int layer[17][10];
  SDL_Surface *block_img[7];
} GRID;

int lvl = 1, pnt = 0;

#endif // CLASS_H_INCLUDED
