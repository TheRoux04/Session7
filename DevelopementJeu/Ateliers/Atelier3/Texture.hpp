#pragma once
#include "GLContext.hpp"

class Texture
{
private:
    unsigned int textureId;
    int w, h;
public:
    Texture(SDL_Surface* sdlSurface){

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glGenTextures(1, &textureId);

        this->w = sdlSurface->w;
        this->h = sdlSurface->h;

        glBindTexture(GL_TEXTURE_2D, textureId);

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
    Texture(string path) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        SDL_Surface* sdlSurface = IMG_Load(path.c_str());
        this->w = sdlSurface->w;
        this->h = sdlSurface->h;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        #ifdef __APPLE__
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        #else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        #endif
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    ~Texture(){
        glDeleteTextures(1, &textureId);
    }

    double getWidth(){
        return w;
    }

    double getHeight(){
        return h;
    }

    unsigned int getTextureId(){
        return textureId;
    }
};

