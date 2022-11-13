/// @file ButtonSequence.hpp
/// @brief
/// @author Eugène-Emmanuël Dubuc, Jérémy Perreault

#pragma once

#include "../../Matrix44d.hpp"
#include "../../scenes/Scene.hpp"
#include "CheckBox.hpp"
#include "DefaultBar.hpp"
#include "Drawable2d.hpp"
#include "FPSCounter.hpp"
#include "HintBox.hpp"
#include "Image.hpp"
#include "ImageButton.hpp"
#include "ImageCounter.hpp"
#include "Label.hpp"
#include "ReachBar.hpp"
#include "TextBox.hpp"
#include "TextButton.hpp"
#include "TextCounter.hpp"
#include "Timer.hpp"

/// @brief Classe pour les séquences de boutons
class ButtonSequence : public Drawable2d {
private:
    Rectangle background;
    list<Label> charSequence;
    string sequence;

public:
    /// @brief Constructeur
    ButtonSequence() {

    }

    /// @brief Destructeur
    ~ButtonSequence() {
    }

    /// @brief Ajoute un bouton à la séquence
    /// @param button Le bouton à ajouter
    void addButton(TextButton button) {
    }

    /// @brief Retire un bouton de la séquence
    /// @param button Le bouton à retirer
    void removeButton(TextButton button) {
    }

    /// @brief Retire un bouton de la séquence
    /// @param index L'index du bouton à retirer
    void removeButton(int index) {

    }

    /// @brief Retourne le bouton à l'index spécifié
    /// @param index L'index du bouton à retourner
    /// @return Le bouton à l'index spécifié
    TextButton getButton(int index) {
        list<Label>::iterator it = charSequence.begin();
        advance(it, index);
        return *it;
    }

    /// @brief Retourne le nombre de boutons dans la séquence
    /// @return Le nombre de boutons dans la séquence
    int getButtonCount() {
        return charSequence.size();
    }

    /// @brief Retourne la séquence de boutons
    /// @return La séquence de boutons
    list<Label> getButtonSequence() {
        return charSequence;
    }

    /// @brief Retourne la position du bouton à l'index spécifié
    /// @param index L'index du bouton dont on veut la position
    /// @return La position du bouton à l'index spécifié
    Vector3d getButtonPosition(int index) {
        list<Label>::iterator it = charSequence.begin();
        advance(it, index);
        return it->getPosition();
    }

    /// @brief Retour
};