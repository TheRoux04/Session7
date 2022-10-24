#include <SDL2/SDL.h>

using namespace std;

class Event
{
private:
    static SDL_Event sdlEvent;
public:
    static int poll(){
        return SDL_PollEvent(&sdlEvent);
    }

    static unsigned int getType(){
        return sdlEvent.type;
    }
};

SDL_Event Event::sdlEvent;