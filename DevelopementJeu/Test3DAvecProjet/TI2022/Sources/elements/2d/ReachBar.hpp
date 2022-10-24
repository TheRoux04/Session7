/// @file ReachBar.hpp
/// @brief Classe pour la jauge de progression avec valeur à atteindre.
/// @authors Jérémy Gaouette, Nikolas D'Amato

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "ProgressBar.hpp"

/// @class ReachBar
/// @brief Classe pour la jauge de progression avec valeur à atteindre.
class ReachBar : public ProgressBar {
    private:
        float reachValue; ///< Valeur à atteindre de la barre.
        SDL_Color failureColor; ///< Couleur de la barre avant la valeur à atteindre.
        SDL_Color successColor; ///< Couleur de la barre après la valeur à atteindre.

    public:
        /// @brief Constructeur d'une jauge e progression avec valeur à atteindre.
        /// @param position Position de la barre de progression.
        /// @param size Taille de la barre de progression.
        /// @param maxValue Valeur maximale de la barre de progression.
        /// @param currentValue Valeur actuelle de la barre de progression.
        /// @param backgroundColor Couleur de fond de la barre de progression.
        /// @param failureColor Couleur de la jauge avant la valeur à atteindre.
        /// @param successColor Couleur de la jauge après la valeur à atteindre.
        /// @param reachValue Valeur à atteindre de la jauge.
        ReachBar(Vector3d position, Vector3d size, float maxValue = 100, float currentValue = 0, float reachValue = 50, SDL_Color backgroundColor = COLOR_WHITE, SDL_Color failureColor = COLOR_RED,  SDL_Color successColor = COLOR_GREEN) : ProgressBar(position, size, maxValue, currentValue, backgroundColor) {
            this->reachValue = reachValue;
            this->failureColor = failureColor;
            this->successColor = successColor;
        }

        /// @brief Affichage de la jauge de progression avec valeur à atteindre.
        void draw() {
            ProgressBar::draw();

            // Affichage de la jauge de progression
            glBegin(GL_QUADS);
                if (this->currentValue >= this->reachValue) {
                    glColor4d(successColor.r, successColor.g, successColor.b, successColor.a);
                } else {
                    glColor4d(failureColor.r, failureColor.g, failureColor.b, failureColor.a);
                }
                glVertex3d(position.x + outlineWidth, position.y + outlineWidth, 0.0);
                glVertex3d(position.x + (size.x / (this->maxValue / this->currentValue) - outlineWidth),  position.y + outlineWidth, 0.0);
                glVertex3d(position.x + (size.x / (this->maxValue / this->currentValue) - outlineWidth), position.y + size.y - outlineWidth, 0.0);
                glVertex3d(position.x + outlineWidth, position.y + size.y - outlineWidth, 0.0);
            glEnd();
            
            // Affichage de la valeur à atteindre
            glLineWidth(2.0);
            glBegin(GL_LINES);
                glColor4d(0, 0, 0, 1);
                glVertex3d(position.x + (size.x / (this->maxValue / this->reachValue)), position.y + outlineWidth, 0.0);
                glVertex3d(position.x + (size.x / (this->maxValue / this->reachValue)), position.y + size.y - outlineWidth, 0.0);
            glEnd();
        }

        /// @brief Retourne si la valeur a été atteinte.
        /// @return Si la valeur a été atteinte.
        bool hasReached() {
            return currentValue >= reachValue;
        }

        /// @brief Définir une valeur à atteindre.
        /// @param reachValue valeur à atteindre.
        void setReachValue(float reachValue) {
            if (reachValue > maxValue) {
                this->reachValue = maxValue;
            } else if (reachValue < 0) {
                this->reachValue = 0;
            } else {
                this->reachValue = reachValue;
            }
        }
};