
/*This source code copyrighted by Lazy Foo' Productions (2004-2007) and may not be redestributed without written permission.*/

//The headers
#include "SDL.h"
#include "SDL_image.h"
#include <stdlib.h>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *foo = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

SDL_Surface *load_image( char *filename ) {

  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;

  loadedImage = IMG_Load( filename );

  if( loadedImage != NULL ) {
    optimizedImage = SDL_DisplayFormat( loadedImage );
    SDL_FreeSurface( loadedImage );

    if( optimizedImage != NULL ) {
      Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
      SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey );
    }
  }
  return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
    //Temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Get the offsets
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

int init() {
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return 1;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Foo says \"Hello!\"", NULL );

    //If everything initialized fine
    return 1;
}

int load_files() {
    //Load the background image
    background = load_image( ".\\img\\background.png" );

    //If the background didn't load
    if( background == NULL )
    {
        return 0;
    }

    //Load the stick figure
    foo = load_image( ".\\img\\foo.png" );

    //If the stick figure didn't load
    if( foo == NULL )
    {
        return 0;
    }

    return 1;
}

void clean_up() {
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( foo );

    //Quit SDL
    SDL_Quit();
}

int main(int argc, char* args[]) {
    //Quit flag
    int quit = 0;

    //Initialize
    if( init() == 0 )
    {
        return 1;
    }

    //Load the files
    if( load_files() == 0 )
    {
        return 1;
    }

    //Apply the surfaces to the screen
    apply_surface( 0, 0, background, screen );
    apply_surface( 240, 190, foo, screen );

    //Update the screen
    if( SDL_Flip( screen ) == -1 )
    {
        return 1;
    }

    //While the user hasn't quit
    while( quit == 0 )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = 1;
            }
        }
    }

    //Free the surfaces and quit SDL
    clean_up();

    return 0;
}
