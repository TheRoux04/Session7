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

class Matrix44d {
public:
    double elements[16];

    void loadIdentity(){
        e11 = e22 = e33 = e44 = 1.0;
        e12 = e13 = e14 = e21 = e23 = e24 = e31 = e32 = e34 = e41 = e42 = e43 = 0.0;
    }

    void transpose() {
        std::swap(elements[1], elements[4]);
        std::swap(elements[2], elements[8]);
        std::swap(elements[3], elements[12]);
        std::swap(elements[6], elements[9]);
        std::swap(elements[7], elements[13]);
        std::swap(elements[11], elements[14]);
    }

    double scale(double x, double y, double z){
        double elementScale[] = {x, 0, 0,
                                 0, y, 0,
                                 0, 0, z};
       return elementScale;                      
    }
};