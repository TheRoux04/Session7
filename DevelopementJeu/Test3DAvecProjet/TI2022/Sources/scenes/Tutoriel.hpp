/// @file Tutoriel.hpp
/// @brief Scène de message de tutoriel.
/// @authors Marc-Antoine Gagnon

#pragma once

#include "../elements/2d/HintBox.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/FPSCounter.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../Matrix44d.hpp"
#include "Scene.hpp"

#define ON_BUTTON_CLICK 1

/// @class PreQuart
/// @brief Scène de Tutoriel du CAI simulator
class Tutoriel : public Scene {
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
        ResourcesManager::addResource("font-small", new TTFont("Times New Roman.ttf", 40));
        ResourcesManager::addResource("mio", new Texture("MioPhil.png"));

        // Image background mio
        image = new Image({0, 0}, {1920, 1080}, "mio");
        elements2D.push_back(image);
        
        // Titre mio
        Label *title = new Label({325, 350}, "Introduction au CAI", "font",  DEFAULT_COLOR);
        elements2D.push_back(title);

        // Texte mio
        HintBox *hintbox = new HintBox({325, 420}, "Bonjour à toi nouveau technicien officiel du CAI. Comme tu le sais, tous les techniciens ont\ndisparus mystérieusement alors les élèves de la technique informatique doivent prendre la\nrelève avec le CAI. Du devras donc faire 15 quarts de bénévolat au cours de la session\n(1 par semaine) dans la bibliothèque.\n \nPendant tes quarts, tu devras aider les personnes dans le besoin et réparer les machines\nendommagées (imprimantes, router, poste de travail, etc.) L'administration compte\nsur nous et nous accorde un budget de 5$ pour mener à bien cette mission, mais si vous\nne faites pas assez bien votre travail, elle n'hésitera pas à vous remplacer par les SIM.\n \nMoi et la Gopher comptons sur toi.\n \nBonne chance et bonne journée, Philippe.", "font-small", COLOR_MIO_TEXT, DEFAULT_BACKGROUND_COLOR);
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
