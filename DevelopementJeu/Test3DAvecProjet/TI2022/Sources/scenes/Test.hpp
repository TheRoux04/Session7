/// @file Test.hpp
/// @brief Scène de test.
/// @authors Patrick Singcaster, Jean-Philippe Miguel-Gagnon

#pragma once

#include <iostream>

#include "../elements/2d/CheckBox.hpp"
#include "../elements/2d/DefaultBar.hpp"
#include "../elements/2d/FPSCounter.hpp"
#include "../elements/2d/HintBox.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/ImageButton.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/ReachBar.hpp"
#include "../elements/2d/TextBox.hpp"
#include "../elements/2d/TextButton.hpp"
#include "../elements/2d/ImageCounter.hpp"
#include "../elements/2d/TextCounter.hpp"
#include "../elements/2d/Timer.hpp"
#include "Scene.hpp"

// Types d'événement personnalisé
#define ON_HIT_BUTTON_CLICK 1
#define ON_HIT_CHECKBOX_CLICK 2
#define STOP_TIMER_BUTTON_CLICK 3
#define RESUME_TIMER_BUTTON_CLICK 4
#define RESET_TIMER_BUTTON_CLICK 5

/// @class Test
/// @brief Scène de test qui contient tous les éléments graphiques.
class Test : public Scene {
private:
    Matrix44d orthographic;

    TextButton *hitButton;
    ReachBar *lifeBar;
    CheckBox *toggleButton;
    Image *image;
    Label *health;
    TextBox *textBoxAmount;
    Timer *timer;
    Label *timerLabel;
    ImageCounter *imgCounter;
    TextCounter *txtCounter;

public:
    /// @brief Chargement de la scène.
    void load() override {
        /// TODO: Activation des interrupteurs nécessaires.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        /// TODO: Chargement des matrices de projection nécessaires.
        orthographic.loadOrthographic(size.x, size.y);

        // TODO: Ajouter tous les éléments qu'on a créer

        // Resources
        ResourcesManager::addResource("font-big", new TTFont("Side-Love.ttf", 48));
        ResourcesManager::addResource("gopher", new Texture("gopher.png"));

        // ProgressBar
        lifeBar = new ReachBar({25, 120}, {175, 20}, 100, 100, 25);
        elements2D.push_back(lifeBar);

        // Button
        hitButton = new TextButton({25, 175}, {100, 50}, "Hit me!");
        hitButton->setAction(hit);
        hitButton->setButtonColor(COLOR_PRIMARY);
        bindEvent(SDL_MOUSEBUTTONUP, hitButton);
        elements2D.push_back(hitButton);

        // Labels
        health = new Label({25, 100}, "Health: ");
        elements2D.push_back(health);

        Label *title = new Label({25, 25}, "Test Scene Please Ignore", "font-big");
        elements2D.push_back(title);

        Label *toggleLabel = new Label({150, 150}, "Damage?");
        elements2D.push_back(toggleLabel);

        Label *amountLabel = new Label({25, 250}, "Amount");
        elements2D.push_back(amountLabel);

        // Timer avec boutton pour contrôler
        timer = new Timer(15);
        timerLabel = new Label({900, 50}, "Timer:" + Timer::format(timer->getRemainingTime()));
        elements2D.push_back(timerLabel);

        TextButton* stopTimerButton = new TextButton({790, 100}, {100, 50}, "Stop");
        stopTimerButton->setAction(stopTimer);
        bindEvent(SDL_MOUSEBUTTONUP, stopTimerButton);
        elements2D.push_back(stopTimerButton);

        TextButton* resumeTimerButton = new TextButton({900, 100}, {100, 50}, "Resume");
        resumeTimerButton->setAction(resumeTimer);
        bindEvent(SDL_MOUSEBUTTONUP, resumeTimerButton);
        elements2D.push_back(resumeTimerButton);

        TextButton* resetTimerButton = new TextButton({1020, 100}, {100, 50}, "Reset");
        resetTimerButton->setAction(resetTimer);
        bindEvent(SDL_MOUSEBUTTONUP, resetTimerButton);
        elements2D.push_back(resetTimerButton);

        // CheckBox
        toggleButton = new CheckBox({150, 175}, {50, 50}, true);
        toggleButton->setAction(hitCheck);
        bindEvent(SDL_MOUSEBUTTONDOWN, toggleButton);
        elements2D.push_back(toggleButton);

        // Image
        image = new Image({150, 50}, {50, 50}, "gopher");
        elements2D.push_back(image);

        // TextBox
        textBoxAmount = new TextBox({25, 275}, "1");
        bindEvent(SDL_MOUSEBUTTONDOWN, textBoxAmount);
        bindEvent(SDL_KEYDOWN, textBoxAmount);
        elements2D.push_back(textBoxAmount);

        bindEvent(SDL_USEREVENT, this);

        // Counters
        imgCounter = new ImageCounter("missing", {500, 500, 0}, {50, 50, 0});
        elements2D.push_back(imgCounter);
        txtCounter = new TextCounter("Compteur", {625, 512, 0});
        elements2D.push_back(txtCounter);
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
        ResourcesManager::removeResource("gopher", true);
    }

    /// @brief Notification de la scène.
    void notification() {
        switch (Event::getCustomCode()) {
            case ON_HIT_BUTTON_CLICK:
                if (lifeBar->getValue()) {
                    const string input = textBoxAmount->getText();
                    try {
                        int amount = stoi(input);
                        lifeBar->removeValue(amount);
                        health->setText("Health: " + (lifeBar->getValue() ? to_string((int) lifeBar->getValue()) : "Dead"));
                    }
                    catch (...) {
                        textBoxAmount->setText("Bad amount!");
                    }
                }
                // Monte les compteurs
                imgCounter->increase(1);
                txtCounter->increase(1);
                break;

            case ON_HIT_CHECKBOX_CLICK:
                if (toggleButton->isChecked()) {
                    hitButton->setButtonColor(COLOR_PRIMARY);
                    hitButton->setText("Hit me!");
                    hitButton->setEnabled(true);
                }
                else {
                    hitButton->setButtonColor(COLOR_DARK_GRAY);
                    hitButton->setText("Disabled");
                    hitButton->setEnabled(false);
                }
                // Descend les compteurs
                imgCounter->decrease(1);
                txtCounter->decrease(1);
                break;

            case STOP_TIMER_BUTTON_CLICK:
                timer->stop();
                break;

            case RESUME_TIMER_BUTTON_CLICK:
                timer->resume();
                break;

            case RESET_TIMER_BUTTON_CLICK:
                timer->reset();
                break;
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
        glMultMatrixd(orthographic.elements);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        for (auto element: elements2D) {
            element->draw();
        }
    }

    static void hit() {
        Event::pushCustomEvent(ON_HIT_BUTTON_CLICK);
    }

    static void hitCheck() {
        Event::pushCustomEvent(ON_HIT_CHECKBOX_CLICK);
    }

    static void stopTimer() {
        Event::pushCustomEvent(STOP_TIMER_BUTTON_CLICK);
    }

    static void resumeTimer() {
        Event::pushCustomEvent(RESUME_TIMER_BUTTON_CLICK);
    }

    static void resetTimer() {
        Event::pushCustomEvent(RESET_TIMER_BUTTON_CLICK);
    }
};
