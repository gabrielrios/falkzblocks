#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

// Estrutura da peças
// xPos yPos = posição relativa da tela
// choice = Qual peça
// State = qual a rotação da peça
// vel = Velocidade de descida
// Format = a peça
// img = referencia para a imgem que forma a peça
typedef struct PIECE {
  int xPos, yPos;
  int choice;
  int state, vel;
  int format[4][2];
  SDL_Surface *img;
} PIECE;

#endif // STRUCTURES_H_INCLUDED
