#include "Application.hpp"
#include "SDLRenderer.hpp"

int main(int argc, char* argv[]){
    Application application;
    for (int i = 0; i < 1e3; i++) 
    application.addWindow(new SDLRenderer());
    
    application.start();

    return 0;
};