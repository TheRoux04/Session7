/// @file TTFont.hpp
/// @brief Police de caractères.
/// @author Patrick Singcaster <singcaster@clogik.io>, Louis-Félix Veillette <2038026@etu.cegep-lanaudiere.qc.ca>

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Constants.hpp"
#include "Resource.hpp"

/// @class TTFont
/// @brief Police de caractères.
class TTFont : public Resource {
private:
    TTF_Font *font;

public:
    /// @param name Nom de la police de caractères. Le chemin va être préfixé par Constants::FONTS_PATH.
    /// @param size Taille de la police de caractères, par défaut la taille par défaut.
    TTFont(const string &fileName = DEFAULT_FONT, const int &size = DEFAULT_FONT_SIZE) {
        font = TTF_OpenFont((FONTS_PATH + fileName).c_str(), size);
    }

    ~TTFont() {
        TTF_CloseFont(font);
    }

    SDL_Point getSize(const string& text) {
        SDL_Point size;
        size.x = 0;
        size.y = 0;
        TTF_SizeUTF8(font, text.c_str(), &size.x, &size.y);
        return size;
    }

    /// @brief Génération d'une surface de texte coloré.
    /// @param text Chaîne de caractères.
    /// @param color Couleur du texte.
    /// @return Surface de texte coloré.
    SDL_Surface *renderTextBlended(const char *text, const SDL_Color &color) {
        SDL_Surface *sdlSurface = TTF_RenderUTF8_Blended(font, text, color);
        unsigned int realPitch = sdlSurface->w * sdlSurface->format->BytesPerPixel;
        unsigned char *srcPointer = (unsigned char *) sdlSurface->pixels;
        unsigned char *dstPointer = srcPointer;
        for (int y = 0; y < sdlSurface->h; y++) {
            memmove(dstPointer, srcPointer, realPitch);
            dstPointer += realPitch;
            srcPointer += sdlSurface->pitch;
        }

        sdlSurface->pitch = realPitch;
        return sdlSurface;
    }

    /// @brief Hérite de la classe Resource.
    void inherit() {
    }
};
