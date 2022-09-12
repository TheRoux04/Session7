#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_opengl.h>


//NOTES DE COURS SUR etudions.ca

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Event sdlEvent;
  SDL_Window* sdlWindow = SDL_CreateWindow("Ma première fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_RESIZABLE);
  SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  //SDL_GLContext glContext = SDL_GL_CreateContext(sdlWindow);

  //glClear(GL_COLOR_BUFFER_BIT);

  bool isOpen = true;
  while (isOpen){
    //Gestion des  événements
    while (SDL_PollEvent(&sdlEvent)) {
      switch (sdlEvent.type){
      case SDL_QUIT:
        isOpen = false;
        break;
      }
    }
    
    //Gestion des mises à jour

    SDL_RenderClear(sdlRenderer);
    //Gestion de l'affichage
    SDL_RenderPresent(sdlRenderer);
  }
  
  

  //SDL_GL_SwapWindow(sdlWindow);
  //SDL_GL_DeleteContext(sdlWindow);
  SDL_DestroyRenderer(sdlRenderer);
  SDL_DestroyWindow(sdlWindow);

  SDL_Quit();

  return 0;
}
