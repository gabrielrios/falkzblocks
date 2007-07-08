void init_piece(PIECE *self, int tipo) {
  int i;

  self->xPos = 4;
  self->yPos = 0;
  self->hit = 0;
  self->choice = tipo;
  self->state = 1;
  self->vel = 1;

  if (tipo == 1) {//Line
    self->img = red_block;
    for (i=0; i<4; i++) {
      self->format[i][0] = 0;
      self->format[i][1] = i;
    }
  }
  if (tipo == 2) {//cubo
    self->img = orange_block;
    self->format[0][0] = 0; self->format[0][1] = 0;
    self->format[1][0] = 1; self->format[1][1] = 0;
    self->format[2][0] = 0; self->format[2][1] = 1;
    self->format[3][0] = 1; self->format[3][1] = 1;
  }
  else if (tipo == 3) {//Z
    self->img = yellow_block;
		self->format[0][0] = 0; self->format[0][1] = 0;
		self->format[1][0] = 1; self->format[1][1] = 0;
		self->format[2][0] = 1; self->format[2][1] = 1;
		self->format[3][0] = 2; self->format[3][1] = 1;
  }
	else if (tipo == 4) {//S
    self->img = green_block;
		self->format[0][0] = 0; self->format[0][1] = 1;
		self->format[1][0] = 1; self->format[1][1] = 1;
		self->format[2][0] = 1; self->format[2][1] = 0;
		self->format[3][0] = 2; self->format[3][1] = 0;
	}
	else if (tipo == 5) {//T
    self->img = azul_block;
		self->format[0][0] = 0; self->format[0][1] = 0;
		self->format[1][0] = 1; self->format[1][1] = 0;
		self->format[2][0] = 1; self->format[2][1] = 1;
		self->format[3][0] = 2; self->format[3][1] = 0;
	}
	else if (tipo == 6) {//F
    self->img = anil_block;
		self->format[0][0] = 0; self->format[0][1] = 0;
		self->format[1][0] = 0; self->format[1][1] = 1;
		self->format[2][0] = 0; self->format[2][1] = 2;
		self->format[3][0] = 1; self->format[3][1] = 0;
	}
	else if (tipo == 7) {
    self->img = purple_block;
		self->format[0][0] = 0; self->format[0][1] = 0;
		self->format[1][0] = 1; self->format[1][1] = 0;
		self->format[2][0] = 1; self->format[2][1] = 1;
		self->format[3][0] = 1; self->format[3][1] = 2;
	}
}

void desenha_peca(PIECE self, int atual) {
  int i;

  if (atual == 1) {
    for (i=0; i<4; i++) {
      blit_at_surface(self.img, 6+(self.xPos + self.format[i][0])*30, 6+(self.yPos + self.format[i][1])*30);
    }
  } else {
    for (i=0; i<4; i++) {
      blit_at_surface(self.img, 345+(self.format[i][0])*30, 50+(self.yPos + self.format[i][1])*30);
    }
  }
}

void move_peca(PIECE *self, int key) {
  //key = 1 right, key = 2 left
  if (key == 1) {
    if (!collision(self, 2)) {
      if ((self->xPos+self->format[3][0]) < 9)
      self->xPos +=1;
    }
  } else if (key == 2) {
    if (!collision(self, 3)) {
      if (self->xPos > 0)
        self->xPos -=1;
    }
  }
}

void desce_peca(PIECE *self) {
		if (self->yPos < 16) {
			  self->yPos +=1;
		}
}

int rotaciona_peca(PIECE *self) {
  if (self->choice != 1 && self->xPos+self->format[3][0] >= 9) {
    return 0;
  } else if(self->choice == 1 && self->xPos+self->format[3][0] >= 7 && self->state == 1) {
    return 0;
  }
  if (collision(self, 1) || collision(self, 2) || collision(self, 3)) {
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
