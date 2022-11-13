/// @file Scene.hpp
/// @brief Abstraction d'une scène.
/// @authors Raphael Rail, Isabelle Provost, Thomas Laporte, Jérémie Perreault, Eugène-Emmanuel Dubuc, Olivier Savoie, Gabriel Dufresne, Raphael Sincerny

#pragma once

#include <list>
#include <map>

#include "../Event.hpp"
#include "../Observable.hpp"
#include "../Observer.hpp"
#include "../elements/2d/Drawable2d.hpp"

/// @class Scene
/// @brief Abstraction d'une scène.
class Scene : public Observer {
private:
    map<unsigned int, Observable *> events; ///< Événements gérés.

protected:
    SDL_Point size;
    list<Drawable2d *> elements2D; ///< Éléments 2D affichables.
    // list<Drawable3d *> elements3D; ///< Éléments 3D affichables.

public:
    virtual ~Scene() {
        clearEvents();

        // Clear drawable2D
        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }
    }

    /// @brief Libération et retrait des événements gérés.
    void clearEvents() {
        for (const auto& it : events)
            delete it.second;
        events.clear();        
    }

    /// @brief Abonnement d'un observateur à un évènement.
    /// @param eventType Événement à observer.
    /// @param element Observateur à abonner.
    void bindEvent(unsigned int eventType, Observer *element) {
        if (events.find(eventType) == events.end())
            events[eventType] = new Observable();
        events[eventType]->subscribe(element);
    }

    /// @brief Désabonnement d'un observateur d'un événement.
    /// @param eventType Événement observé.
    /// @param element Observateur à désabonner.
    void unbindEvent(unsigned int eventType, Observer *element) {
        if (events.find(eventType) != events.end())
            events[eventType]->unsubscribe(element);
    }

    /// @brief Notification des observateurs d'un type d'événement.
    /// @param eventType Type d'événement concerné.
    void handleEvent(unsigned int eventType) {
        if (events.find(eventType) != events.end())
            events[eventType]->notify();
    }

    /// @brief Obtention de la taille de la scène.
    /// @return Taille de la scène.
    const SDL_Point& getSize() {
        return size;
    }

    /// @brief Détermination de la taille de la scène.
    /// @param size Taille de la scène.
    void setSize(const SDL_Point& size) {
        this->size = { size.x, size.y };
    }

    /// @brief Chargement de la scène.
    virtual void load() = 0;

    /// @brief Déchargement de la scène.
    virtual void unload() = 0;

    /// @brief Notification de la scène.
    virtual void notification() = 0;

    /// @brief Mise à jour de la scène.
    virtual void handleUpdate(const double& deltaTime) = 0;

    /// @brief Affichage de la scène.
    virtual void handleDraw() = 0;
};
