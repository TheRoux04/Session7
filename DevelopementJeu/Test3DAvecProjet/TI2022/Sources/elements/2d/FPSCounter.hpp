/// @file FPSCounter.hpp
/// @brief Compteur de FPS.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

#include "Label.hpp"
#include "../../Chrono.hpp"

/// @class FPSCounter
/// @brief Compteur de FPS.
class FPSCounter : public Drawable2d {
private:
    Label *label; ///< Label du compteur.
    Chrono chrono; ///< Chronomètre.
    int frames; ///< Nombre de frames depuis le dernier reset.

public:
    /// @brief Constructeur d'un compteur de FPS.
    /// @param position Position du compteur.
    /// @param font Nom de la police d'écriture.
    FPSCounter(Vector3d position = {}, const string &font = DEFAULT_FONT) {
        this->label = new Label(position, "FPS: 0", font, {255, 255, 255, 255});
        this->frames = 0;
        anchor = TOP_LEFT;
    }

    ~FPSCounter() {
        delete label;
    }

    /// @brief Met à jour le compteur de FPS.
    void update() {
        frames++;
        if (chrono.getDelta() >= 1) {
            label->setText("FPS: " + to_string(frames));
            chrono.reset();
            frames = 0;
        }
    }

    /// @brief Dessine le compteur de FPS.
    void draw() {
        label->draw();
    }

    void notification() {};

    void setAnchor(Anchor anchor) {
        this->anchor = anchor;
        label->setAnchor(anchor);
    }
};