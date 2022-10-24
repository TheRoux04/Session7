#include "Event.hpp"
#include <map>
#include "Renderer.hpp"

using namespace std;


class Application {
private:

    map<unsigned int, Window*> windows;

public:
    Application() {
        SDL_Init(SDL_INIT_EVERYTHING);
    }
    ~Application() {
        for (auto it : windows) {
            delete it.second;
        }
        windows.clear();
        SDL_Quit();
        
    }
    void addWindow(Window* window) {

        windows[window->getId()] = window;
    }

    void start() {

        while (windows.size()) {
            while (Event::poll()) {
                switch(Event::getType()) {
                    
                    case SDL_WINDOWEVENT:

                        switch (Event::getWindowEventType())
                        {
                        case SDL_WINDOWEVENT_CLOSE:
                            delete windows[Event::getWindowId()];
                            windows.erase(Event::getWindowId());
                            break;
                        
                        default:
                            break;
                        }
                        break;
                }
            }
            for(auto it : windows) {
                it.second->clear();

                it.second->onRefresh();
            }
        }
        
    }

};