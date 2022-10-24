/// @file Counter.hpp
/// @brief Classe pour les compteurs.
/// @authors Isabelle Provost

#pragma once

#include "Label.hpp"
#include <string> 

using namespace std;

/// @class Counter
/// @brief Abstraction d'un compteur.
class Counter : public Drawable2d {
protected:
    Label *labCount; ///< Étiquette du compteur.
    int count; ///< Compteur.

    /// @brief Constructeur virtuel d'un compteur.
    /// @param position Position du compteur.
    /// @param fontName Police du texte.
    /// @param count Valeur initiale du compteur.
    /// @param color Couleur du texte.
    Counter(Vector3d position, string fontName = DEFAULT_FONT, int count = 0, SDL_Color color = COLOR_WHITE) {
        this->position = position;
        this->count = count;
        anchor = TOP_LEFT;
    }

    /// @brief Destructeur virtuel du compteur.
    virtual ~Counter() {}

public:
    /// @brief Augmente le compteur.
    /// @param nb Points à ajouter au compteur.
    void increase(int nb) {
        if (nb > 0) {
            setCount(count + nb);
        }
    }

    /// @brief Baisse le compteur.
    /// @param nb Points à retirer du compteur.
    void decrease(int nb) {
        if (nb > 0) {
            setCount(count - nb);
        }
    }

    /// @brief Met le compteur à une valeur.
    /// @param count Nouvelle valeur du compteur.
    void setCount(int count) {
        this->count = count;
        labCount->setText(" : " + to_string(count));
    }

    /// @brief Retourne la valeur du compteur.
    /// @return Valeur du compteur.
    int getCount() {
        return count;
    }

    /// @brief Dessine le compteur.
    virtual void draw() = 0;

    /// @brief Fonction qui notifie l'observateur.
    void notification() {}

    void setAnchor(Anchor anchor) {
        this->anchor = anchor;
        labCount->setAnchor(anchor);
    }
};