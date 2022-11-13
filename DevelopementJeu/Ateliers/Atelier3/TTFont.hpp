#pragma once
#include "GLContext.hpp"
using namespace std;
class TTFont
{
private:
        SDL_Surface* sdlSurface;
        TTF_Font* font;

public:
    TTFont(const char* fontText, int size){
        font = TTF_OpenFont(fontText, 42);
       
    };

    ~TTFont(){
        TTF_CloseFont(font);
    };

    SDL_Surface* getSurface(string text, SDL_Color color){
        sdlSurface = TTF_RenderText_Blended(font, text.c_str(), color);
        unsigned int realPitch = sdlSurface->w * sdlSurface->format->BytesPerPixel;
        unsigned char* srcPointer = (unsigned char*)sdlSurface->pixels;
        unsigned char* dstPointer = srcPointer;
        for (size_t i = 0; i < sdlSurface->h; i++)
        {
            memmove(dstPointer, srcPointer, realPitch);
            dstPointer += realPitch;
            srcPointer += sdlSurface->pitch;
        }
        sdlSurface->pitch = realPitch;

        return sdlSurface;
    }
};

