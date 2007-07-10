#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

// Estrutura da pecas
// xPos yPos = posicao relativa da tela
// choice = Qual peca
// State = qual a rotaca da peca
// vel = Velocidade de descida
// Format = a peca
// img = referencia para a imgem que forma a peca
typedef struct PIECE {
  int xPos, yPos;
  int choice;
  int state, vel;
  int format[4][2];
  SDL_Surface *img;
} PIECE;

#endif // STRUCTURES_H_INCLUDED
