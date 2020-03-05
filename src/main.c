#include "vm.h"
#include "SDL/SDL.h"








int main(){
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Surface* screen = SDL_SetVideoMode(512, 512, 32, 0);

  int cont = 1;
  while(cont){

    /*
      * Run computer
      * Visualize screen, RAM stack, RAM heap, etc.
      * Eventually: cache, cache stalls
    */


    SDL_Event event;
		while(SDL_PollEvent( &event )){
			if(event.type == SDL_QUIT) cont = 0;
		}

    SDL_Flip(screen);
    SDL_Delay(16);
  }
  SDL_Quit();
}
