/// @file Save.hpp
/// @brief Scène de sauvegarde.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

#include "../Matrix44d.hpp"
#include "../SaveFile.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/SaveSlot.hpp"
#include "../elements/2d/TextButton.hpp"
#include "PreQuart.hpp"
#include "Scene.hpp"

#define ON_SAVE_ONE_CLICK 1
#define ON_SAVE_TWO_CLICK 2
#define ON_SAVE_THREE_CLICK 3
#define ON_RETURN_CLICK 4
#define ON_LAUNCH_CLICK 5
#define ON_DELETE_CLICK 6

/// @class Save
/// @brief Scène de sauvegarde.
class Save : public Scene {
private:
    Matrix44d orthographic;

    TextButton *startButton;
    TextButton *deleteButton;

    SaveSlot *saveSlotOne;
    SaveSlot *saveSlotTwo;
    SaveSlot *saveSlotThree;

    SaveFile *saveFileOne;
    SaveFile *saveFileTwo;
    SaveFile *saveFileThree;

    unsigned int saveSelected;

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
        ResourcesManager::addResource("font-big", new TTFont(DEFAULT_FONT, 48));

        // Labels
        Label *title = new Label({25, 25}, "Démarrer une sauvegarde");
        elements2D.push_back(title);

        // Boutons
        startButton = new TextButton({25, 525}, {950, 50}, "Lancer", DEFAULT_FONT, COLOR_WHITE, COLOR_DARK_GRAY);
        startButton->setEnabled(false);
        startButton->setAction([]() {
            Event::pushCustomEvent(ON_LAUNCH_CLICK);
        });
        bindEvent(SDL_MOUSEBUTTONUP, startButton);
        elements2D.push_back(startButton);

        deleteButton = new TextButton({25, 600}, {450, 50}, "Supprimer", DEFAULT_FONT, COLOR_WHITE, COLOR_DARK_GRAY);
        deleteButton->setEnabled(false);
        bindEvent(SDL_MOUSEBUTTONUP, deleteButton);
        elements2D.push_back(deleteButton);

        TextButton *backButton = new TextButton({525, 600}, {450, 50}, "Retour", DEFAULT_FONT, COLOR_WHITE, COLOR_PRIMARY);
        bindEvent(SDL_MOUSEBUTTONUP, backButton);
        elements2D.push_back(backButton);

        // Sauvegardes
        saveSelected = -1;

        saveFileOne = new SaveFile("save1");     // temporary
        saveFileTwo = new SaveFile("save2");     // temporary
        saveFileThree = new SaveFile("save3");   // temporary

        saveSlotOne = new SaveSlot({25, 75}, {300, 400}, *saveFileOne);
        saveSlotOne->setAction([]() {
            Event::pushCustomEvent(ON_SAVE_ONE_CLICK);
        });
        bindEvent(SDL_MOUSEBUTTONUP, saveSlotOne);
        elements2D.push_back(saveSlotOne);

        saveSlotTwo = new SaveSlot({350, 75}, {300, 400}, *saveFileTwo);
        saveSlotTwo->setAction([]() {
            Event::pushCustomEvent(ON_SAVE_TWO_CLICK);
        });
        bindEvent(SDL_MOUSEBUTTONUP, saveSlotTwo);
        elements2D.push_back(saveSlotTwo);

        saveSlotThree = new SaveSlot({675, 75}, {300, 400}, *saveFileThree);
        saveSlotThree->setAction([]() {
            Event::pushCustomEvent(ON_SAVE_THREE_CLICK);
        });
        bindEvent(SDL_MOUSEBUTTONUP, saveSlotThree);
        elements2D.push_back(saveSlotThree);

        bindEvent(SDL_USEREVENT, this);
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
            case ON_SAVE_ONE_CLICK:
                enableSave(0);
                break;
            case ON_SAVE_TWO_CLICK:
                enableSave(1);
                break;
            case ON_SAVE_THREE_CLICK:
                enableSave(2);
                break;
            case ON_LAUNCH_CLICK:
                if (saveSelected != -1) {
                    // TODO: Fix segfault
                    Application::getInstance().swapScene("PreQuart");
                }
        }
    }

    void enableSave(unsigned int save) {
        saveSelected = save;

        switch (save) {
            case 0:
                saveSlotOne->setButtonColor(COLOR_GREEN);
                saveSlotTwo->setButtonColor(COLOR_DARK_GRAY);
                saveSlotThree->setButtonColor(COLOR_DARK_GRAY);
                break;
            case 1:
                saveSlotOne->setButtonColor(COLOR_DARK_GRAY);
                saveSlotTwo->setButtonColor(COLOR_GREEN);
                saveSlotThree->setButtonColor(COLOR_DARK_GRAY);
                break;
            case 2:
                saveSlotOne->setButtonColor(COLOR_DARK_GRAY);
                saveSlotTwo->setButtonColor(COLOR_DARK_GRAY);
                saveSlotThree->setButtonColor(COLOR_GREEN);
                break;
            default:
                disableSave();
                return;
        }

        startButton->setEnabled(true);
        startButton->setButtonColor(COLOR_PRIMARY);

        deleteButton->setEnabled(true);
        deleteButton->setButtonColor(COLOR_PRIMARY);
    }

    void disableSave() {
        saveSelected = -1;

        startButton->setEnabled(false);
        startButton->setButtonColor(COLOR_DARK_GRAY);

        deleteButton->setEnabled(false);
        deleteButton->setButtonColor(COLOR_DARK_GRAY);
    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
    }

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
};
