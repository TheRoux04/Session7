/// @file Matrix44d.hpp
/// @brief Matrice 4x4 de doubles.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

#include <cmath>
#include "Vector3d.hpp"

#define PI 3.14159265358979323846

#define e11 elements[0]    ///< 1e ligne, 1e colonne
#define e12 elements[1]    ///< 1e ligne, 2e colonne
#define e13 elements[2]    ///< 1e ligne, 3e colonne
#define e14 elements[3]    ///< 1e ligne, 4e colonne
#define e21 elements[4]    ///< 2e ligne, 1e colonne
#define e22 elements[5]    ///< 2e ligne, 2e colonne
#define e23 elements[6]    ///< 2e ligne, 3e colonne
#define e24 elements[7]    ///< 2e ligne, 4e colonne
#define e31 elements[8]    ///< 3e ligne, 1e colonne
#define e32 elements[9]    ///< 3e ligne, 2e colonne
#define e33 elements[10]   ///< 3e ligne, 3e colonne
#define e34 elements[11]   ///< 3e ligne, 4e colonne
#define e41 elements[12]   ///< 4e ligne, 1e colonne
#define e42 elements[13]   ///< 4e ligne, 2e colonne
#define e43 elements[14]   ///< 4e ligne, 3e colonne
#define e44 elements[15]   ///< 4e ligne, 4e colonne

/// @struct Matrix44d
/// @brief Une matrice 4x4 de doubles.
struct Matrix44d {
    double elements[16]{};   ///< Les éléments de la matrice.

    /// @brief Charge la matrice identité, c'est-à-dire une matrice avec 1.0 sur
    /// la diagonale et 0.0 partout ailleurs.
    void loadIdentity() {
        e11 = e22 = e33 = e44 = 1.0;
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;
    }

    /// @brief Charge une matrice de projection orthographique.
    /// @param width La largeur de la vue.
    /// @param height La hauteur de la vue.
    void loadOrthographic(int width, int height) {
        e11 = 2.0 / (double) width;
        e22 = 2.0 / (double) -height;
        e33 = e42 = e44 = 1.0;
        e41 = -1.0;
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e34 = e43 = 0.0;
    }

    void loadPerspective(double fov, double nearCut, double farCut, double ratio) {
        const double right = std::tan(fov / 2.0 * PI / 180.0) * nearCut;

        e11 = nearCut / right;
        e22 = nearCut / (right * ratio);
        e33 = -(farCut + nearCut) / (farCut - nearCut);
        e43 = (-2.0 * farCut * nearCut) / (farCut - nearCut);
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e41 = e42 = e44 = 0.0;
        e34 = -1.0;
    }

    /// @brief Charge une matrice de rotation sur l'axe X.
    /// @param angle Angle de rotation en degrés.
    void loadXRotation(double angle) {
        angle = angle * PI / 180.0;
        e11 = e44 = 1.0;
        e12 = e13 = e14 = e21 = e24 = e31 = e34 = e41 = e42 = e43 = 0.0;
        e22 = cos(angle);
        e23 = -sin(angle);
        e32 = sin(angle);
        e33 = cos(angle);


    }

    /// @brief Charge une matrice de rotation sur l'axe Y.
    /// @param angle Angle de rotation en degrés.
    void loadYRotation(double angle) {
        angle = angle * PI / 180.0;
        e22 = e44 = 1.0;
        e12 = e14 = e21 = e23 = e24 = e32 = e34 = e41 = e42 = e43 = 0.0;
        e11 = cos(angle);
        e13 = sin(angle);
        e31 = -sin(angle);
        e33 = cos(angle);

    }

    /// @brief Charge une matrice de rotation sur l'axe Z.
    /// @param angle Angle de rotation en degrés.
    void loadZRotation(double angle) {
        angle = angle * PI / 180.0;
        e33 = e44 = 1.0;
        e13 = e14 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;
        e11 = cos(angle);
        e12 = sin(angle);
        e21 = -sin(angle);
        e22 = cos(angle);

    }

    /// @brief Charge une matrice de Rotation sur un axe donné.
    /// @param angle Angle de rotation en degrés.
    /// @param axis Axe de rotation.
    void loadRotation(double angle, Vector3d axis) {
        angle = angle * PI / 180.0;
        axis.unit();
        double c = cos(angle);
        double s = sin(angle);
        double t = 1.0 - c;
        e22 = e33 = e44 = 1.0;
        e14 = e24 = e34 = e41 = e42 = e43 = 0.0;
        e11 = t * axis.x * axis.x + c;
        e12 = t * axis.x * axis.y - s * axis.z;
        e13 = t * axis.x * axis.z + s * axis.y;
        e21 = t * axis.x * axis.y + s * axis.z;
        e22 = t * axis.y * axis.y + c;
        e23 = t * axis.y * axis.z - s * axis.x;
        e31 = t * axis.x * axis.z - s * axis.y;
        e32 = t * axis.y * axis.z + s * axis.x;
        e33 = t * axis.z * axis.z + c;
    }
};