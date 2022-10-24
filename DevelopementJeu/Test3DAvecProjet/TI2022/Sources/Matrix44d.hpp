/// @file Matrix44d.hpp
/// @brief Matrice 4x4 de doubles.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

#include <cmath>

#define PI 3.1415926535897932384626433832795

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

    /// @brief Charge une matrice de projection perspective.
    /// @param fov Angle (degré) du champ de vision horizontal.
    /// @param nearCut Distance minimale de rendu.
    /// @param farCut Distance maximale de rendu.
    void loadPerspective(double fov, double nearCut, double farCut, double ratio) {
        const double right = tan((fov / 2.0) * PI / 180.0) * nearCut;
        const double top = right * ratio;

        e11 = nearCut / right;
        e22 = nearCut / top;
        e33 = -(farCut + nearCut) / (farCut - nearCut);
        e34 = -1.0;
        e43 = (-2.0 * farCut * nearCut) / (farCut - nearCut);
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e41 = e42 = e44 = 0.0;
    }
};