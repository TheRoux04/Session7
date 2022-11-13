/// @file Application.hpp
/// @brief Classe principale de l'application.
/// @authors Eugène-Emmanuël Dubuc, Gabriel Daoust, Jérémie Perreault

#pragma once

#include <SDL2/SDL_opengl.h>

#include "../../Rectangle.hpp"
#include "../../ResourcesManager.hpp"
#include "../../Texture.hpp"
#include "../../Vector3d.hpp"
#include "Drawable2d.hpp"

/// @brief Classe image
class Image : public Drawable2d {
private:
    Texture *texture;     ///< Texture de l'image
    Vector3d size;        ///< Taille de l'image

public:
    /// @brief Constructeur de l'image
    /// @param texture Texture de l'image
    /// @param position Position de l'image
    Image(Vector3d position, Vector3d size, const string &textureName) {
        texture = ResourcesManager::getResource<Texture>(textureName);
        this->position = position;
        this->size = size;
        anchor = TOP_LEFT;
    }

    /// @brief Destructeur
    ~Image() {
    }

    /// @brief Dessiner l'image
    void draw() override {
        Rectangle::drawTexture(position, size, texture, anchor);
    }

    /// @brief Notification
    void notification() override {
    }
};