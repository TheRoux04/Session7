/// @file Chrono.hpp
/// @brief Chronomètre.
/// @author Jean-Philippe Miguel-Gagnon, Jérémy Gaouette

#pragma once

#include <chrono>
#include <string>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;
using std::string;
using std::to_string;

/// @class Chrono
/// @brief Chronomètre.
class Chrono {
private:
    steady_clock::time_point start;  ///< Début du chronomètre.
    
public:
    /// @brief Constructeur d'un chronomètre.
    Chrono() {
        reset();
    }

    /// @brief Remet le chronomètre à zéro.
    inline void reset() {
        start = steady_clock::now();
    }

    /// @brief Retourne le temps écoulé depuis le dernier reset.
    /// @return Temps écoulé depuis le dernier reset.
    inline double getDelta() {
        return (double) duration_cast<nanoseconds>(steady_clock::now() - this->start).count() / 1000000000.0;
    }
};