void removeline_grid(int line);

// Inicializa a grade que vai conter a pecas
//que ja estao no jogo
void init_grid() {
  int i, j;

  for (i=0; i<18; i++) {
    for (j=0; j<10; j++) {
      grid[i][j] = 0;
    }
  }
  for (i=0; i<10; i++) {
    grid[17][i] = 8; // Essa linha e preenchia com 8 para garantir que a peca chegou ao fim
  }

}

// Adiciona um peca a grade, colocando o numero 'choice' que repesenta a peca
//nas posicoes que a peca ocupa
void adiciona_a_grid(PIECE peca) {
  int i, x, y;
  for (i=0; i<4; i++) {
    x = peca.format[i][0] + peca.xPos;
    y = peca.format[i][1] + peca.yPos;
    grid[y][x] = peca.choice;
  }
}

// Mostra a grade, cada valor nela e equivalente a
// uma cor de bloco: 1-Red, 2-orange, 3-yellow, 4-green, 5-azul, 6-anil, 7-purple
void draw_grid() {
  int x, y;
  for (y=0; y<17; y++) {
    for (x=0; x<10; x++) {
      if (grid[y][x] == 1) {
        blit_at_surface(red_block, (6+(x*30)), 6+(y*30));
      } else if (grid[y][x] == 2) {
        blit_at_surface(orange_block, (6+(x*30)), 6+(y*30));
      } else if (grid[y][x] == 3) {
        blit_at_surface(yellow_block, (6+(x*30)), 6+(y*30));
      } else if (grid[y][x] == 4) {
        blit_at_surface(green_block, (6+(x*30)), 6+(y*30));
      } else if (grid[y][x] == 5) {
        blit_at_surface(azul_block, (6+(x*30)), 6+(y*30));
      } else if (grid[y][x] == 6) {
        blit_at_surface(anil_block, (6+(x*30)), 6+(y*30));
      } else if (grid[y][x] == 7) {
        blit_at_surface(purple_block, (6+(x*30)), 6+(y*30));
      }
    }
  }
}

// Checa se a linha ja esta preenchida procurando por '0's, se nao tiver
// nenhum zero na linha siginifica que ela esta preenchida, entao zera-se
// esta linha e chama a funcao remove_line para fazer a animacao das pecas
// descendo
void linefilled_grid() {
  int has = 1, x, y;
  for (y=0; y<17; y++) {
    for (x=0; x<10; x++) {
      if (grid[y][x] == 0) {
        x = 9;
        has = 0;
      }
    }
    if (has) {
      for (x=0; x<10; x++) {
        grid[y][x] = 0;
        removeline_grid(y);
        pnt += 1;
      }
    }
    has = 1;
  }
}

// Move as linhas acima da linha que foi preenchida
void removeline_grid(int line) {
  int has = 1;
  int x, y;
  for (y=line; y>0; y--) {
    for (x=0; x<10; x++) {
      if (grid[y][x] != 0) {
        x = 9;
        has = 0;
      }
    }
    if (has) {
      for (x=0; x<10; x++) {
        grid[y][x] = grid[y-1][x];
        grid[y-1][x] = 0;
      }
    }
    has = 1;
  }
  if (pnt >= (lvl*100) + ((lvl-1)*100)) {
    lvl += 1;
  }
}
