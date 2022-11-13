/// @file Application.hpp
/// @brief Classe principale de l'application.
/// @authors Raphael Rail <@answr42Hub>, Isabelle Provost <@IsabelleProvost>, Jérémie Perreault <@JeremiePerreault>, Eugène-Emmanuel Dubuc <@EugeneEmmanuelDubuc>, Olivier Savoie <@OlivierSavoie>, Gabriel Dufresne <@GabrielDufresne>, Raphael Sincerny <@RaphaelSincerny>

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <stack>
#include <string>

#include "Chrono.hpp"
#include "Event.hpp"
#include "GLContext.hpp"
#include "ResourcesManager.hpp"
#include "elements/2d/FPSCounter.hpp"
#include "Constants.hpp"
#include "scenes/Scene.hpp"

/// @class Application
/// @brief Gestion de l'application.
class Application {
private:
    stack<Scene *> scenes;          ///< Scènes actives.
    map<string, Scene *> mapScenes; ///< Collection de scènes.
    GLContext *glContext;           ///< Contexte OpenGL.
    FPSCounter *fpsCounter;         ///< Compteur de FPS.

    static Application instance;    ///< Instance de l'application.

public:
    Application() {
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();

        glContext = new GLContext();
    }

    ~Application() {
        delete glContext;

        ResourcesManager::free();

        for (auto mapScene: mapScenes) {
            delete mapScene.second;
        }

        while (!scenes.empty()) {
            scenes.pop();
        }

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    /// @brief Démarrage de l'application.
    void start() {
        bool isUp = true;
        while (isUp) {
            while (Event::poll()) {
                unsigned int eventType = Event::getType();
                switch (eventType) {
                    case SDL_QUIT:
                        isUp = false;
                        break;

                    default:
                        if (!scenes.empty()) {
                            scenes.top()->handleEvent(eventType);
                        }
                }
            }

            glContext->clear();
            scenes.top()->handleUpdate(0.001);   // TODO: Passé un vrai delta temps comme argument.
            scenes.top()->handleDraw();
            glContext->refresh();
        }
    }

    /// @brief Obtention de l'instance de l'application.
    /// @return Instance de l'application.
    static Application &getInstance() {
        return instance;
    }

    /// @brief Swap de la scène courante.
    /// @param scene Nom de la scène à afficher.
    void swapScene(const string &name) {
        if (!scenes.empty()) {
            popScene();
        }
        pushScene(mapScenes[name]);
    }

    /// @brief Pop de la scène courante.
    void popScene() {
        scenes.top()->unload();
        scenes.pop();
    }

    /// @brief Push d'une scène.
    /// @param scene Scène à afficher.
    void pushScene(Scene *scene) {
        scene->load();
        scenes.push(scene);
    }

    /// @brief Ajout d'une scène.
    /// @param scene Scène à ajouter.
    void addScene(string name, Scene *scene) {
        scene->setSize(glContext->getSize());
        mapScenes[name] = scene;
    }

    /// @brief Suppression d'une scène.
    /// @param scene Scène à supprimer.
    void removeScene(string name) {
        delete mapScenes[name];
        mapScenes.erase(name);
    }
};

Application Application::instance;