/// @file Constants.hpp
/// @brief Définition des constantes.
/// @author Jean-Philippe Miguel-Gagnon

#pragma once

// Couleurs
#define COLOR_WHITE \
    { 255, 255, 255, 255 }   ///< Couleur blanche.
#define COLOR_BLACK \
    { 0, 0, 0, 255 }   ///< Couleur noire.
#define COLOR_GRAY \
    { 128, 128, 128, 255 }   ///< Couleur grise.
#define COLOR_DARK_GRAY \
    { 64, 64, 64, 255 }   ///< Couleur grise foncée.
#define COLOR_RED \
    { 255, 0, 0, 255 }   ///< Couleur rouge.
#define COLOR_GREEN \
    { 0, 255, 0, 255 }   ///< Couleur verte.
#define COLOR_BLUE \
    { 0, 0, 255, 255 }   ///< Couleur bleue.
#define COLOR_PRIMARY \
    { 128, 128, 255, 255 }   ///< Couleur primaire. (bleu)
#define COLOR_MIO_TEXT \
    {252, 202, 3, 255} ///< Couleur du texte dans les mio. (Bleu pâle)    

// Chemins
#define ASSSETS_PATH "../Assets/"   ///< Chemin vers les assets.
#define FONTS_PATH ASSSETS_PATH "Fonts/"   ///< Chemin vers les polices.
#define IMAGES_PATH ASSSETS_PATH "Images/"   ///< Chemin vers les images.

// Polices
#define DEFAULT_FONT "Side-Love.ttf"                 ///< Police par défaut.
#define DEFAULT_FONT_SIZE 24                   ///< Taille de police par défaut.

// Images
#define MISSING_IMAGE "missing.png"   ///< Chemin vers l'image manquante.
#define MISSING_IMAGE_PATH IMAGES_PATH MISSING_IMAGE   ///< Chemin vers l'image manquante.

#define DEFAULT_COLOR COLOR_WHITE              ///< Couleur par défaut.
#define DEFAULT_BACKGROUND_COLOR COLOR_BLACK   ///< Couleur de fond par défaut.

// Paramètres de la fenêtre
#define WINDOW_WIDTH 1280   ///< Largeur de la fenêtre.
#define WINDOW_HEIGHT 720   ///< Hauteur de la fenêtre.
