#include <SDL2/SDL.h>
#include <stdio.h>

#include "CG.h"

SDL_Event sdlEvent;




int main (){

GerenciadorGrafico gerenciador(1024,768);



  bool finish = false;

  while(!finish)
  {
    while(SDL_PollEvent(&sdlEvent))
    {
      if(sdlEvent.type == SDL_QUIT)
      {
        finish = true;
        break;
      }

     /* if(sdlEvent.key.keysym.sym == SDLK_1)
      {
        if(sdlEvent.key.state == SDL_PRESSED)
          
      }

      if(sdlEvent.key.keysym.sym == SDLK_2)
      {
        if(sdlEvent.key.state == SDL_PRESSED)
          
      }*/

     

    }




}
}
