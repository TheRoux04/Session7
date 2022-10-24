/// @file CheckBox.hpp
/// @brief Contrôle visuel: CheckBox
/// @author Olivier Savoie et Thomas Laporte

#pragma once

#include "../../Rectangle.hpp"
#include "../../Vector3d.hpp"
#include "Drawable2d.hpp"

/// @class CheckBox
/// @brief Contrôle visuel qui permet de sélectionner une option.
class CheckBox : public Drawable2d {
private:
    Vector3d size;      ///< Taille.
    bool checked;       ///< Case cochée ou non (Valeur).
    void (*action)();   ///< Action à effectuer lorsque l'état change.

public:

    /// @brief Constructeur checkbox.
    /// @param position     ///< Position du checkbox.
    /// @param size         ///< Taille du checkbox.
    /// @param checked      ///< Case cochée ou non.
    CheckBox(Vector3d position, Vector3d size, bool checked = false) {
        this->position = position;
        this->size = size;
        this->checked = checked;
        anchor = TOP_LEFT;
    }

    /// @brief Assignation d'une action à la case à cocher.
    /// @param newAction Action à exécuter.
    void setAction(void (*newAction)()) {
        action = newAction;
    };    

    /// @brief Cocher la case.
    void setChecked() {
        this->checked = true;
    }

    /// @brief Décocher la case.
    void setUnchecked() {
        this->checked = false;
    }
    
    /// @brief Retourne la valeur de la case.
    /// @return true si la case est cochée, false sinon.
    bool isChecked() {
        return this->checked;
    }

    /// @brief Affichage de la case.
    void draw(){
        // Bordure
        Rectangle::drawColor(position, size, COLOR_WHITE, anchor);

        // Fond
        Rectangle::drawColor({position.x + size.x * 0.12, position.y + size.x * 0.12}, {size.x * 0.76, size.y * 0.76}, COLOR_BLACK, anchor);

        // Cocher
        if (checked) {
            Rectangle::drawColor({position.x + size.x * 0.3, position.y + size.x * 0.3}, {size.x * 0.4, size.y * 0.4}, COLOR_WHITE, anchor);
        }
    }

    /// @brief Gestion des événements.
    void notification() {
        if (Event::getType() == SDL_MOUSEBUTTONDOWN) {
            SDL_Point mousePosition = Event::getMousePosition();
            if (mousePosition.x >= position.x && mousePosition.x <= position.x + size.x && mousePosition.y >= position.y && mousePosition.y <= position.y + size.y) {
                checked = !checked;
                if (action)
                    action();
            }
        }
    }
};
    

