/// @file GLContext.hpp
/// @brief Moteur de rendu OpenGL.
/// @author Patrick Singcaster <singcaster@clogik.io>

#pragma once

#include "ResourcesManager.hpp"
#include "TTFont.hpp"
#include "Texture.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Matrix44d.hpp"
#include "Texture.hpp"
#include "Vector3d.hpp"

/// @class GLContext
/// @brief Moteur de rendu OpenGL.
class GLContext {
private:
    SDL_Window *sdlWindow;     ///< Fenêtre
    SDL_GLContext glContext;   ///< Moteur de rendu OpenGL

public:
    /// @param title Titre de la fenêtre
    /// @param x Position de la fenêtre sur l'axe des x
    /// @param y Position de la fenêtre sur l'axe des y
    /// @param width Largeur de la fenêtre
    /// @param height Hauteur de la fenêtre
    /// @param windowFlags Options de la fenêtre
    GLContext(const char *title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT, unsigned int windowFlags = 0) {
        sdlWindow = SDL_CreateWindow(title, x, y, width, height, windowFlags | SDL_WINDOW_OPENGL);
        glContext = SDL_GL_CreateContext(sdlWindow);

        SDL_GL_SetSwapInterval(0);
    }

    ~GLContext() {
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(sdlWindow);
    }

    /// @brief Supprime le contenu de la fenêtre.
    void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /// @brief Obtention de la taille de la fenêtre.
    /// @return Taille de la fenêtre.
    SDL_Point getSize() {
        SDL_Point windowSize;
        SDL_GetWindowSize(sdlWindow, &windowSize.x, &windowSize.y);
        return windowSize;
    }

    /// @brief Présentation du contenu de la fenêtre.
    void refresh() {
        SDL_GL_SwapWindow(sdlWindow);
    }
};
