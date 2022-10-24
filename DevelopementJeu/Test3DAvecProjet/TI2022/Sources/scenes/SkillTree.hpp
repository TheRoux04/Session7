/// @file SkillTree.hpp
/// @brief Classe des arbes a competences
/// @author Bryan <1672406@etu.cegep-lanaudiere.qc.ca>
#pragma once

#include <string>
#include <map>

#include "Scene.hpp"
#include "Constants.hpp"
#include "../elements/2d/Label.hpp"
#include "../elements/2d/Button.hpp"
#include "../elements/2d/Image.hpp"
#include "../elements/2d/HintBox.hpp"

//Just defines (facilite peut-etre la lecture)
#define NO_INDEX -1
#define IMAGE_COUNT 13
#define IMAGE_GOPHER "gopher.png"

//TODO: Changer 1 a 0 pour pas avoir des debugs
#define DEBUG 1

//Layout
#define MARGIN_LEFT 100
#define MARGIN_TOP 110
#define SPACING_HORIZONTAL 260
#define SPACING_VERTICAL 100

//Images
#define SKILL_BACKGROUND "SkillBackground.png"
#define IMAGE_SIZE_X 75
#define IMAGE_SIZE_Y 75
#define IMAGE_SIZE {IMAGE_SIZE_X, IMAGE_SIZE_Y}
#define IMAGE_OFFSET_XY -10

//Start
#define IMAGE_START_X MARGIN_LEFT + IMAGE_OFFSET_XY
#define IMAGE_START_Y MARGIN_LEFT + IMAGE_OFFSET_XY

#if DEBUG == 1
  #include <iostream>
  #define dLog(msg, tag) std::cout << msg << " : " << tag << std::endl
  #define dElement(elemName, pos) std::cout << elemName << " : " << pos
#else
  #define dLog(msg, tag)
#endif

/// @class SkillTree
/// @brief Classe pour les arbes a competences
class SkillTree : public Scene{
private:
    map<int, Image*> images;     ///< Positions d'images avec leur indices
    Texture *background;         ///< Arriere plan du Scene
    Button *btn;                 ///< Bouton pour aller a Post-Quart

    //TODO: A voir comment on va avoir les stats du joueur (sa peut peut-etre attendre?)
//    PlayerStats *playerStats;

    //Hintbox
    HintBox *hintBoxDescriptor;  ///< Hintbox decrivant les competences
    char hintIndex;              ///< Index du image

    /// @brief Calculer indice du image selon la souris
    /// @param ParamName DescParam
    char getIndexFromMouse(const SDL_Point &pt){
        for(int index = 0; index < IMAGE_COUNT; index++){
            Vector3d pos = images[index + 1]->position;

            if(pt.x >= pos.x && pt.x <= pos.x + IMAGE_SIZE_X &&
               pt.y >= pos.y && pt.y <= pos.y + IMAGE_SIZE_Y){
                return index;
            }
        }

        return NO_INDEX;
    }

public:
    enum SKILL_TYPE{
      MOVE_SPEED, SMELL, TIME, FIXING_SPEED
    };

    enum SKILL_LEVEL{
      STUDENT, TRAINEE, TECHNICIAN, BENJAMIN
    };

    void load() override{
        bindEvent(SDL_MOUSEMOTION, this);
        hintIndex = 0;
        //TODO: Ajouter Titre
        //TODO: Resize Labels
        //TODO: Ajouter texte en dessus image
        //TODO: Trouver images pour chaque image/Skill
        ResourcesManager::addResource("SkillBackground", new Texture(SKILL_BACKGROUND));
        ResourcesManager::addResource("gopher", new Texture(IMAGE_GOPHER));

        background = ResourcesManager::getResource<Texture>("SkillBackground");

        hintBoxDescriptor = new HintBox({0, 0}, "Hi, i'm a placeholder!", DEFAULT_FONT, COLOR_WHITE, COLOR_BLACK);

        //Nom de labels + fichiers image
        string labels[8];
        //Niveaux
        labels[0] = "Etudiant";
        labels[1] = "Stagiere";
        labels[2] = "Technicien";
        labels[3] = "Benjamin";
        //Type de competences
        labels[4] = "Vitesse Deplacement";
        labels[5] = "Odeur";
        labels[6] = "Temps";
        labels[7] = "Reparation";

        for(int xIndex = 0; xIndex < 4; xIndex++){
            Label *lvlHeader = new Label({MARGIN_LEFT + SPACING_HORIZONTAL * double(xIndex+1), MARGIN_TOP}, labels[xIndex].c_str());
            elements2D.push_back(lvlHeader);

            Label *skillType = new Label({MARGIN_LEFT, MARGIN_TOP + SPACING_VERTICAL * double(xIndex+1)}, labels[xIndex+4].c_str());
            elements2D.push_back(skillType);

            for(int yIndex = 0; yIndex < 4; yIndex++){
                //Skip ceux pas necessaire
                if((xIndex == 2 || xIndex == 3) && yIndex == 0){
                    continue;
                }else if(xIndex == 0 && yIndex == 3){
                    continue;
                }

                Image *skillImg = new Image(
                            {IMAGE_START_X + SPACING_HORIZONTAL * double(yIndex+1),
                              IMAGE_START_Y + SPACING_VERTICAL * double(xIndex+1)},
                            IMAGE_SIZE, "gopher");
                images[(((xIndex * 3) + 1) + yIndex)] = skillImg;
                elements2D.push_back(skillImg);
            }
        }

#if DEBUG == 1
        for(int i = 0; i < IMAGE_COUNT; i++){
          dLog("X Index", images[i + 1]->position.x);
          dLog("Y Index", images[i + 1]->position.y);
        }
#endif
    }

    void unload() override{
        unbindEvent(SDL_MOUSEMOTION, this);

        delete hintBoxDescriptor;

        auto itElements2D = elements2D.begin();
        auto endElements2D = elements2D.end();
        while (itElements2D != endElements2D) {
            delete *itElements2D;
            itElements2D = elements2D.erase(itElements2D);
        }

        ResourcesManager::removeResource("SkillBackground");
        ResourcesManager::removeResource("gopher");
    }

    void notification() override{
        SDL_Point mousePos = Event::getMousePosition();
        dLog("MouseX", mousePos.x);
        dLog("MouseY", mousePos.y);

        hintIndex = getIndexFromMouse(mousePos);
        if(hintIndex != NO_INDEX){
            dLog("INDEX", (int)hintIndex);
            delete hintBoxDescriptor;
            hintBoxDescriptor = new HintBox({(double)mousePos.x, (double)mousePos.y}, std::to_string(hintIndex));
        }

        //TODO: Afficher texte selon l'index
    }

    void handleUpdate(const double& deltaTime) override{}

    void handleDraw() override{
        Rectangle::drawTexture({0,0}, {WINDOW_WIDTH, WINDOW_HEIGHT}, background);

        for(Drawable2d *element: elements2D){
            element->draw();
        }

        //TODO: Verifier pourquoi il s'affiche rien que blanc
        if(hintIndex != NO_INDEX){
            hintBoxDescriptor->draw();
        }
    }

    /// @brief Debloquer une competence
    /// @param type Type de competence
    /// @param lvl Niveau de competence
    /// @return True, si competence peut etre debloquer
    bool unblockSkill(SKILL_TYPE type, SKILL_LEVEL lvl){
        //TODO: Verification
        //TODO: Debloquer Competence
        return false;
    }

};
