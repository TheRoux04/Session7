/// @file main.cpp
/// @brief Fichier principal.

#include "Application.hpp"
#include "scenes/Save.hpp"
#include "scenes/Cours.hpp"
#include "scenes/Test.hpp"
#include "scenes/PreQuart.hpp"
#include "scenes/NewGame.hpp"

int main(int argc, char *argv[]) {
    Application::getInstance().addScene("Cours", new Cours());
    Application::getInstance().addScene("Save", new Save());
    Application::getInstance().addScene("Test", new Test());
    Application::getInstance().addScene("PreQuart", new PreQuart("", "")); // TODO: Constructeur par défaut?
    Application::getInstance().addScene("NewGame", new NewGame());

    Application::getInstance().swapScene("Cours");
    Application::getInstance().start();

    return 0;
}
