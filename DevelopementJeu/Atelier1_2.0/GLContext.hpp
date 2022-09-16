#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include "Window.hpp"
#include <SDL2/SDL_opengl.h>


class GLContext : public Window
{
private:
    SDL_GLContext glContext;
public:
    GLContext(){
        glContext =SDL_GL_CreateContext(sdlWindow);
    }
    ~GLContext(){
        SDL_GL_DeleteContext(sdlWindow);
    }

    void clear(){
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void refresh(){
        SDL_GL_SwapWindow(sdlWindow);
    }
};

