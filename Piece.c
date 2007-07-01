/*typedef struct PIECE {
  int xPos, xPos;
  int hit, choice;
  int state;
  SDL_Surface *block;
  SDL_Rect rect;
  int **format;
} PIECE;*/


void init_piece(PIECE *self, int tipo) {
  int i;

  self->xPos = 4;
  self->yPos = 0;
  self->hit = 0;
  self->choice = tipo;
  self->state = 1;

  if (tipo == 1) {//Line
    self->block = load_image(".\\img\\red.png");
    for (i=0; i<4; i++) {
      self->format[i][0] = 0;
      self->format[i][1] = i;
    }
  }
  if (tipo == 2) {//cubo
    self->block = load_image(".\\img\\orange.png");
    self->format[0][0] = 0; self->format[0][1] = 0;
    self->format[1][0] = 1; self->format[1][1] = 0;
    self->format[2][0] = 0; self->format[2][1] = 1;
    self->format[3][0] = 1; self->format[3][1] = 1;
  }
  else if (tipo == 3) {//Z
		self->block = load_image(".\\img\\yellow.png");
		self->format[0][0] = 0; self->format[0][1] = 0;
		self->format[1][0] = 1; self->format[1][1] = 0;
		self->format[2][0] = 1; self->format[2][1] = 1;
		self->format[3][0] = 2; self->format[3][1] = 1;
  }
	else if (tipo == 4) {//S
		self->block = load_image(".\\img\\green.png");
		self->format[0][0] = 0; self->format[0][1] = 1;
		self->format[1][0] = 1; self->format[1][1] = 1;
		self->format[2][0] = 1; self->format[2][1] = 0;
		self->format[3][0] = 2; self->format[3][1] = 0;
	}
	else if (tipo == 5) {//T
		self->block = load_image(".\\img\\azul.png");
		self->format[0][0] = 0; self->format[0][1] = 0;
		self->format[1][0] = 1; self->format[1][1] = 0;
		self->format[2][0] = 1; self->format[2][1] = 1;
		self->format[3][0] = 2; self->format[3][1] = 0;
	}
	else if (tipo == 6) {//F
		self->block = load_image(".\\img\\anil.png");
		self->format[0][0] = 0; self->format[0][1] = 0;
		self->format[1][0] = 0; self->format[1][1] = 1;
		self->format[2][0] = 0; self->format[2][1] = 2;
		self->format[3][0] = 1; self->format[3][1] = 0;
	}
	else if (tipo == 7) {
		self->block = load_image(".\\img\\purple.png");
		self->format[0][0] = 0; self->format[0][1] = 0;
		self->format[1][0] = 1; self->format[1][1] = 0;
		self->format[2][0] = 1; self->format[2][1] = 1;
		self->format[3][0] = 1; self->format[3][1] = 2;
	}
}

void draw_piece(PIECE *self, SDL_Surface *screen, int next) {
  int i;

  if (next) {
    for (i=0; i<4; i++) {
      blit_surface(screen, self->block, 230+((self->xPos + self->format[i][0])*30), 50+(self->yPos + self->format[i][1])*30);
    }
  } else {
    for (i=0; i<4; i++) {
      blit_surface(screen, self->block, 10+((self->xPos + self->format[i][0])*30), 10+(self->yPos + self->format[i][1])*30);
    }
  }
}

void move_piece(PIECE *self, SDLKey key, GRID *grid) {
  if (key == SDLK_RIGHT) {
    if (!collision(self, grid, 2)) {
      if ((self->xPos+self->format[3][0]) < 9)
        self->xPos +=1;
    }
  } else if (key == SDLK_LEFT) {
    if (!collision(self, grid, 3)) {
      if (self->xPos > 0)
        self->xPos -=1;
    }
  }
}

void fall_piece(PIECE *self) {
		if (self->yPos < 15) {
			self->yPos +=1;
		}
}

int rotate_piece(PIECE *self) {
  if (self->choice != 1 && self->xPos+self->format[3][0] >= 9) {
    return 0;
  } else if(self->xPos+self->format[3][0] >=7 && self->state == 1) {
    return 0;
  }
  if (self->choice == 1) {
    if (self->state == 1 ){
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 1; self->format[1][1] = 0;
      self->format[2][0] = 2; self->format[2][1] = 0;
      self->format[3][0] = 3; self->format[3][1] = 0;
      self->state = 2;
    } else if (self->state ==2) {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 0; self->format[1][1] = 1;
      self->format[2][0] = 0; self->format[2][1] = 2;
      self->format[3][0] = 0; self->format[3][1] = 3;
      self->state = 1;
    }
  }
  else if (self->choice == 3) {
    if (self->state == 1) {
      self->format[0][0] = 1; self->format[0][1] = 0;
      self->format[1][0] = 0; self->format[1][1] = 1;
      self->format[2][0] = 0; self->format[2][1] = 2;
      self->format[3][0] = 1; self->format[3][1] = 1;
      self->state = 2;
    } else {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 1; self->format[1][1] = 0;
      self->format[2][0] = 1; self->format[2][1] = 1;
      self->format[3][0] = 2; self->format[3][1] = 1;
      self->state = 1;
    }
  }
  else if (self->choice == 4) {
    if (self->state == 1) {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 0; self->format[1][1] = 1;
      self->format[2][0] = 1; self->format[2][1] = 1;
      self->format[3][0] = 1; self->format[3][1] = 2;
      self->state = 2;
    } else {
      self->format[0][0] = 0; self->format[0][1] = 1;
      self->format[1][0] = 1; self->format[1][1] = 1;
      self->format[2][0] = 1; self->format[2][1] = 0;
      self->format[3][0] = 2; self->format[3][1] = 0;
      self->state = 1;
    }
  }
  else if (self->choice == 5) {
    if (self->state == 1) {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 0; self->format[1][1] = 1;
      self->format[2][0] = 0; self->format[2][1] = 2;
      self->format[3][0] = 1; self->format[3][1] = 1;
      self->state = 2;
    } else if (self->state == 2) {
      self->format[0][0] = 1; self->format[0][1] = 0;
      self->format[1][0] = 0; self->format[1][1] = 1;
      self->format[2][0] = 1; self->format[2][1] = 1;
      self->format[3][0] = 2; self->format[3][1] = 1;
      self->state = 3;
    } else if (self->state == 3) {
      self->format[0][0] = 1; self->format[0][1] = 0;
      self->format[1][0] = 0; self->format[1][1] = 1;
      self->format[2][0] = 1; self->format[2][1] = 1;
      self->format[3][0] = 1; self->format[3][1] = 2;
      self->state = 4;
    } else {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 1; self->format[1][1] = 0;
      self->format[2][0] = 1; self->format[2][1] = 1;
      self->format[3][0] = 2; self->format[3][1] = 0;
      self->state = 1;
    }
  }
  else if (self->choice == 6) {
    if (self->state == 1) {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 0; self->format[1][1] = 1;
      self->format[2][0] = 1; self->format[2][1] = 1;
      self->format[3][0] = 2; self->format[3][1] = 1;
      self->state = 2;
    } else if (self->state == 2) {
      self->format[0][0] = 1; self->format[0][1] = 0;
      self->format[1][0] = 1; self->format[1][1] = 1;
      self->format[2][0] = 0; self->format[2][1] = 2;
      self->format[3][0] = 1; self->format[3][1] = 2;
      self->state = 3;
    } else if (self->state == 3) {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 1; self->format[1][1] = 0;
      self->format[2][0] = 2; self->format[2][1] = 0;
      self->format[3][0] = 2; self->format[3][1] = 1;
      self->state = 4;
    } else {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 0; self->format[1][1] = 1;
      self->format[2][0] = 0; self->format[2][1] = 2;
      self->format[3][0] = 1; self->format[3][1] = 0;
      self->state = 1;
    }
  }
  else if (self->choice == 7) {
    if (self->state == 1) {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 0; self->format[1][1] = 1;
      self->format[2][0] = 1; self->format[2][1] = 0;
      self->format[3][0] = 2; self->format[3][1] = 0;
      self->state = 2;
    }
    else if (self->state == 2) {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 0; self->format[1][1] = 1;
      self->format[2][0] = 0; self->format[2][1] = 2;
      self->format[3][0] = 1; self->format[3][1] = 2;
      self->state = 3;
    }
    else if (self->state == 3) {
      self->format[0][0] = 0; self->format[0][1] = 1;
      self->format[1][0] = 1; self->format[1][1] = 1;
      self->format[2][0] = 2; self->format[2][1] = 0;
      self->format[3][0] = 2; self->format[3][1] = 1;
      self->state = 4;
    }
    else {
      self->format[0][0] = 0; self->format[0][1] = 0;
      self->format[1][0] = 1; self->format[1][1] = 0;
      self->format[2][0] = 1; self->format[2][1] = 1;
      self->format[3][0] = 1; self->format[3][1] = 2;
      self->state = 1;
    }
  }
  return 1;
}
