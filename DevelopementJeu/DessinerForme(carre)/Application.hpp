/// @file Application.hpp
/// @brief Applivation
/// @author Olivier Savoie (1908527\etu.cegep-lanaudiere.qc.ca)

#include "Event.hpp"
#include "GLContext.hpp"

using namespace std;

/// @class Application
/// @brief Classe permettant de gérer l'application
class Application {
private:
    static Application instance;
    GLContext glContext;

public:
    Application() {
        SDL_Init(SDL_INIT_EVERYTHING);
    }

    ~Application() {
        SDL_Quit();
    }

    static Application& getInstance() {
        return instance;
    }

    void start() {
        bool isUp = true;
        while (isUp) {
            //Gestionnaire des événements
            while (Event::poll()) {
                switch(Event::getType()) {
                    case SDL_QUIT:
                        isUp = false;
                        break;
                }
            }
            //Gestion des mise à jour
            glContext.clear();
            glContext.draw();   //Gestion de l'affichage
            glContext.refresh();
        }
        
    }

};

Application Application::instance;