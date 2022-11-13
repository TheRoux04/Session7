#include "Application.hpp"
#include "SDLRenderer.hpp"

int main(int argc, char* argv[]){
    Application application;
    application.addWindow(new SDLRenderer("A"));
    application.addWindow(new SDLRenderer("B"));
    
    application.start();

    return 0;
};