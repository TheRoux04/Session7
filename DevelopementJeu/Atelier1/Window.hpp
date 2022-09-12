
#include <SDL2/SDL.h>
#include "Event.hpp"
#pragma once

using namespace std;

class Window
{ 
protected:
    SDL_Window* sdlWindow;
public:
    virtual void refresh() = 0;
    virtual void clear() = 0;
};
