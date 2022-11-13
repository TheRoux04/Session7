/// @file Cours.hpp
/// @brief Scène de cours.
/// @authors Patrick Singcaster

#pragma once

#include <SDL2/SDL_opengl.h>

#include "Scene.hpp"
#include "../Matrix44d.hpp"
#include "../Texture.hpp"
#include "../ResourcesManager.hpp"

/// @class Test
/// @brief Scène de cours.
class Cours : public Scene {
private:
    double rotX, rotY, rotZ; ///< Angles de rotation de la position de la caméra.
    Matrix44d orthographic; ///< Matrice de projection orthogonale (2D).
    Matrix44d perspective;  ///< Matrice de projection perspective (3D).

public:
    /// @brief Chargement de la scène.
    void load() override {
        /// TODO: Activation des interrupteurs nécessaires.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        orthographic.loadOrthographic(size.x, size.y);
        perspective.loadPerspective(89.0, 1.0, 100.0, (double)size.y / (double)size.x);

        ResourcesManager::addResource("Crate", new Texture("gopher.png"));

        rotX = rotY = rotZ = 0.0;
    }

    /// @brief Déchargement de la scène.
    void unload() {

    }    

    /// @brief Notification de la scène.
    void notification() {

    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
        rotX += 0.03;
        rotY += 0.05;
        rotZ += 0.07;
    }

    /// @brief Affichage de la scène.
    void handleDraw() override {
        // Affichage 3D
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(perspective.elements);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslated(0.0, 0.0, -2.0);
        glRotated(rotX, 1.0, 0.0, 0.0);
        glRotated(rotY, 0.0, 1.0, 0.0);
        glRotated(rotZ, 0.0, 0.0, 1.0);

        glBegin(GL_QUADS);
            // Back
            glTexCoord2d(0.0, 0.0); glVertex3d(-0.5, -0.5, -0.5);
            glTexCoord2d(1.0, 0.0); glVertex3d(0.5, -0.5, -0.5);
            glTexCoord2d(1.0, 1.0); glVertex3d(0.5, 0.5, -0.5);
            glTexCoord2d(0.0, 1.0); glVertex3d(-0.5, 0.5, -0.5);
            // Front
            glTexCoord2d(0.0, 0.0); glVertex3d(-0.5, -0.5, 0.5);
            glTexCoord2d(1.0, 0.0); glVertex3d(0.5, -0.5, 0.5);
            glTexCoord2d(1.0, 1.0); glVertex3d(0.5, 0.5, 0.5);
            glTexCoord2d(0.0, 1.0); glVertex3d(-0.5, 0.5, 0.5);
            // Top
            glTexCoord2d(0.0, 0.0); glVertex3d(-0.5, -0.5, 0.5);
            glTexCoord2d(1.0, 0.0); glVertex3d(-0.5, -0.5, -0.5);
            glTexCoord2d(1.0, 1.0); glVertex3d(0.5, -0.5, -0.5);
            glTexCoord2d(0.0, 1.0); glVertex3d(0.5, -0.5, 0.5);
            // Bottom
            glTexCoord2d(0.0, 0.0); glVertex3d(-0.5, 0.5, 0.5);
            glTexCoord2d(1.0, 0.0); glVertex3d(-0.5, 0.5, -0.5);
            glTexCoord2d(1.0, 1.0); glVertex3d(0.5, 0.5, -0.5);
            glTexCoord2d(0.0, 1.0); glVertex3d(0.5, 0.5, 0.5);
            // Left
            glTexCoord2d(0.0, 0.0); glVertex3d(-0.5, 0.5, 0.5);
            glTexCoord2d(1.0, 0.0); glVertex3d(-0.5, 0.5, -0.5);
            glTexCoord2d(1.0, 1.0); glVertex3d(-0.5, -0.5, -0.5);
            glTexCoord2d(0.0, 1.0); glVertex3d(-0.5, -0.5, 0.5);
            // Right
            glTexCoord2d(0.0, 0.0); glVertex3d(0.5, 0.5, 0.5);
            glTexCoord2d(1.0, 0.0); glVertex3d(0.5, 0.5, -0.5);
            glTexCoord2d(1.0, 1.0); glVertex3d(0.5, -0.5, -0.5);
            glTexCoord2d(0.0, 1.0); glVertex3d(0.5, -0.5, 0.5);
        glEnd();

        // Affichage 2D
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(orthographic.elements);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        /*
        glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0); glVertex3d(0.0, 0.0, 0.0);
            glTexCoord2d(1.0, 0.0); glVertex3d(100.0, 0.0, 0.0);
            glTexCoord2d(1.0, 1.0); glVertex3d(100.0, 100.0, 0.0);
            glTexCoord2d(0.0, 1.0); glVertex3d(0.0, 100.0, 0.0);
        glEnd();
        */
    }
};
