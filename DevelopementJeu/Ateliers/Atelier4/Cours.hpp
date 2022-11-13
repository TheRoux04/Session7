/// @file Cours.hpp
/// @brief Scène de cours.
/// @authors Patrick Singcaster

#pragma once

#include "Scene.hpp"
#include "../Matrix44d.hpp"
#include "../Mesh.hpp"

/// @class Test
/// @brief Scène de cours.
class Cours : public Scene {
private:
    Matrix44d perspective;   ///< Matrice de projection perspective.
    Mesh* mesh;              ///< Maillage.
    
    Matrix44d rotationX, rotationY, rotationZ; ///< Matrices de rotation.

public:
    /// @brief Chargement de la scène.
    void load() override {
    
        /// TODO: Activation des interrupteurs nécessaires.
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        /// TODO: Chargement des matrices de projection nécessaires.
        perspective.loadPerspective(85.0, 1.0, 10.0, (double)size.y / (double)size.x);

        /// TODO: Ajout des resources nécessaires.
        ResourcesManager::addResource("Crate", new Texture("Crate.png"));

        mesh = new Mesh("", "Crate");
        mesh->translate(0.0, 3.0, 0.0);
        rotationX.loadXRotation(0.03, {0.0, 3.0, 0.0});
        rotationY.loadYRotation(0.05, {0.0, 3.0, 0.0});
        rotationZ.loadZRotation(0.07, {0.0, 3.0, 0.0});
    }

    /// @brief Déchargement de la scène.
    void unload() {
        delete mesh;
        ResourcesManager::removeResource("Crate");
    }    

    /// @brief Notification de la scène.
    void notification() {

    }

    /// @brief Mise à jour de la scène.
    /// @param deltaTime Secondes écoulées depuis le dernier rafraîchissement.
    void handleUpdate(const double &deltaTime) {
        mesh->globalTransform(rotationX);
        mesh->globalTransform(rotationY);
        mesh->globalTransform(rotationZ);
    }

    /// @brief Affichage de la scène.
    void handleDraw() override {
        // Affichage 3D.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(perspective.elements);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslated(0.0, 0.0, -3.0);
        
        mesh->draw();

    }
};
