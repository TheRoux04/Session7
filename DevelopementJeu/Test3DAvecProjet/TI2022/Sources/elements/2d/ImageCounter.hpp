/// @file ImageCounter.hpp
/// @brief Classe pour les compteurs avec une image.
/// @authors Isabelle Provost

#pragma once

#include "Counter.hpp"

/// @class Counter
/// @brief Classe pour les compteurs avec une image.
class ImageCounter : public Counter {
private:
    Texture *image; ///< Image du compteur.
    Vector3d imageSize; ///< Taille de l'image.

public:
    /// @brief Constructeur d'un compteur avec une image.
    /// @param imageName Nom de l'image.
    /// @param position Position du compteur.
    /// @param imageSize Taille de l'image.
    /// @param fontName Police du texte.
    /// @param count Valeur initiale du compteur.
    /// @param color Couleur du texte.
    ImageCounter(string imageName, Vector3d position, Vector3d imageSize, string fontName = DEFAULT_FONT, int count = 0, SDL_Color color = COLOR_WHITE) : Counter(position, fontName, count, color) {
        this->imageSize = imageSize;
        this->image = ResourcesManager::getResource<Texture>(imageName);
        this->labCount = new Label({0, 0, 0}, " ", fontName, color);

        TTFont* font = ResourcesManager::getResource<TTFont>(fontName);
        SDL_Point textSize = font->getSize(to_string(count));
        labCount->setPosition({position.x + imageSize.x, position.y + (imageSize.y / 2) - (textSize.y / 2), position.z});
        labCount->setText(" : " + to_string(count));
    }

    /// @brief Destructeur du compteur avec une image.
    ~ImageCounter() {
        delete labCount;
    }

    /// @brief Dessine le compteur avec une image.
    void draw() {
        // Image
        Rectangle::drawTexture(position, imageSize, image, anchor);

        // Compteur
        labCount->draw();
    }
};