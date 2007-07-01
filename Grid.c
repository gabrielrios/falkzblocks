/*typedef struct GRID {
  int layer[10][17];
  SDL_Surface block_img[7];
} GRID;*/

void removeline_grid(GRID *self, int line);

void init_grid(GRID *self) {
  int i, j;

  for (i=0; i<17; i++) {
    for (j=0; j<10; j++) {
      self->layer[i][j] = 0;
    }
  }
  for (i=0; i<10; i++) {
    self->layer[16][i] = 8;
  }
  self->block_img[0] = load_image(".\\img\\red.png");
  self->block_img[1] = load_image(".\\img\\orange.png");
	self->block_img[2] = load_image(".\\img\\yellow.png");
	self->block_img[3] = load_image(".\\img\\green.png");
	self->block_img[4] = load_image(".\\img\\azul.png");
	self->block_img[5] = load_image(".\\img\\anil.png");
	self->block_img[6] = load_image(".\\img\\purple.png");
}

void draw_grid(GRID *self, SDL_Surface *screen) {
  int x, y;
  for (y=0; y<16; y++) {
    for (x=0; x<10; x++) {
      if (self->layer[y][x] != 0) {
        blit_surface(screen, self->block_img[self->layer[y][x]-1], (10+(x*30)), 10+(y*30));
      }
    }
  }
}

void add_grid(GRID *self, PIECE *piece) {
  int i, x, y;
  for (i=0; i<4; i++) {
    x = piece->format[i][0] + piece->xPos;
    y = piece->format[i][1] + piece->yPos;
    self->layer[y][x] = piece->choice;
  }
}

void linefilled_grid(GRID *self) {
  int has = 1, x, y;
  for (y=0; y<16; y++) {
    for (x=0; x<10; x++) {
      if (self->layer[y][x] == 0) {
        x = 9;
        has = 0;
      }
    }
    if (has) {
      for (x=0; x<10; x++) {
        self->layer[y][x] = 0;
        removeline_grid(self, y);
        pnt += 100;
      }
    }
    has = 1;
  }
}

void removeline_grid(GRID *self, int line) {
  int has = 1;
  int x, y;
  for (y=line; y>0; y--) {
    for (x=0; x<10; x++) {
      if (self->layer[y][x] != 0) {
        x = 9;
        has = 0;
      }
    }
    if (has) {
      for (x=0; x<10; x++) {
        self->layer[y][x] = self->layer[y-1][x];
        self->layer[y-1][x] = 0;
      }
    }
    has = 1;
  }
}
