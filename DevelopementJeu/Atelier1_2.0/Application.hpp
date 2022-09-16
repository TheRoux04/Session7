/// @file Application.hpp
/// @brief Application
/// @author Olivier Savoie (1908527\etu.cegep-lanaudiere.qc.ca)

#pragma once
#include "Window.hpp"
#include "Event.hpp"
#include <map>

using namespace std;

/// @class Application
/// @brief Classe permettant de gérer l'application
class Application
{
private:
    map<unsigned int, Window*> windows; ///< Fenêtres de l'application

public:
    Application(){
        SDL_Init(SDL_INIT_EVERYTHING);
    }
    ~Application(){
        for (auto it : windows)
            delete it.second;
        windows.clear();

        SDL_Quit();
    }

    void addWindow(Window* window){
        windows[window->getId()] = window;
    }

    void start(){
        while (windows.size()){
            //Gestion des  événements
            while (Event::poll()) {
                switch (Event::getType()){
                case SDL_WINDOWEVENT:
                    switch (Event::getWindowEventType()){
                        case SDL_WINDOWEVENT_CLOSE:
                            delete windows[Event::getWindowId()];
                            windows.erase(Event::getWindowId());
                            break;
                    }
                    break;
                }
            }

            //Gestionnaire de mises à jour

            for (auto it : windows){
                it.second->clear();
                //Gestionnaire de l'affichage
                it.second->refresh();
            }

            
        }
    }

};

