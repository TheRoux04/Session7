/// @file Label.hpp
/// @brief Ligne de texte.
/// @authors Raphael Rail, Gabriel Dufresne, Raphael Sincerny

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "../../Rectangle.hpp"
#include "../../ResourcesManager.hpp"
#include "../../TTFont.hpp"
#include "../../Texture.hpp"
#include "../../Vector3d.hpp"
#include "Drawable2d.hpp"

using namespace std;
/// @brief Étiquette.
class Label : public Drawable2d {
private:
    SDL_Color color;    ///< Couleur du texte.
    TTFont *font;       ///< Police de caractères du texte.
    string text;        ///< Texte.
    Texture *texture;   ///< Texture du texte.

public:
    /// @param fontName Police du texte.
    /// @param text Texte.
    /// @param color Couleur du texte.
    /// @param position Position du texte.
    Label(const Vector3d& position = {0, 0}, const string& text = "text", const string& fontName = DEFAULT_FONT, const SDL_Color& color = COLOR_WHITE) {
        this->position = position;
        this->text = text;
        this->font = ResourcesManager::getResource<TTFont>(fontName);
        this->color = color;
        this->texture = new Texture(font->renderTextBlended(text.c_str(), color));
    }

    ~Label() {
        delete texture;
    }

    /// @brief Affichage de l'étiquette.
    void draw() {
        Rectangle::drawTexture(position, {(double)texture->getWidth(), (double)texture->getHeight()}, texture, anchor);
    }

    /// @brief Fonction qui notifie l'obsevateur.
    void notification() {
    }

    /// @brief Mise à jour du texte.
    /// @param text Nouveau texte.
    void setText(const string& text) {
        this->text = text;
        delete texture;
        texture = new Texture(font->renderTextBlended(text.c_str(), color));
    }

    /// @brief Mise à jour de la couleur.
    /// @param color Nouvelle couleur du texte.
    void setColor(const SDL_Color& color) {
        this->color = color;
        delete texture;
        texture = new Texture(font->renderTextBlended(text.c_str(), color));
    }
};
