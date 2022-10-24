/// @file Button.hpp
/// @brief Contrôle visuel: Bouton
/// @author Jean-Philippe Miguel-Gagnon, Isabelle Provost

#pragma once

#include <string>

#include "../../Rectangle.hpp"
#include "Drawable2d.hpp"

/// @class Boutton
/// @brief Bouton générique.
class Button : public Drawable2d {
protected:
    void (*action)();   ///< Action à effectuer lors d'un clic.
    bool enabled;       ///< Disponibilité.
    Vector3d size;      ///< Taille.
    Texture *texture;   ///< Texture.

public:
    /// @param position Position du bouton.
    /// @param size Taille du bouton.
    Button(const Vector3d &position, const Vector3d &size) {
        this->position = position;
        this->size = size;
        texture = nullptr;
        enabled = true;
        action = nullptr;
        anchor = TOP_LEFT;
    };

    virtual ~Button() {};

    /// @brief Assignation d'une action au bouton.
    /// @param action Action à exécuter.
    void setAction(void (*action)()) {
        this->action = action;
    };

    /// @brief Déclenchement de l'action du bouton.
    void notification() {
        if (enabled && action && Event::getMouseButton() == SDL_BUTTON_LEFT) {
            const SDL_Point mousePosition = Event::getMousePosition();
            if (mousePosition.x >= position.x && mousePosition.x <= position.x + size.x && mousePosition.y >= position.y && mousePosition.y <= position.y + size.y) {
                action();
            }
        }
    }

    /// @brief Affichage du bouton.
    virtual void draw() = 0;

    /// @brief Détermine si le bouton est activé.
    /// @return Vrai si le bouton est activé.
    bool isEnabled() const {
        return enabled;
    }

    /// @brief Active ou désactive le bouton.
    /// @param state Vrai pour activer le bouton.
    void setEnabled(bool state) {
        this->enabled = state;
    }
};
