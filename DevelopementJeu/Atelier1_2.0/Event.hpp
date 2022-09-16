/// @file Event.hpp
/// @brief Gestionnaire d'informations d'événements
/// @author Olivier Savoie (1908527\etu.cegep-lanaudiere.qc.ca)

#pragma once

#include <SDL2/SDL.h>

/// @class Event
/// @brief Classe permettant d'obtenir l'informations d'événements
class Event
{
private:
    static SDL_Event sdlEvent; ///< Conteneur d'informations d'événements
public:
    /// @brief Obtention des informations du prochain événement
    /// @return Le nombre d'événements restant dans la file
    static int poll(){
        return SDL_PollEvent(&sdlEvent);
    }

    /// @brief Obtention du type d'événement
    /// @return Type de l'événement
    static unsigned int getType(){
        return sdlEvent.type;
    }

    /// @brief Obtention du type d'événement de fenêtre
    /// @return Type de l'événement
    static unsigned int getWindowEventType(){
        return sdlEvent.window.event;
    }

    /// @brief Obtention d'identifiant de fenêtre
    /// @return Identifiant
    static unsigned int getWindowId(){
        return sdlEvent.window.windowID;
    }
};

SDL_Event Event::sdlEvent;