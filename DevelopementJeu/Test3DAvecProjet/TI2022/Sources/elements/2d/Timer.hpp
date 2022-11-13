/// @file Timer.hpp
/// @brief Minuteur.
/// @author Jérémy Gaouette, Jean-Philippe Miguel-Gagnon

#pragma once

#include <chrono>
#include <string>

using std::string;
using std::to_string;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

/// @class Chrono
/// @brief minuteur.
class Timer {
private:
    steady_clock::time_point pauseTime;   ///< Début du minuteur.
    steady_clock::time_point endTime;     ///< Fin du minuteur.
    double time;                          ///< Temps du minuteur en secondes.
    bool isPaused;

public:
    /// @brief Constructeur d'un minuteur.
    Timer(double time) {
        this->time = time;
        isPaused = false;
        reset();
    }

    /// @brief Reprise du minuteur.
    void resume() {
        if (isPaused) {
            endTime += steady_clock::now() - pauseTime;
            isPaused = false;
        }
    }

    /// @brief Mets en pause le minuteur
    void stop() {
        if (!isPaused) {
            pauseTime = steady_clock::now();
            isPaused = true;
        }
    }

    /// @brief Remet le minuteur à zéro.
    void reset() {
        pauseTime = steady_clock::now();
        endTime = pauseTime + duration_cast<steady_clock::duration>(duration<double>(time));
    }

    /// @brief Retourne le temps restant avant la fin du minuteur en secondes.
    double getRemainingTime() {
        if (duration_cast<nanoseconds>(endTime - steady_clock::now()).count() <= 0) {
            stop();
            return 0;
        }
        
        if (isPaused) {
            return (double) duration_cast<nanoseconds>(endTime - pauseTime).count() / 1000000000.0;
        }


        return (double) duration_cast<nanoseconds>(endTime - steady_clock::now()).count() / 1000000000.0;
    }

    /// @brief Retourne si le minuteur est terminé.
    bool isFinished() {
        return steady_clock::now() >= endTime;
    }

    /// @brief Permet de formater un temps en une chaîne de caractères représentant les minutes et secondes.
    /// @param time Temps à formater en seconde.
    /// @return Temps formaté.
    static string format(double time) {
        int minutes = (int) time / 60;
        int seconds = (int) time % 60;

        if (seconds < 10) {
            return to_string(minutes) + ":0" + to_string(seconds);
        }
        return to_string(minutes) + ":" + to_string(seconds);
    }
};