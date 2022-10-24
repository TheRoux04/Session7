/// @file DefaultBar.hpp
/// @brief Classe pour la jauge de progression.
/// @authors Nikolas D'Amato, Jérémy Gaouette

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "ProgressBar.hpp"

/// @class DefaultBar
/// @brief Classe pour la jauge de progession.
class DefaultBar : public ProgressBar {
    private:
        SDL_Color barColor; ///< Couleur de la jauge de progression.

    public:
        /// @brief Constructeur d'une jauge de progression.
        /// @param position Position de la barre de progression.
        /// @param size Taille de la barre de progression.
        /// @param maxValue Valeur maximale de la barre de progression.
        /// @param currentValue Valeur actuelle de la barre de progression.
        /// @param backgroundColor Couleur de fond de la barre de progression.
        /// @param progressColor Couleur de la jauge de progression.
        /// @see ProgressBar
        DefaultBar(Vector3d position, Vector3d size, float maxValue = 100, float currentValue = 0, SDL_Color backgroundColor = COLOR_WHITE, SDL_Color progressColor = COLOR_GREEN) : ProgressBar(position, size, maxValue, currentValue, backgroundColor) {
            this->barColor = progressColor;
        }

        /// @brief Affichage de la jauge de progression.
        void draw() {
            ProgressBar::draw();
            
            // Jauge de progression
            glBegin(GL_QUADS);
                glColor4d(barColor.r, barColor.g, barColor.b, barColor.a);
                glVertex3d(position.x + outlineWidth, position.y + outlineWidth, 0.0);
                glVertex3d(position.x + (size.x / (this->maxValue / this->currentValue) - outlineWidth),  position.y + outlineWidth, 0.0);
                glVertex3d(position.x + (size.x / (this->maxValue / this->currentValue) - outlineWidth), position.y + size.y - outlineWidth, 0.0);
                glVertex3d(position.x + outlineWidth, position.y + size.y - outlineWidth, 0.0);
            glEnd();
        }
};