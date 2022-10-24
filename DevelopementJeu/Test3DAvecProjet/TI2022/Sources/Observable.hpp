/// @file Observable.hpp
/// @brief Patron de conception observateur.
/// @author Patrick Singcaster (singcaster\@clogik.io)

#pragma once

#include <list>

#include "Observer.hpp"

using namespace std;

/// @class Observable
/// @brief Sujet d'observation.
class Observable {
private:
    list<Observer *> observers;   ///< Liste des observateurs.

public:
    /// @brief Inscription d'un observateur.
    /// @param observer Observateur à inscrire.
    void subscribe(Observer *observer) {
        observers.push_back(observer);
    }

    /// @brief Désinscription d'un observateur.
    /// @param observer Observateur à désinscrire.
    void unsubscribe(Observer *observer) {
        observers.remove(observer);
    }

    /// @brief Notification des observateurs.
    void notify() {
        for (auto &it: observers)
            if (it)
                it->notification();
    }
};
