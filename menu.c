void menu() {
  SDL_Surface *menu_img;
  SDL_Rect clip[3][2], pos[3];
  int game=1;
  SDL_Event event;

  menu_img = load_image(".\\data\\imgs\\menu.png");

  clip[0][0].x=0;    clip[0][0].y=0;
  clip[0][0].w=198;  clip[0][0].h=34;
  clip[0][1].x=205;  clip[0][1].y=0;
  clip[0][1].w=198;  clip[0][1].h=34;
  pos[0].x=125;      pos[0].y=160;
  SDL_BlitSurface(menu_img, &clip[0][0], screen, &pos[0]);

  clip[1][0].x=0;    clip[1][0].y=42;
  clip[1][0].w=198;  clip[1][0].h=34;
  clip[1][1].x=205;  clip[1][1].y=42;
  clip[1][1].w=198;  clip[1][1].h=34;
  pos[1].x=125;      pos[1].y=200;
  SDL_BlitSurface(menu_img, &clip[1][0], screen, &pos[1]);

  clip[2][0].x=0;  clip[2][0].y=83;
  clip[2][0].w=198;  clip[2][0].h=34;
  clip[2][1].x=205;  clip[2][1].y=83;
  clip[2][1].w=198;  clip[2][1].h=34;
  pos[2].x=125;  pos[2].y=240;
  SDL_BlitSurface(menu_img, &clip[2][0], screen, &pos[2]);


  while(game) {
    SDL_Flip(screen);
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        exit(1);
      }
      if (event.type == SDL_MOUSEMOTION) {
        if (event.motion.x > pos[0].x + clip[0][0].x && (event.motion.x < pos[0].x + clip[0][0].x + clip[0][0].w) && (event.motion.y > pos[0].y) &&  (event.motion.y < pos[0].y + clip[0][0].h)) {
          SDL_BlitSurface(menu_img, &clip[0][1], screen, &pos[0]);
        } else if (event.motion.x > pos[1].x + clip[1][0].x && (event.motion.x < pos[1].x + clip[1][0].x + clip[1][0].w) && (event.motion.y > pos[1].y) &&  (event.motion.y < pos[1].y + clip[1][0].h)) {
          SDL_BlitSurface(menu_img, &clip[1][1], screen, &pos[1]);
        } else if (event.motion.x > pos[2].x + clip[2][0].x && (event.motion.x < pos[2].x + clip[2][0].x + clip[2][0].w) && (event.motion.y > pos[2].y) &&  (event.motion.y < pos[2].y + clip[2][0].h)) {
          SDL_BlitSurface(menu_img, &clip[2][1], screen, &pos[2]);
        } else {
          SDL_BlitSurface(menu_img, &clip[0][0], screen, &pos[0]);
          SDL_BlitSurface(menu_img, &clip[1][0], screen, &pos[1]);
          SDL_BlitSurface(menu_img, &clip[2][0], screen, &pos[2]);
        }
      }
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
          if (event.motion.x > pos[0].x + clip[0][0].x && (event.motion.x < pos[0].x + clip[0][0].x + clip[0][0].w) && (event.motion.y > pos[0].y) &&  (event.motion.y < pos[0].y + clip[0][0].h)) {
            game = 0;
          } else if (event.motion.x > pos[1].x + clip[1][0].x && (event.motion.x < pos[1].x + clip[1][0].x + clip[1][0].w) && (event.motion.y > pos[1].y) &&  (event.motion.y < pos[1].y + clip[1][0].h)) {
            //SDL_BlitSurface(menu_img, &clip[1][1], screen, &pos[1]);
          } else if (event.motion.x > pos[2].x + clip[2][0].x && (event.motion.x < pos[2].x + clip[2][0].x + clip[2][0].w) && (event.motion.y > pos[2].y) &&  (event.motion.y < pos[2].y + clip[2][0].h)) {
            exit(1);
          }
        }
      }
    }
  }
  SDL_FreeSurface(menu_img);
}
