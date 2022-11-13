/// @file MainMenu.hpp
/// @brief Menu principal du jeu
/// @authors Louis-Félix Veillette

#pragma once

#include "../elements/2d/Image.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../elements/2d/Label.hpp"
#include "Scene.hpp"

/// @class MainMenu
/// @brief Scène du menu principal
class MainMenu : public Scene {
private:
    Image *imageCAI;
    Image *imageTechInfo;
    
    Label *labCAI;
    Label *labSousTitre;

    TextButton *btnJouer;
    TextButton *btnOptions;
    TextButton *btnQuitter;

public:

    void load() {

        ResourcesManager::addResource("imageCAI", new Texture("LogoCAI.png"));

        imageCAI = new Image({ 0, 0 }, { 300, 300 }, "imageCAI");
        elements2D.push_back(imageCAI);

        labCAI = new Label({300, 0}, "C.A,I");
        elements2D.push_back(labCAI);

        labSousTitre = new Label({ 300, 50 }, "Dernier maître du soutien informatique");
        elements2D.push_back(labSousTitre);

        btnJouer = new TextButton({ 300, 105 }, { 200, 50 }, "Jouer", DEFAULT_FONT);
        btnJouer->setAction(sauvegarde);
        btnJouer->setButtonColor({ 0, 149, 255, 255 });
        bindEvent(SDL_MOUSEBUTTONUP, btnJouer);
        elements2D.push_back(btnJouer);<

        btnOptions = new TextButton({ 300, 160 }, { 200, 50 }, "Options", DEFAULT_FONT);
        btnOptions->setAction(options);
        btnOptions->setButtonColor({ 0, 149, 255, 255 });
        bindEvent(SDL_MOUSEBUTTONUP, btnOptions);
        elements2D.push_back(btnOptions);

        btnQuitter = new TextButton({ 300, 215 }, { 200, 50 }, "Quitter", DEFAULT_FONT);
        btnQuitter->setAction(quitter);
        btnQuitter->setButtonColor({ 0, 149, 255, 255 });
        bindEvent(SDL_MOUSEBUTTONUP, btnQuitter);
        elements2D.push_back(btnQuitter);


    }

    void unload() {

    }

    void notification() {

    }

    void handleUpdate(const double& deltaTime) {

    }

    void handleDraw() {

    }

    static void sauvegarde() {
        
    }

    static void options() {

    }

    static void quitter() {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
    }
};
