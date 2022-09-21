/// @file Vector3d.hpp
/// @brief Structure des vecteur à 3 dimensions
/// @author Olivier Savoie (1908527\etu.cegep-lanaudiere.qc.ca)

#include <cmath>

/// @struct Vecteur 3d
/// @brief Structure représentant les opérations  possible d'effectuer sur un vecteur 3d
struct Vector3d{
    double x;
    double y;
    double z;

    /// @param x Variable représentant l'axe des X du vecteur
    /// @param y Variable représentant l'axe des Y du vecteur
    /// @param z Variable représentant l'axe des Z du vecteur
    Vector3d(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /// @brief Obtention de la norme d'un vecteur
    /// @return Norme
    double norme(){
        return sqrt(x * x + y * y + z * z);
    }

    /// @brief Rendre un vecteur unitaire
    /// @return Vecteur unitaire
    Vector3d unitaire(){
        return Vector3d(x / norme(), y / norme(), z / norme());
    }

    /// @brief Calculer la somme de 2 vecteurs
    /// @param vector Vecteur recu en paramètre
    /// @return Vecteur du resultat
    Vector3d operator +(Vector3d vector){
        double x = this->x + vector.x;
        double y = this->y + vector.y;
        double z = this->z + vector.z;

        return Vector3d(x, y, z);
    }   

    /// @brief Calculer la différence de 2 vecteurs
    /// @param vector Vecteur recu en paramètre
    /// @return Vecteur du resultat
    Vector3d operator -(Vector3d vector){
        double x = this->x - vector.x;
        double y = this->y - vector.y;
        double z = this->z - vector.z;

        return Vector3d(x, y, z);
    }   

    /// @brief Calculer la produit vectoriel de 2 vecteurs
    /// @param vector Vecteur recu en paramètre
    /// @return Vecteur du resultat
    Vector3d operator *(Vector3d vector){
        double x = vector.y * this->z - this->y * vector.z;
        double y = vector.z * this->x - this->z * vector.x;
        double z = vector.x * this->y - this->x * vector.y;

        return Vector3d(x, y, z);
    }    

    /// @brief Calculer la somme de 2 vecteurs
    /// @param vector Vecteur recu en paramètre
    /// @return Vecteur du resultat
    double operator %(Vector3d vector){
        return this->x * vector.x + this->y * vector.y + this->z * vector.z;
    }  


    Vector3d operator *(int number){
        return Vector3d(this->x * number, this->y * number, this->z * number);
    }

    double angleBetween2Vector3d(Vector3d vector){
        return (*this % vector) / (norme()) * (vector.norme());
    }  
};