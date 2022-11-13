/// @file ResourcesManager.hpp
/// @brief Gestionnaire des ressources
/// @authors Jérémy Gaouette <jeremygaouette@gmail.com>,
///          Louis-Félix Veillette <2038026@etu.cegep-lanaudiere.qc.ca>

#pragma once

#include <map>
#include <string>

#include "Resource.hpp"

using std::enable_if;
using std::is_base_of;
using std::map;
using std::string;

class ResourcesManager {
private:
    static map<string, Resource *> resources;   ///< Collection de ressources

public:
    /// @brief Libération de toutes les ressources.
    static void free() {
        for (const auto &it: resources) {
            delete it.second;
        }
        resources.clear();
    }

    /// @brief Ajout d'une ressource.
    /// @param name Nom de la ressource.
    /// @param resource Ressource à ajouter.
    static void addResource(const string &name, Resource *resource) {
        resources[name] = resource;
    }

    /// @brief Retrait d'une ressource.
    /// @param name Nom de la ressource.
    static void removeResource(const string &name, bool destroy = false) {
        if (resources.find(name) != resources.end()) {
            if (destroy)
                delete resources[name];
            resources.erase(name);
        }
    }

    /// @brief Obtention d'une ressource.
    /// @param name Nom de la ressource.
    /// @tparam T Type de la ressource. Elle doit hériter de la classe Resource.
    /// @return Ressource.
    template<typename T, typename = typename enable_if<is_base_of<Resource, T>::value>::type>
    static T *getResource(const string &name) {
        if (resources.find(name) == resources.end()) {
            T *missing = new T();
            resources[name] = missing;
            return missing;
        }
        return dynamic_cast<T *>(resources[name]);
    }
};

map<string, Resource *> ResourcesManager::resources;
