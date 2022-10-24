/// @file Vector3d.hpp
/// @brief Vecteurs.
/// @author Thomas Laporte (thomas.laporte@hotmail.com)

#pragma once

/// @struct Vector3d
/// @brief Structure représantant un vecteur de 3 composantes réelles et opérations de vectorielles.
struct Vector3d {
    double x, y, z;   ///< Composantes (x, y, z).

    /// @param x Composante x.
    /// @param y Composante y.
    /// @param z Composante z.
    Vector3d(double x = 0.0, double y = 0.0, double z = 0.0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /// @brief Additionne deux vecteurs.
    /// @param v Vecteur à additionner.
    /// @return Vecteur additionné.
    Vector3d operator+(const Vector3d &v) const {
        return {x + v.x, y + v.y, z + v.z};
    }

    /// @brief Soustrait deux vecteurs.
    /// @param v Vecteur à soustraire.
    /// @return Vecteur soustrait.
    Vector3d operator-(const Vector3d &v) const {
        return {x - v.x, y - v.y, z - v.z};
    }
};