#pragma once
#include <iostream>   // std::cout
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Window.hpp"
#include "Matrix44d.hpp"
#include "TTFont.hpp"
#include "Texture.hpp"
#include "Chrono.hpp"

using namespace std;

class GLContext : public Window
{
private:
    SDL_GLContext glContext;
    Matrix44d projectionMatrix;
    TTFont* font;
    Texture* texture;
    Chrono chrono;
    int fps;

public:
    /// @param title Titre de la fenêtre
    /// @param x Position sur l'axe des x
    /// @param y Position sur l'axe des y
    /// @param width Largeur
    /// @param height Hauteur
    /// @param windowFlags Indicateurs de la fenêtre
    GLContext(const char* title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 640, int height = 480, unsigned int windowFlags = 0) 
    : Window(title, x, y, width, height, windowFlags | SDL_WINDOW_OPENGL){
        TTF_Init();
        glContext = SDL_GL_CreateContext(sdlWindow);
        SDL_GL_SetSwapInterval(0);
        projectionMatrix.loadOrthographic(width, height);

        font = new TTFont("varsity_regular.ttf", 42);
        string text = to_string(fps);
        texture = new Texture(font->getSurface("fps: " + text, {255, 0, 0, 255}));
    
    }

    ~GLContext() {
        delete font;
        delete texture;
        SDL_GL_DeleteContext(glContext);
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
            glTexCoord2d(0.0, 0.0); glVertex3d(0.0, 0.0, 0.0);
            glTexCoord2d(1.0, 0.0); glVertex3d(texture->getWidth(), 0.0, 0.0);
            glTexCoord2d(1.0, 1.0); glVertex3d(texture->getWidth(), texture->getHeight(), 0.0);
            glTexCoord2d(0.0, 1.0); glVertex3d(0.0, texture->getHeight(), 0.0);
        glEnd();

    }

    void refresh() {
        fps++;
        if (chrono.delta() >= 1.0) {
            chrono.reset();
            string text = to_string(fps);
            texture = new Texture(font->getSurface("fps: " + text, {255, 0, 0, 255}));
            fps = 0;
        }
        SDL_GL_SwapWindow(sdlWindow);
    }
};

