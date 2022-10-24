/// @file Window.hpp
/// @brief Fenêtre du système d'exploitation
/// @author Olivier Savoie (1908527\etu.cegep-lanaudiere.qc.ca)

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/// @class Window
/// @brief Classe représentant une fenêtre du système d'exploitation
class Window
{ 
protected:
    SDL_Window* sdlWindow; ///< Fenêtre

public:
    /// @param title Titre de la fenêtre
    /// @param x Position sur l'axe des x
    /// @param y Position sur l'axe des y
    /// @param width Largeur
    /// @param height Hauteur
    /// @param flags Indicateurs de la fenêtre
    Window(const char* title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 640, int height = 480, unsigned int flags = 0){
        sdlWindow = SDL_CreateWindow(title, x, y, width, height, flags);
    }

    virtual ~Window(){
        SDL_DestroyWindow(sdlWindow);
    }

    /// @brief Obtention de l'identifiant
    /// @return Identifiant
    unsigned int getId(){
        return SDL_GetWindowID(sdlWindow);
    }
    
   

    /// @brief Vider le contenu
    virtual void clear() = 0;
    /// @brief Rafraîchir le contenu
    virtual void refresh() = 0;
};
