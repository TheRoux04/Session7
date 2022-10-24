/// @file SaveSlot.hpp
/// @brief Classe pour afficher une sauvegarde.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

#include "Label.hpp"
#include "Button.hpp"
#include "../../SaveFile.hpp"
class SaveSlot : public Button {
private:
    list<Label *> labels;

    SDL_Color bgColor;
public:
    SaveSlot(const Vector3d& position, const Vector3d& size, const SaveFile& saveFile, SDL_Color fgColor = COLOR_WHITE, SDL_Color bgColor = COLOR_DARK_GRAY) : Button(position, size) {
        this->bgColor = bgColor;

        Label *title = new Label({position.x + size.x / 2, position.y + 20}, "Sauvegarde", DEFAULT_FONT, fgColor);
        Label *name = new Label({position.x + size.x / 2, position.y + 50}, saveFile.getName(), DEFAULT_FONT, fgColor);
        title->setAnchor(TOP_CENTER);
        name->setAnchor(TOP_CENTER);

        labels.push_back(title);
        labels.push_back(name);
    }

    ~SaveSlot() {
        for (Label *label : labels) {
            delete label;
        }
    }

    void draw() {
        Rectangle::drawColor(position, size, bgColor, anchor);
        for (Label *label : labels) {
            label->draw();
        }
    }

    /// @brief Défini la couleur du bouton.
    /// @param color La nouvelle couleur.
    void setButtonColor(const SDL_Color &color) {
        bgColor = color;
    }
};
