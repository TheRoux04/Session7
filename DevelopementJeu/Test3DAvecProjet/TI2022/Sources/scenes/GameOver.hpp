/// @file GameOver.hpp
/// @brief Scène de fin de partie.
/// @authors Marc-Antoine Gagnon

#pragma once

#include "../elements/2d/Image.hpp"
#include "../elements/2d/FPSCounter.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../Matrix44d.hpp"
#include "Scene.hpp"

#define ON_BUTTON_CLICK 1

/// @class GameOver
/// @brief Scène de Game over
class GameOver : public Scene {
private:
    Matrix44d orthographic;

    Image *image;
    TextButton *Button;

public:
    /// @brief Chargement de la scène.
    void load() override {
        /// TODO: Activation des interrupteurs nécessaires.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        /// TODO: Chargement des matrices de projection nécessaires.
        orthographic.loadOrthographic(size.x, size.y);

        // Resources
        ResourcesManager::addResource("font", new TTFont("Times New Roman.ttf", 48));
        ResourcesManager::addResource("gameOver", new Texture("GameOver.png"));

        // Image background game over avec du feu partout WOW
        image = new Image({0, 0}, {1920, 1080}, "gameOver");
        elements2D.push_back(image);

        // Button
        Button = new TextButton({785, 580}, {350, 50}, "Retour au menu", "font");
        Button->setAction(menu);
        Button->setButtonColor({0, 149, 255, 255});
        bindEvent(SDL_MOUSEBUTTONUP, Button);
        elements2D.push_back(Button);

        bindEvent(SDL_USEREVENT, this);
    }

    /// @brief Déchargement de la scène
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
        ResourcesManager::removeResource("font", true);
        ResourcesManager::removeResource("gameOver", true);
    }

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            case ON_BUTTON_CLICK:
                // Redirect sur une autre scène
                // Menu principal
                break;
        }
    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {}

    /// @brief Affichage de la scène.
    void handleDraw() override {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(orthographic.elements);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (auto element: elements2D) {
            element->draw();
        }
    }

    /// @brief Définit l'event du bouton suivant
    static void menu() {
        SDL_Event customEvent;
        customEvent.type = SDL_USEREVENT;
        customEvent.user.code = ON_BUTTON_CLICK;
        SDL_PushEvent(&customEvent);
    }

};
