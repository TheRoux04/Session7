/// @file Collision.hpp
/// @brief Classe de permettant la détection de collision
/// @author Olivier Savoie

#pragma once

#include "Vector3d.hpp"

/// @class Collision
class Collision {
public:
    /// @brief Constructeur.
    /// @param position Position de la collision.
    /// @param movement Mouvement de la collision.
    /// @param t0 Position 0
    /// @param t1 Position 1
    /// @param t2 Position 2
    /// @param normal Normale de la collision.
    Vector3d collision(Vector3d position, Vector3d movement, Vector3d t0, Vector3d t1, Vector3d t2, Vector3d normal) {
        double dot = movement % normal;
        if (dot != 0.0) {
            double ratio = (normal % (t0 - position)) / (normal % movement);
            if ((ratio > 0.0) && (ratio <= 1.0)) {
                Vector3d intersection = position + movement * ratio;

                Vector3d viTo0 = t0 - intersection;
                Vector3d v0To2 = t2 - t0;

                Vector3d viTo2 = t2 - intersection;
                Vector3d v2To1 = t1 - t2;

                Vector3d viTo1 = t1 - intersection;
                Vector3d v2To0 = t0 - t1;

                double det1 = viTo0.x * v0To2.y - viTo0.y * v0To2.x;
                double det2 = viTo2.x * v2To1.y - viTo2.y * v2To1.x;
                double det3 = viTo1.x * v2To0.y - viTo1.y * v2To0.x;

                if (((det1 >= 0.0) && (det2 >= 0.0) && (det3 >= 0.0)) || ((det1 <= 0.0) && (det2 <= 0.0) && (det3 <= 0.0))) {
                    return intersection;
                }
            }
        }
        return NULL;
    }
};