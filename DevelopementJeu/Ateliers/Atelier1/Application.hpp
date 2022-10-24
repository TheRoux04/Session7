#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include "Window.hpp"
#include "SDLRenderer.hpp"
#include <vector>


using namespace std;

class Application
{
private:
    vector<Window*> allWindows;
public:
    Application(){
        SDL_Init(SDL_INIT_EVERYTHING);
    }
    ~Application(){
        SDL_Quit();
    }

    void addWindow(Window *window){
        allWindows.push_back(window);
    }

    void start(){
        allWindows.push_back(new SDLRenderer);
        bool isOpen = true;
        while (isOpen){
            //Gestion des  événements
            while (Event::poll()) {
                switch (Event::getType()){
                    case SDL_QUIT:
                        isOpen = false;
                        break;
                }
            }

            for (Window* window: allWindows){
                window->clear();
                window->refresh();
            }
        }

        for (Window* window: allWindows){
            delete window;
        }
    }

};

