/// @file Rectangle.hpp
/// @brief Classe pour dessiner des rectangles.
/// @author Jean-Philippe Miguel-Gagnon, Isabelle Provost

#pragma once

#include "Texture.hpp"
#include "Vector3d.hpp"

enum Anchor {
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_CENTER,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,
};

/// @class Rectangle
/// @brief Classe pour dessiner des rectangles.
class Rectangle {
private:
    /// @brief Dessine un rectangle.
    /// @param position Position du rectangle.
    /// @param size Taille du rectangle.
    /// @param anchor Ancre de la position, par défaut en haut à gauche.
    static void draw(Vector3d position, Vector3d size, Anchor anchor = TOP_LEFT) {
        switch (anchor) {
            case TOP_LEFT:
                break;
            case TOP_CENTER:
                position.x -= size.x / 2;
                break;
            case TOP_RIGHT:
                position.x -= size.x;
                break;
            case MIDDLE_LEFT:
                position.y -= size.y / 2;
                break;
            case MIDDLE_CENTER:
                position.x -= size.x / 2;
                position.y -= size.y / 2;
                break;
            case MIDDLE_RIGHT:
                position.x -= size.x;
                position.y -= size.y / 2;
                break;
            case BOTTOM_LEFT:
                position.y -= size.y;
                break;
            case BOTTOM_CENTER:
                position.x -= size.x / 2;
                position.y -= size.y;
                break;
            case BOTTOM_RIGHT:
                position.x -= size.x;
                position.y -= size.y;
                break;
        }

        glBegin(GL_QUADS);
            glTexCoord2d(0, 0); glVertex2d(position.x, position.y);
            glTexCoord2d(1, 0); glVertex2d(position.x + size.x, position.y);
            glTexCoord2d(1, 1); glVertex2d(position.x + size.x, position.y + size.y);
            glTexCoord2d(0, 1); glVertex2d(position.x, position.y + size.y);
        glEnd();
    }

public:
    /// @brief Dessine un rectangle avec une texture.
    /// @param position Position du rectangle.
    /// @param size Taille du rectangle.
    /// @param texture Texture du rectangle.
    /// @param anchor Ancre de la position, par défaut en haut à gauche.
    static void drawTexture(Vector3d position, Vector3d size, Texture *texture, Anchor anchor = TOP_LEFT) {
        glColor4d(1, 1, 1, 1);
        glDisable(GL_COLOR);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture->getId());
        draw(position, size, anchor);
    }

    /// @brief Dessine un rectangle avec une couleur.
    /// @param position Position du rectangle.
    /// @param size Taille du rectangle.
    /// @param color Couleur du rectangle, par défaut blanc.
    /// @param anchor Ancre de la position, par défaut en haut à gauche.
    static void drawColor(Vector3d position, Vector3d size, SDL_Color color = COLOR_WHITE, Anchor anchor = TOP_LEFT) {
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR);
        glColor4d(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
        draw(position, size);
    }
};