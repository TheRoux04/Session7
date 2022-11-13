/// @file Test.hpp
/// @brief Scène du jeu "Éviter des interventions".
/// @authors Isabelle Provost

#pragma once

#include <iostream>

#include "../elements/2d/Label.hpp"
#include "../elements/2d/Timer.hpp"
#include "Scene.hpp"

/// @class Escape
/// @brief Scène du jeu "Éviter des interventions".
class Escape : public Scene {
private:
    Timer *timer; ///< Temps imparti pour s'enfuir
    Label *timerLabel; ///< Étiquette du temps

public:
    /// @brief Chargement de la scène.
    void load() override {
        // Resources
        ResourcesManager::addResource("font-big", new TTFont("Side-Love.ttf", 48));

        // Taille de l'écran
        SDL_DisplayMode displayMode; ///< Mode d'affichage de l'écran
        int w, h; ///< Largeur et hauteur de l'écran
        w = displayMode.w;
        h = displayMode.h;

        // Timer
        timer = new Timer(180);
        timerLabel = new Label({0, h / 5}, "Timer:" + Timer::format(timer->getRemainingTime()));
        elements2D.push_back(timerLabel);
    }

    void unload() {
        // Events
        clearEvents();

        // Drawables 2D
        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }

        // Resources
        ResourcesManager::removeResource("font-big", true);
    }

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            /// TODO: À voir.
        }
    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
        timerLabel->setText("Timer: " + Timer::format(timer->getRemainingTime()));
    }

    /// @brief Affichage de la scène.
    void handleDraw() override {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        /// TODO: Le rectangle gris en haut.
        
        for (auto element: elements2D) {
            element->draw();
        }
    }
};
