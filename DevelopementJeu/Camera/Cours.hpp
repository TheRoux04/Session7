/// @file Cours.hpp
/// @brief Scène de cours.
/// @authors Patrick Singcaster

#pragma once

#include "Scene.hpp"
#include "../Matrix44d.hpp"
#include "../elements/3d/Camera.hpp"

/// @class Test
/// @brief Scène de cours.
class Cours : public Scene {
private:
    Matrix44d perspective;   ///< Matrice de projection perspective.
    Camera camera;           ///< Caméra.
    double *vertices, *texCoords;

public:
    /// @brief Chargement de la scène.
    void load() override {
        vertices = new double[72] { -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5};
        texCoords = new double[48] { 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0 };

        /// TODO: Activation des interrupteurs nécessaires.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        /// TODO: Chargement des matrices de projection nécessaires.
        perspective.loadPerspective(85.0, 1.0, 10.0, (double)size.y / (double)size.x);

        camera.setView({-3.0, 2.0, 3.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0});

        /// TODO: Ajout des resources nécessaires.
        ResourcesManager::addResource("Crate", new Texture("Crate.png"));
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
        
    }

    /// @brief Affichage de la scène.
    void handleDraw() override {
        // Affichage 3D.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(perspective.elements);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        camera.applyView();

        //glTranslated(0.0, 0.0, -3.0);
        
        glBindTexture(GL_TEXTURE_2D, ResourcesManager::getResource<Texture>("Crate")->getId());

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
        glDrawArrays(GL_QUADS, 0, 24);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    }
};
