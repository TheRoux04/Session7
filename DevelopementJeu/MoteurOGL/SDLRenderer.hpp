/// @file SDLRenderer.hpp
/// @brief Gestionnaire du rendu
/// @author Olivier Savoie (1908527\etu.cegep-lanaudiere.qc.ca)

#pragma once
#include <SDL2/SDL.h>

#include "Window.hpp"

/// @class SDLRenderer
/// @brief Gestionnaire de rendu 2D
class SDLRenderer : public Window
{
private:
    SDL_Renderer* sdlRenderer; ///< Gestionnaire du rendu
public:
    /// @param title Titre de la fenêtre
    /// @param x Position sur l'axe des x
    /// @param y Position sur l'axe des y
    /// @param width Largeur
    /// @param height Hauteur
    /// @param windowFlags Indicateurs de la fenêtre
    /// @param rendererFlags Indicateurs du rendu
    SDLRenderer(const char* title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 640, int height = 480, unsigned int windowFlags = 0, unsigned int rendererFlags = 0) 
    : Window(title, x, y, width, height, windowFlags){
        sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, rendererFlags);
    }

    ~SDLRenderer(){
        SDL_DestroyRenderer(sdlRenderer);
    }

    void clear(){
        SDL_RenderClear(sdlRenderer);
    }

    void refresh(){
        SDL_RenderPresent(sdlRenderer);
    }
};

