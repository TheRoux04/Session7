///@file Terminal.hpp
///@brief Scène du jeu en ligne de commandes
///@authors Raphaël Sincerny, Ulric Richer

#pragma once

#include "Scene.hpp"
#include "../elements/2d/HintBox.hpp"
#include "../elements/2d/TextBox.hpp"
#include "../elements/2d/Button.hpp"
#include "../elements/2d/Timer.hpp"


///@class Terminal
///@brief Classe représentant la scène du jeu en ligne de commandes

class Terminal : public Scene {
private:
    HintBox *hintBoxInputs;
    HintBox *hintBoxObjectives;
    TextBox *textBox;
    Timer *timer;
    Button *button;



public:

///@brief Chargement de la scène.
    void load() override {
        ResourcesManager::addResource("font", new TTFont("decterm.ttf", 12));
        
        //HintBox des commandes entrées
        hintBoxInputs = new HintBox({0, 0}, "", "font", COLOR_GREEN, DEFAULT_BACKGROUND_COLOR);

        //HintBox des objectifs à accomplir
        hintBoxObjectives = new HintBox({0, 0}, "Objectifs", "font", COLOR_GREEN, DEFAULT_BACKGROUND_COLOR);

        //TextBox pour entrer une commande
        //textBox = new TextBox({0, 0}, )


    }

    ///@brief Déchargement de la scène.
    void unload() {

    }    

    ///@brief Notification de la scène.
    void notification() {

    }

    ///@brief Affichage de la scène.
    void handleDraw() override {

    }
};