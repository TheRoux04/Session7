/// @file QuickFixHoldButton.hpp
/// @brief Élément graphique 2d pour la réparation simple qui est de maintenir un bouton enfoncé.
/// @author Nikolas D'Amato

#pragma once

#include "Label.hpp"
#include "DefaultBar.hpp"
#include "Drawable2d.hpp"

/// @class QuickFixHoldButton
/// @brief Élément graphique 2d pour la réparation simple qui est de maintenir un bouton enfoncé.
class QuickFixHoldButton : public Drawable2d {
private:
    Label *label; ///< Label de l'élément.
    DefaultBar *bar; ///< Barre de progression.
    bool isFixed; ///< Si la réparation est terminée.
    Vector3d size; ///< Taille de l'élément.
    Vector3d position; ///< Position de l'élément.

public:
    /// @brief Création d'une instance de QuickFixHoldButton.
    /// @param position Position de l'élément.
    /// @param duration Durée de la réparation.
    QuickFixHoldButton(Vector3d position = {0, 0}, float duration = 100) {
        size = {320, 50};
        this->position = position;
        label = new Label({position.x + 10, position.y + 5}, "Garde E enfoncé pour réparer", "Side-Love.ttf", COLOR_BLACK);
        bar = new DefaultBar({position.x + 5, position.y + 35}, {size.x - 10, 10}, duration, 0, COLOR_WHITE, COLOR_BLUE);
        isFixed = false;
        anchor = TOP_LEFT;
    }

    ~QuickFixHoldButton() {
        delete label;
        delete bar;
    }

    /// @brief Met à jour le bouton.
    void update() {
        bar->addValue(1);
        if (bar->getValue() >= bar->getMaxValue()) {
            isFixed = true;
            label->setText("       Réparation terminée");
        }
    }

    /// @brief Dessine la réparation simple.
    void draw() {
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR);
        glBegin(GL_QUADS);
            glColor4d(0,1,4,1);
            glVertex3d(position.x, position.y, 0.0);
            glVertex3d(position.x + size.x,  position.y, 0.0);
            glVertex3d(position.x + size.x, position.y + size.y, 0.0);
            glVertex3d(position.x, position.y + size.y, 0.0);
        glEnd();
        label->draw();
        bar->draw();
    }

    /// @brief Notifie le bouton que la touche E est enfoncée.
    void notification() {
        if ((Event::getKey() == 'e' || Event::getKey() == 'E') && SDL_KEYDOWN && !isFixed) {
            update();
        }
    }

    /// @brief Donne si la reparation est terminée.
    bool getIsFixed() {
        return isFixed;
    }

    /// @brief Assigne une nouvelle position au bouton.
    /// @param position Nouvelle position.
    void setPosition(Vector3d position) {
        label->position = position;
        bar->position = (position + Vector3d(0, 50));
    }

    void setAnchor(Anchor anchor) {
        this->anchor = anchor;
        label->setAnchor(anchor);
        bar->setAnchor(anchor);
    }
};