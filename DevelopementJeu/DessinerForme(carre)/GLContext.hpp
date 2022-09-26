#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Window.hpp"
#include "Matrix44d.hpp"


class GLContext : public Window
{
private:
    SDL_GLContext glContext;
    Matrix44d projectionMatrix;
public:
    /// @param title Titre de la fenêtre
    /// @param x Position sur l'axe des x
    /// @param y Position sur l'axe des y
    /// @param width Largeur
    /// @param height Hauteur
    /// @param windowFlags Indicateurs de la fenêtre
    GLContext(const char* title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 640, int height = 480, unsigned int windowFlags = 0) 
    : Window(title, x, y, width, height, windowFlags | SDL_WINDOW_OPENGL){
        glContext = SDL_GL_CreateContext(sdlWindow);
        projectionMatrix.loadOrthographic(width, height);
    }
    ~GLContext() {
        SDL_GL_DeleteContext(sdlWindow);
    }

    void clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void draw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(projectionMatrix.elements);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glBegin(GL_QUADS);
            glColor4d(1.0, 0.0, 0.0, 1.0);
            glVertex3d(25.0, 25.0, 0.0);
            glColor4d(0.0, 1.0, 0.0, 1.0);
            glVertex3d(125.0, 25.0, 0.0);
            glColor4d(0.0, 0.0, 1.0, 1.0);
            glVertex3d(125.0, 125.0, 0.0);
            glColor4d(1.0, 1.0, 1.0, 1.0);
            glVertex3d(25.0, 125.0, 0.0);
        glEnd();
    }

    void refresh() {
        SDL_GL_SwapWindow(sdlWindow);
    }
};

