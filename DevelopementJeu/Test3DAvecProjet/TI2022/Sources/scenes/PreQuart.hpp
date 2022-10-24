/// @file PreQuart.hpp
/// @brief Scène de message de pré quart.
/// @authors Marc-Antoine Gagnon

#pragma once

#include "../elements/2d/HintBox.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/FPSCounter.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../Matrix44d.hpp"
#include "Scene.hpp"
#include <string>

#define ON_BUTTON_CLICK 1

/// @class PreQuart
/// @brief Scène de pré quart qui contient tous les éléments graphiques.
class PreQuart : public Scene {
private:
    Matrix44d orthographic;

    Image *image;
    TextButton *Button;
    string title;
    string mio;

public:

    /// @brief Reçoit le titre et le texte à afficher dans la scène
    /// @param title 
    /// @param mio 
    PreQuart(string title, string mio) {
        this->title = title; //"Cai semaine 1"
        this->mio = mio; //"Bonjour à toi cher technicien du CAI, cette semaine on s'attend à une hausse\nde personnes a la bibliothèque qui feront leur travaux. Attend toi à devoir aider\nplus de personnes. On a aussi reçu une nouvelle imprimante mais elle nous fait\ndéfaut et devra surement être réparé. N'hésite pas a regarder un tutoriel en ligne\npour savoir comment la réparer.\n \nBonne chance et bonne journée, Philippe."
    }


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
        ResourcesManager::addResource("mio", new Texture("MioPhil.png"));

        // Image background mio
        image = new Image({0, 0}, {1920, 1080}, "mio");
        elements2D.push_back(image);
        
        // Titre mio
        Label *title = new Label({325, 350}, this->title, "font", DEFAULT_COLOR);
        elements2D.push_back(title);

        // Texte mio
        HintBox *hintbox = new HintBox({325, 430}, this->mio, "font", COLOR_MIO_TEXT, DEFAULT_BACKGROUND_COLOR);
        elements2D.push_back(hintbox);

        // Button
        Button = new TextButton({1710, 20}, {100, 50}, "Suivant", "font");
        Button->setAction(next);
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
        ResourcesManager::removeResource("mio", true);
    }

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            case ON_BUTTON_CLICK:
                // Redirect sur une autre scène
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
    static void next() {
        SDL_Event customEvent;
        customEvent.type = SDL_USEREVENT;
        customEvent.user.code = ON_BUTTON_CLICK;
        SDL_PushEvent(&customEvent);
    }

};
