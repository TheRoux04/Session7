#pragma once

#include <fstream>
#include "ResourcesManager.hpp"

using namespace std;

class Mesh
{
private:
    int vertexCount; // Nombre de sommets
    unsigned int textureId; // Tableau des identifiants de texture.
    double *vertices;  ///< Sommets.
    double *texCoords; ///< Coordonnées de texture.
    double *normals;   ///< Normales.

public:
    Mesh(const char* filename, const string& textureName){
        /*ifstream file;
        file.open(filename);
        if (file.is_open()){
            double x, y, z;
            file >> x;
            file >> y;
            file >> z;

            file.ignore(50, 10);
        }
        file.close();*/

        this->vertexCount = 24;
        this->textureId = ResourcesManager::getResource<Texture>(textureName)->getId();
        this->vertices = new double[72] { -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5};
        this->texCoords = new double[48] { 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0 };
        this->normals = new double[72] { 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, //Back
                                   0.0, 0.0,  1.0, 0.0, 0.0,  1.0, 0.0, 0.0,  1.0, 0.0, 0.0,  1.0, //Front
                                   0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, //Buttom
                                   0.0, 1.0 , 0.0, 0.0, 1.0 , 0.0, 0.0, 1.0 , 0.0, 0.0, 1.0 , 0.0, //Top
                                   -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, //Left
                                   1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 }; //Right
    }

    ~Mesh(){
        delete[] vertices;
        delete[] texCoords;
    }

    void draw(){
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
        glNormalPointer(GL_DOUBLE, 0, normals);
        glDrawArrays(GL_QUADS, 0, vertexCount);

    }

    void globalTransform(const Matrix44d& matrix){
        double x, y, z;
        for(int i = 0; i < vertexCount; i++){
            x = vertices[i * 3];
            y = vertices[i * 3 + 1];
            z = vertices[i * 3 + 2];
            

            vertices[i * 3] = x * matrix.e11 + y * matrix.e21 + z * matrix.e31;
            vertices[i * 3 + 1] = x * matrix.e12 + y * matrix.e22 + z * matrix.e32;
            vertices[i * 3 + 2] = x * matrix.e13 + y * matrix.e23 + z * matrix.e33;

            x = normals[i * 3];
            y = normals[i * 3 + 1];
            z = normals[i * 3 + 2];

            normals[i * 3] = x * matrix.e11 + y * matrix.e21 + z * matrix.e31;
            normals[i * 3 + 1] = x * matrix.e12 + y * matrix.e22 + z * matrix.e32;
            normals[i * 3 + 2] = x * matrix.e13 + y * matrix.e23 + z * matrix.e33;
        }
    }

    void localTransform(const Matrix44d& matrix){
        double x, y, z;
        for(int i = 0; i < vertexCount; i++){
            x = vertices[i * 3] - matrix.e14;
            y = vertices[i * 3 + 1] - matrix.e24;
            z = vertices[i * 3 + 2] - matrix.e34;
            

            vertices[i * 3] = (x * matrix.e11 + y * matrix.e21 + z * matrix.e31) + matrix.e14;
            vertices[i * 3 + 1] = (x * matrix.e12 + y * matrix.e22 + z * matrix.e32) + matrix.e24;
            vertices[i * 3 + 2] = (x * matrix.e13 + y * matrix.e23 + z * matrix.e33) + matrix.e34;

            x = normals[i * 3];
            y = normals[i * 3 + 1];
            z = normals[i * 3 + 2];

            normals[i * 3] = (x * matrix.e11 + y * matrix.e21 + z * matrix.e31);
            normals[i * 3 + 1] = (x * matrix.e12 + y * matrix.e22 + z * matrix.e32);
            normals[i * 3 + 2] = (x * matrix.e13 + y * matrix.e23 + z * matrix.e33);
        }
    }

    void translate(double x, double y, double z){
        for(int i = 0; i < vertexCount; i++){
            vertices[i * 3] += x;
            vertices[i * 3 + 1] += y;
            vertices[i * 3 + 2] += z;
        }
    }
};

