void blit_surface(SDL_Surface *self, SDL_Surface *source, int x, int y) {
  SDL_Rect dsrect;

  dsrect.x = x;
  dsrect.y = y;
  SDL_BlitSurface(source, NULL, self, &dsrect);
}


void fill_surface(SDL_Surface *self, Uint8 r, Uint8 g, Uint8 b) {
  Uint32 color = SDL_MapRGB(self->format, r, g, b);
  SDL_FillRect(self, NULL, color);
}

SDL_Surface* surface(int W, int H) {
  SDL_Surface *self;
  self = SDL_CreateRGBSurface(SDL_SWSURFACE, W, H, 32, 0, 0, 0, 0);
  if (self == NULL) {
    fprintf(stderr, "Falha ao criar a surface");
  }
  return self;
}
