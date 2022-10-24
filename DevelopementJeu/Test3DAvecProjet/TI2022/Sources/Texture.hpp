/// @file Texture.hpp
/// @brief Créateur de texture.
/// @author Louis-Félix Veillette, Jérémie Perreault. Jérémy Gaouette, Jean-Philippe Miguel-Gagnon

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "Resource.hpp"

/// @class Texture
/// @brief Créer des textures pour qu'elles apparaissent dans la fenêtre.
class Texture : public Resource {
private:
    unsigned int textureId, width, height;

public:
    /// @brief Génère une texture à partir d'une surface.
    /// @param surface Surface à partir de laquelle la texture sera générée.
    Texture(SDL_Surface *sdlSurface) {
        if (sdlSurface == nullptr) {
            generateMissingTexture();
            return;
        }
        this->width = sdlSurface->w;
        this->height = sdlSurface->h;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
#ifdef __APPLE__
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
#else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
#endif
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(sdlSurface);
    }

    /// @brief Génère une texture à partir d'un fichier.
    /// @param fileName Nom du fichier. Le chemin va être préfixé par Constants::IMAGES_PATH.
    Texture(const string &fileName = MISSING_IMAGE) {
        SDL_Surface *sdlSurface = IMG_Load((IMAGES_PATH + fileName).c_str());
        if (sdlSurface == nullptr) {
            generateMissingTexture();
            return;
        }
        this->width = sdlSurface->w;
        this->height = sdlSurface->h;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(sdlSurface);
    }

    ~Texture() {
        glDeleteTextures(1, &textureId);
    }

    /// @brief Génère une texture manquante.
    void generateMissingTexture() {
        SDL_Surface *sdlSurface = IMG_Load(MISSING_IMAGE_PATH);
        this->width = sdlSurface->w;
        this->height = sdlSurface->h;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        SDL_FreeSurface(sdlSurface);
    }

    /// @brief Accède à la largeur de la texture.
    /// @return Largeur de la texture.
    inline unsigned int getWidth() {
        return width;
    }

    /// @brief Accède à la hauteur de la texture.
    /// @return Hauteur de la texture.
    inline unsigned int getHeight() {
        return height;
    }

    /// @brief Retourne l'identifiant de la texture.
    /// @return Identifiant de la texture.
    inline unsigned int getId() {
        return textureId;
    }

    /// @brief Hérite de la classe Resource.
    void inherit() {
    }
};