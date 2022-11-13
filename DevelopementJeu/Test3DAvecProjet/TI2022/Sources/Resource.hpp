/// @file Resource.hpp
/// @brief Les ressources (TTFont et Texture).
/// @author Louis-Félix Veillette <2038026@etu.cegep-lanaudiere.qc.ca>

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

class Resource {

public:
    virtual ~Resource() {};
    /// @brief Rend la classe virtuelle pure.
    virtual void inherit() = 0;
};
