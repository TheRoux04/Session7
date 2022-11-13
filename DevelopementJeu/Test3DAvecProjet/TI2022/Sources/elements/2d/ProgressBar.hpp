/// @file ProgressBar.hpp
/// @brief Classe abstraite pour les barres de progression.
/// @authors Nikolas D'Amato, Jérémy Gaouette

#pragma once

#include "../../Vector3d.hpp"
#include "Drawable2d.hpp"

/// @class ProgressBar
/// @brief Méthode abstraite pour les barres de progression.
class ProgressBar : public Drawable2d {
    protected:
        SDL_Color bgColor; ///< Couleur de fond de la jauge de progression.
        float maxValue; ///< Valeur maximale de la barre de progression.
        float currentValue; ///< Valeur actuelle de la barre de progression.
        float outlineWidth; ///< Largeur de la bordure de la barre de progression.
        Vector3d size; ///< Taille de la barre de progression.

    public:
        /// @brief Constructeur d'une barre de progression.
        /// @param position Position de la barre de progression.
        /// @param size Taille de la barre de progression.
        /// @param maxValue Valeur maximale de la barre de progression.
        /// @param currentValue Valeur actuelle de la barre de progression.
        /// @param backgroundColor Couleur de fond de la barre de progression.
        ProgressBar(Vector3d position, Vector3d size, float maxValue = 100, float currentValue = 0, SDL_Color backgroundColor = COLOR_WHITE) {
            outlineWidth = 1;
            this->position = position;
            this->maxValue = maxValue;
            setValue(currentValue);
            this->size = size;
            this->bgColor = backgroundColor;
        }

        /// @brief Méthode pour dessiner la barre de progression.
        virtual void draw()  {
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_COLOR);

            // Contour de la jauge de progression.
            glBegin(GL_QUADS);
                glColor4d(0,0,0,1);
                glVertex3d(position.x, position.y, 0.0);
                glVertex3d(position.x + size.x,  position.y, 0.0);
                glVertex3d(position.x + size.x, position.y + size.y, 0.0);
                glVertex3d(position.x, position.y + size.y, 0.0);
            glEnd();

            // Fond de la jauge de progression.
            glBegin(GL_QUADS);
                glColor4d(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
                glVertex3d(position.x + outlineWidth, position.y + outlineWidth, 0.0);
                glVertex3d(position.x + size.x - outlineWidth,  position.y + outlineWidth, 0.0);
                glVertex3d(position.x + size.x - outlineWidth, position.y + size.y - outlineWidth, 0.0);
                glVertex3d(position.x + outlineWidth, position.y + size.y - outlineWidth, 0.0);
            glEnd();
        }

        /// @brief Fonction qui notifie l'utilisateur
        void notification() {} 

        /// @brief Méthode pour définir la valeur actuelle de la barre de progression.
        /// @param value Valeur actuelle de la barre de progression.
        void setValue(float value) {
            if (value > this->maxValue) {
                this->currentValue = this->maxValue;
            } else if (value < 0) {
                this->currentValue = 0;
            } else {
                this->currentValue = value;
            }
        }

        /// @brief Méthode pour ajouter une valeur à la valeur actuelle de la barre de progression.
        /// @param value Valeur à ajouter à la valeur actuelle de la barre de progression.
        void addValue(float addValue) {
            setValue(this->currentValue + addValue);
        }

        /// @brief Méthode pour enlever une valeur à la valeur actuelle de la barre de progression.
        /// @param value Valeur à enlever à la valeur actuelle de la barre de progression.
        void removeValue(float removeValue) {
            setValue(this->currentValue - removeValue);
        }

        /// @brief Méthode pour obtenir la valeur actuelle de la barre de progression.
        float getValue() {
            return this->currentValue;
        }

        /// @brief Méthode pour obtenir la valeur maximale de la barre de progression.
        float getMaxValue() {
            return this->maxValue;
        }

        /// @brief Méthode pour définir la largeur du contour de la barre de progression.
        void setOutlineWidth(float width) {
            this->outlineWidth = width;
        }
};