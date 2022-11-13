/// @file TextCounter.hpp
/// @brief Classe pour les compteurs avec un texte.
/// @authors Isabelle Provost

#pragma once

#include "Counter.hpp"

/// @class Counter
/// @brief Classe pour les compteurs avec un texte.
class TextCounter : public Counter {
private:
    Label *labText; ///< Étiquette du texte du compteur.

public:
    /// @brief Constructeur d'un compteur avec un texte.
    /// @param text Texte.
    /// @param position Position du compteur.
    /// @param fontName Police du texte.
    /// @param count Valeur initiale du compteur.
    /// @param color Couleur du texte.
    TextCounter(string text, Vector3d position, string fontName = DEFAULT_FONT, int count = 0, SDL_Color color = COLOR_WHITE) : Counter(position, fontName, count, color) {
        TTFont* font = ResourcesManager::getResource<TTFont>(fontName);
        SDL_Point textSize = font->getSize(text);
        this->labText = new Label({position.x, position.y, position.z}, text, fontName, color);
        this->labCount = new Label({position.x + textSize.x, position.y, position.z}, " ", fontName, color);

        labCount->setText(" : " + to_string(count));
    }

    /// @brief Destructeur du compteur avec un texte.
    ~TextCounter() {
        delete labCount;
        delete labText;
    }

    /// @brief Dessine le compteur avec un texte.
    void draw() {
        // Texte
        labText->draw();

        // Compteur
        labCount->draw();
    }

    void setAnchor(Anchor anchor) {
        Counter::setAnchor(anchor);
        labCount->setAnchor(anchor);
    }
};