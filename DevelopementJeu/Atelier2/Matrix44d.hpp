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

class Matrix44d {
public:
    double elements[16];

    void loadIdentity(){
        e11 = e22 = e33 = e44 = 1.0;
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;
    }

    void loadTranspose() {
        swap(elements[1], elements[4]);
        swap(elements[2], elements[8]);
        swap(elements[3], elements[12]);
        swap(elements[6], elements[9]);
        swap(elements[7], elements[13]);
        swap(elements[11], elements[14]);
    }

    void loadEchelle(double w, double x, double y, double z){
        e11 = w;
        e22 = x;
        e33 = y;
        e44 = z;
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;
    }

    void loadXRotation(double angle){
        e22 = cos(angle);
        e23 = -sin(angle);
        e32 = sin(angle);
        e33 = cos(angle);
        e11 = e44 = 1.0;
        e12 = e13 = e14 = e21 = e24 = e31 = e34 = e41 = e42 = e43 = 0.0;  
    }

    void loadYRotation(double angle){
        e11 = cos(angle);
        e13 = sin(angle);
        e31 = -sin(angle);
        e33 = cos(angle);
        e22 = e44 = 1.0;
        e12 = e14 = e21 = e23 = e24 = e32 = e34 = e41 = e42 = e43 = 0.0;  
    }

    void loadZRotation(double angle){
        e11 = cos(angle);
        e12 = -sin(angle);
        e21 = sin(angle);
        e22 = cos(angle);
        e33 = e44 = 1.0;
        e13 = e14 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;  
    }

    void loadRotation(double angle, Vector3d axis){
        double c = cos(angle);
        double s = sin(angle);
        double t = 1.0 - c;
        double x = axis.x;
        double y = axis.y;
        double z = axis.z;

        e11 = t * x * x + c;
        e12 = t * x * y - s * z;
        e13 = t * x * z + s * y;
        e14 = 0.0;

        e21 = t * x * y + s * z;
        e22 = t * y * y + c;
        e23 = t * y * z - s * x;
        e24 = 0.0;

        e31 = t * x * z - s * y;
        e32 = t * y * z + s * x;
        e33 = t * z * z + c;
        e34 = 0.0;

        e31 = 0.0;
        e32 = 0.0;
        e33 = 0.0;
        e34 = 1.0;
    }


};