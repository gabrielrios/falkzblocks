#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

// Estrutura da pe�as
// xPos yPos = posi��o relativa da tela
// choice = Qual pe�a
// State = qual a rota��o da pe�a
// vel = Velocidade de descida
// Format = a pe�a
// img = referencia para a imgem que forma a pe�a
typedef struct PIECE {
  int xPos, yPos;
  int choice;
  int state, vel;
  int format[4][2];
  SDL_Surface *img;
} PIECE;

#endif // STRUCTURES_H_INCLUDED
