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
    unsigned int textureId;
    TTF_Font* ttfFont;
    int w, h;
public:
    /// @param title Titre de la fenêtre
    /// @param x Position sur l'axe des x
    /// @param y Position sur l'axe des y
    /// @param width Largeur
    /// @param height Hauteur
    /// @param windowFlags Indicateurs de la fenêtre
    GLContext(const char* title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 640, int height = 480, unsigned int windowFlags = 0) 
    : Window(title, x, y, width, height, windowFlags | SDL_WINDOW_OPENGL){
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
        glContext = SDL_GL_CreateContext(sdlWindow);
        SDL_GL_SetSwapInterval(0);

        projectionMatrix.loadOrthographic(width, height);

        ttfFont = TTF_OpenFont("varsity_regular.ttf", 42);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

      


        SDL_Surface* sdlSurface = IMG_Load("pingouin.png");
        //SDL_Surface* sdlSurface = TTF_RenderText_Blended(ttfFont, "HELLO WORLD!", {255, 0, 0, 255});
        w = sdlSurface->w;
        h = sdlSurface->h;

        /*unsigned int realPitch = sdlSurface->w * sdlSurface->format->BytesPerPixel;
        unsigned char* srcPointer = (unsigned char*)sdlSurface->pixels;
        unsigned char* dstPointer = srcPointer;
        for (size_t i = 0; i < sdlSurface->h; i++)
        {
            memmove(dstPointer, srcPointer, realPitch);
            dstPointer += realPitch;
            srcPointer += sdlSurface->pitch;
        }
        sdlSurface->pitch = realPitch;*/

        #ifdef __APPLE__
            glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, sdlSurface->w, sdlSurface->h,
                                    0, GL_BGRA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        #else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h,
                                    0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        #endif

        SDL_FreeSurface(sdlSurface);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    ~GLContext() {
        TTF_CloseFont(ttfFont);
        //glDeleteTextures(1, &textureId);
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

        glBindTexture(GL_TEXTURE_2D, textureId);
        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0); glVertex3d(0.0, 0.0, 0.0);
            glTexCoord2d(1.0, 0.0); glVertex3d(w, 0.0, 0.0);
            glTexCoord2d(1.0, 1.0); glVertex3d(w, h, 0.0);
            glTexCoord2d(0.0, 1.0); glVertex3d(0.0, h, 0.0);
        glEnd();

        //fps++
    }

    void refresh() {
        SDL_GL_SwapWindow(sdlWindow);
    }
};

