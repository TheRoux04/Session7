#include <cmath>

struct Vector{
    double x;
    double y;
    double z;

    Vector(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double norme(){
        return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    }

    Vector unitaire(){
        return Vector(x / norme(), y / norme(), z / norme());
    }

    Vector operator +(Vector vector){
        double x = this->x + vector.x;
        double y = this->y + vector.y;
        double z = this->z + vector.z;

        return Vector(x, y, z);
    }   

    Vector operator -(Vector vector){
        double x = this->x - vector.x;
        double y = this->y - vector.y;
        double z = this->z - vector.z;

        return Vector(x, y, z);
    }   

    Vector operator *(Vector vector){
        double x = vector.y * this->z - this->y * vector.z;
        double y = vector.z * this->x - this->z * vector.x;
        double z = vector.x * this->y - this->x * vector.y;

        return Vector(x, y, z);
    }    

    double operator %(Vector vector){
        return this->x * vector.x + this->y * vector.y + this->z * vector.z;
    }  


    Vector operator *(int number){
        return Vector(this->x * number, this->y * number, this->z * number);
    }    
};