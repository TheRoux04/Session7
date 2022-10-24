/// @file SaveFile.hpp
/// @brief Classe pour les fichiers de sauvegarde.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

#include <string>

using std::string;

/// @class SaveFile
/// @brief Classe pour les fichiers de sauvegarde.
class SaveFile {
private:
    string name; ///< Nom du joueur.
    // TODO: Ajouter les autres attributs.
public:
    /// @param name Nom du joueur.
    SaveFile(const string& name) {
        this->name = name;
    }

    ~SaveFile();

    /// @brief Retourne le nom du joueur.
    /// @return Nom du joueur.
    string getName() const {
        return name;
    }
};