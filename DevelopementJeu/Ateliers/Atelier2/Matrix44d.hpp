/// @file Matrix44d.hpp
/// @brief Classe des matrices 4x4
/// @author Olivier Savoie (1908527\etu.cegep-lanaudiere.qc.ca)

#define e11 elements[0]
#define e12 elements[1]
#define e13 elements[2]
#define e14 elements[3]
#define e21 elements[4]
#define e22 elements[5]
#define e23 elements[6]
#define e24 elements[7]
#define e31 elements[8]
#define e32 elements[9]
#define e33 elements[10]
#define e34 elements[11]
#define e41 elements[12]
#define e42 elements[13]
#define e43 elements[14]
#define e44 elements[15]

#include <algorithm> 
#include "Vector3d.hpp"

using namespace std;

/// @class Matrice 4x4
/// @brief Structure représentant les opérations  possible d'effectuer sur une matrice 4x4
class Matrix44d {
public:
    double elements[16];

    /// @brief Charge une matrice identité
    void loadIdentity(){
        e11 = e22 = e33 = e44 = 1.0;
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;
    }

    /// @brief Charge une matrice l'inversion des valeurs sur la diagonale
    void loadTranspose() {
        swap(elements[1], elements[4]);
        swap(elements[2], elements[8]);
        swap(elements[3], elements[12]);
        swap(elements[6], elements[9]);
        swap(elements[7], elements[13]);
        swap(elements[11], elements[14]);
    }

    /// @brief Charge une matrice qui change l'echelle
    void loadEchelle(double x, double y, double z){
        e11 = x;
        e22 = y;
        e33 = z;
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = e44 = 0.0;
    }

    /// @brief Charge une matrice de rotation selon l'axe X
    void loadXRotation(double angle){
        e22 = cos(angle);
        e23 = -sin(angle);
        e32 = sin(angle);
        e33 = cos(angle);
        e11 = e44 = 1.0;
        e12 = e13 = e14 = e21 = e24 = e31 = e34 = e41 = e42 = e43 = 0.0;  
    }

    /// @brief Charge une matrice de rotation selon l'axe Y
    void loadYRotation(double angle){
        e11 = cos(angle);
        e13 = sin(angle);
        e31 = -sin(angle);
        e33 = cos(angle);
        e22 = e44 = 1.0;
        e12 = e14 = e21 = e23 = e24 = e32 = e34 = e41 = e42 = e43 = 0.0;  
    }

    /// @brief Charge une matrice de rotation selon l'axe Z
    void loadZRotation(double angle){
        e11 = cos(angle);
        e12 = -sin(angle);
        e21 = sin(angle);
        e22 = cos(angle);
        e33 = e44 = 1.0;
        e13 = e14 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;  
    }

    /// @brief Charge une matrice de rotation selon l'axe X, Y et Z
    void loadRotationOnNormalisedAxis(double angle, Vector3d axis){
        double c = cos(angle);
        double s = sin(angle);
        double t = 1.0 - c;
        double x = axis.x;
        double y = axis.y;
        double z = axis.z;

        e11 = t * x * x + c;
        e12 = t * x * y - s * z;
        e13 = t * x * z + s * y;

        e21 = t * x * y + s * z;
        e22 = t * y * y + c;
        e23 = t * y * z - s * x;

        e31 = t * x * z - s * y;
        e32 = t * y * z + s * x;
        e33 = t * z * z + c;

        e14 = e24 = e34 = e41 = e42 = e43 = 0.0;
        e44 = 1.0;
    }

    /// @brief Verifie si le vecteur est unitaire avant la rotation
    void loadRotationOnAxis(double angle, Vector3d axis){
        if((axis.x * axis.x + axis.y * axis.y + axis.z * axis.z) != 1){
            axis = axis.unitaire();
        }
        
        loadRotationOnNormalisedAxis(angle, axis);
    }



};