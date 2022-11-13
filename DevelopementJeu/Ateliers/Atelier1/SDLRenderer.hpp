#include <SDL2/SDL.h>
#include "Window.hpp"
#pragma once


using namespace std;

class SDLRenderer : public Window
{
private:
    SDL_Renderer* sdlRenderer;
public:
    SDLRenderer(){
        sdlWindow = SDL_CreateWindow("Ma première fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
        sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    }
    ~SDLRenderer(){
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(sdlWindow);
    }

    void clear(){
        SDL_RenderClear(sdlRenderer);
    }

    void refresh(){
        SDL_RenderPresent(sdlRenderer);
    }
};

