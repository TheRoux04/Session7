/// @file NewGame.hpp
/// @brief Scène pour lancer une Nouvelle Partie
/// @authors Gabriel Dufresne

#pragma once

#include "../elements/2d/TextBox.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../elements/2d/Label.hpp"
#include "../Matrix44d.hpp"
#include "Scene.hpp"
#define ON_BUTTON_CLICK 1

/// @class NewGame
/// @brief Scène pour lancer une Nouvelle Partie
class NewGame : public Scene {
private:
    Matrix44d matrix;
    TextButton *startButton;
    TextButton *returnButton;
    TextBox *text;
    Label *title;
public:

    /// @brief Chargement de la scène.
   void load() override {

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //resource
        ResourcesManager::addResource("font-big", new TTFont(DEFAULT_FONT, 48));

        //matrice de projection
        matrix.loadOrthographic(size.x, size.y);

        //label
        title = new Label({500, 20}, "Nouvelle partie ");
        elements2D.push_back(title);

        //bouton start
        startButton = new TextButton({480, 240}, {100, 50}, "Lancer la partie", DEFAULT_FONT, COLOR_WHITE, COLOR_DARK_GRAY);
        startButton->setEnabled(false);
        elements2D.push_back(startButton);

        //bouton retour
        returnButton = new TextButton({520, 400}, {100, 50}, "Retour", DEFAULT_FONT, COLOR_WHITE, COLOR_DARK_GRAY);
        returnButton->setEnabled(false);
        elements2D.push_back(returnButton);

        //textBox
        text = new TextBox({470, 100}, "nom de la sauvegarde");
        text->setText("nom de la partie");
        bindEvent(SDL_MOUSEBUTTONDOWN, text);
        bindEvent(SDL_KEYDOWN, text);
        elements2D.push_back(text);
    }

    /// @brief Déchargement de la scène.
    void unload() override{
        // Events
        clearEvents();

        // Drawables 2D
        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }

        //resources
        ResourcesManager::removeResource("font-big", true);
    }
    
    /// @brief Notification de la scène.
    void notification() override{

    }

     /// @brief Mise à jour de la scène.
    void handleUpdate(const double& deltaTime) override{

    }

    /// @brief Affichage de la scène.
    void handleDraw() override{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(matrix.elements);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        for (auto element: elements2D) {
            element->draw();
        }
    }
};