/// @file TextButton.hpp
/// @brief Contrôle visuel: Bouton avec text
/// @author Jean-Philippe Miguel-Gagnon, Isabelle Provost

#pragma once

#include <string>

#include "../../ResourcesManager.hpp"
#include "Button.hpp"

/// @class TextButton
/// @brief Contrôle visuel avec un texte qui peut déclencher une action.
class TextButton : public Button {
private:
    SDL_Color bgColor;     ///< Couleur de fond du bouton.
    SDL_Color fgColor;     ///< Couleur de text du bouton.
    string font;           ///< Police de caractères.
    int initialPaddingX;   ///< Marge initial intérieur sur l'axe des x.
    int initialPaddingY;   ///< Marge initial intérieur sur l'axe des y.
    int paddingX;          ///< Marge intérieure sur l'axe des x.
    int paddingY;          ///< Marge intérieure sur l'axe des y.
    string text;           ///< Texte.

    /// @brief Génère la texture du bouton.
    void generateText() {
        delete texture;
        SDL_Surface *surface = ResourcesManager::getResource<TTFont>(font)->renderTextBlended(text.c_str(), fgColor);

        // Si la taille du bouton est plus petite que la taille du texte, on ajuste la taille du bouton.
        // Il doit avoir au moins la distance de paddingX et paddingY.

        if (size.x < surface->w + initialPaddingX * 2) {
            size.x = surface->w + initialPaddingX * 2;
        }

        if (size.y < surface->h + initialPaddingY * 2) {
            size.y = surface->h + initialPaddingY * 2;
        }

        paddingX = (size.x - surface->w) / 2;
        paddingY = (size.y - surface->h) / 2;

        texture = new Texture(surface);
    }

public:
    /// @brief Constructeur d'un bouton avec un texte.
    /// @param position Position du bouton.
    /// @param size Taille du bouton. Elle est minimalement la taille du texte + padding.
    /// @param font Police du texte.
    /// @param text Texte du bouton.
    /// @param fgColor Couleur du texte, par défaut blanc.
    /// @param bgColor Couleur du bouton, par défaut gris.
    /// @param paddingX Marge intérieure sur l'axe des x, par défaut 20.
    /// @param paddingY Marge intérieure sur l'axe des y, par défaut 10.
    TextButton(const Vector3d &position, const Vector3d &size, const string &text = "Button", const string &font = DEFAULT_FONT, const SDL_Color &fgColor = COLOR_WHITE, const SDL_Color &bgColor = COLOR_DARK_GRAY, int paddingX = 20, int paddingY = 10) : Button(position, size) {
        this->font = font;
        this->text = text;
        this->fgColor = fgColor;
        this->bgColor = bgColor;
        this->paddingX = paddingX;
        this->paddingY = paddingY;
        this->initialPaddingX = paddingX;
        this->initialPaddingY = paddingY;

        generateText();
    }

    ~TextButton() {
        delete texture;
    }

    void draw() {
        Rectangle::drawColor(position, size, bgColor, anchor); // Arrière-plan
        Rectangle::drawTexture({position.x + paddingX, position.y + paddingY}, {size.x - paddingX * 2, size.y - paddingY * 2}, texture, anchor); // Texte
    }

    /// @brief Défini la couleur du bouton.
    /// @param color La nouvelle couleur.
    void setButtonColor(const SDL_Color &color) {
        bgColor = color;
    }

    /// @brief Défini la couleur du texte.
    /// @param color La nouvelle couleur.
    /// @note Ceci nécessite un regeneration du texte.
    void setTextColor(const SDL_Color &color) {
        if (memcmp(&fgColor, &color, sizeof(SDL_Color))) {
            fgColor = color;
            generateText();
        }
    }

    /// @brief Défini le texte.
    /// @param value Le nouveau texte.
    /// @note Ceci nécessite un regeneration de la texture. La taille va aussi être changée par rapport au texte.
    void setText(const string &value) {
        if (text != value) {
            text = value;
            generateText();
        }
    }
};
