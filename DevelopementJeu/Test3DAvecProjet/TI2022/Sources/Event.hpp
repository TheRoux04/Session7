/// @file Event.hpp
/// @brief Classe d'informations d'événement.
/// @author Eugène-Emmanuël Dubuc <eugene-emmanuel@hotmail.com>

#pragma once

#include <SDL2/SDL.h>

/// @class Event
/// @brief Gestion d'informations d'un événement.
class Event {
private:
    static SDL_Event sdlEvent;   ///< Conteneur d'informations relatives à un événement.

public:
    /// @brief Obtention du type de l'événement.
    /// @return Identifiant du type d'événement.
    static unsigned int getType() {
        return sdlEvent.type;
    }

    /// @brief Obtention du code de l'événement personnalisé.
    /// @return Code d'événement personnalisé.
    static unsigned int getCustomCode() {
        return sdlEvent.user.code;
    }

    /// @brief Récupération des informations et défilement d'un événement.
    /// @return S'il reste des événéments à traiter.
    static int poll() {
        return SDL_PollEvent(&sdlEvent);
    }

    /// @brief Obtention de la position de la souris.
    /// @param x Position horizontale de la souris.
    /// @param y Position verticale de la souris.
    static SDL_Point getMousePosition() {
        return { sdlEvent.motion.x, sdlEvent.motion.y };
    }

    /// @brief Obtention du bouton de la souris.
    /// @return Bouton de la souris cliqué.
    static unsigned int getMouseButton() {
        return sdlEvent.button.button;
    }
    
    /// @brief Récupère la touche du clavier cliquée
    /// @return Retourne la table ASCII de la touche
    static char getKey() {
        return sdlEvent.key.keysym.sym;
    }

    /// @brief Envoie d'un événement personnalisé.
    /// @param code Code de l'événement personnalisé.
    static void pushCustomEvent(const unsigned int &code) {
        SDL_Event event;
        event.type = SDL_USEREVENT;
        event.user.code = code;
        SDL_PushEvent(&event);
    }
};

SDL_Event Event::sdlEvent;
