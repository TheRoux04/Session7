/// @file HintBox.hpp
/// @brief Controle Visuel: HintBox
/// @authors Ulric <2026856@etu.cegep-lanaudiere.qc.ca> et Marc-Antoine <2026821@etu.cegep-lanaudiere.qc.ca>
#pragma once

#include <string>

#include "../../TTFont.hpp"
#include "Drawable2d.hpp"
#include "Label.hpp"

using namespace std;
/// @brief Classe pour les boites d'indices.
class HintBox : public Drawable2d {
private:
    list<Label*> lblList; ///< Liste des lignes du texte
    int width; ///< Largeur du background
    int height; ///< Hauteur du background
    Vector3d pos; ///< Position ou le hintbox va afficher
    SDL_Color txtColor; ///< Couleur du texte
    SDL_Color backColor; ///< couleur du fond du hintbox

    /// @brief Fonction qui trouve automatiquement les dimensions nécessaires
    void autoSize(){};
public:

    /// @brief Constructeur de l'étiquette
    /// @param text Texte.
    /// @param txtColor Couleur du texte.
    /// @param pos Position du texte.
    /// @param backColor Couleur du carré de background.
    /// @param fontName Nom de la police d'écriture
    /// @param fontSize Taille du texte.
    HintBox(Vector3d pos, string text, string fontName = DEFAULT_FONT, SDL_Color txtColor = COLOR_WHITE, SDL_Color backColor = COLOR_GRAY) {
        TTFont *font = ResourcesManager::getResource<TTFont>(fontName);

        this->txtColor = txtColor;
		this->backColor = backColor;
		this->pos = pos;

        lblList.clear();
        width = 0;
        height = 0;

        int currentPos = 0;
        int taille = 0;

        Vector3d txtPos = pos;
        txtPos.x += 5;
        txtPos.y += 5;

        SDL_Point txtSize;

        for (int i = 0; i < text.size() - 1; i++){
            if (text[i] == '\n'){
                taille = i - currentPos;
                string txtGood = text.substr(currentPos, taille);
                currentPos = i+1;

                txtSize = font->getSize(txtGood);
                height += txtSize.y + 5;

                if (txtSize.x > width){
                    width = txtSize.x;
                }

                Label *label2 = new Label(txtPos, txtGood, fontName, txtColor);
                label2->setText(txtGood);
                label2->setColor(txtColor);
                txtPos.y += txtSize.y + 5;

                lblList.push_back(label2);
            }
        }

        taille = text.size() - currentPos;
        string txtGood = text.substr(currentPos, taille);
        txtSize = font->getSize(txtGood);
        height += txtSize.y + 5;

        if (txtSize.x > width){
            width = txtSize.x;
        }

        Label *label2 = new Label(txtPos, txtGood, fontName, txtColor);
        label2->setText(txtGood);
        label2->setColor(txtColor);
        label2->setPosition(txtPos);
        lblList.push_back(label2);

        this->width += 10;
        this->height += 10;

	}

    /// @brief Destructeur du Hintbox
	~HintBox() {
        for (auto it : lblList){
            delete(it);
        }
        lblList.clear();

    }

    /// @brief Change la position du hintbox
    /// @param newPos La nouvelle position
    void setPosition(Vector3d newPos){
        pos = newPos;
        Vector3d txtPos = pos;
        txtPos.x += 5;
        for (auto it : lblList){
            txtPos.y += 5;
            it->setPosition(txtPos);
        }
    }

    /// @brief Change la couleur du fond
    /// @param newColor La nouvelle couleur du fond
    void setBackgroundColor(SDL_Color newColor){
        backColor = newColor;
    }

    /// @brief Retourne la hauteur du hintbox
    /// @return La hauteur du hintbox
    int getHeight(){
        return height;
    }

    /// @brief Retourne la largeur du hintbox
    /// @return La largeur du hintbox
    int getWidth(){
        return width;
    }

	/// @brief affiche le hintbox
	void draw() override{
        
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_COLOR);

        glBegin(GL_QUADS);

        glColor4d(this->backColor.r, this->backColor.g, this->backColor.b, this->backColor.a);

        glVertex3d(pos.x,pos.y,0.0);
        glVertex3d(pos.x,(pos.y + height),0.0);
        glVertex3d((pos.x + width),(pos.y + height),0.0);
        glVertex3d((pos.x + width),pos.y,0.0);

        glEnd();

        for (auto it : lblList){
            it->draw();
        }
    }

    /// @brief Fait notification
    void notification() override {

    }

};