#pragma once

#include <vector>
#include <string>

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
    vector<double> verticesFile;  ///< Sommets.
    vector<double> texCoordsFile; ///< Coordonnées de texture.
    vector<double> normalsFile;   ///< Normales.
    vector<int> faces;   ///< Faces.

public:
    Mesh(const char* filename, const string& textureName){
        ifstream file;
        string line;
        double x, y, z;
        double vt1, vt2;
        string face;
        string f1, f2, f3;
        file.open(filename);
        if (file.is_open()){
            while (file.tellg() != -1){
                file >> line;
                if (line == "v"){
                    file >> x >> y >> z;
                    verticesFile.push_back(x);
                    verticesFile.push_back(y);
                    verticesFile.push_back(z);
                    
                } else if (line.compare("vt") == 0){
                    file >> vt1 >> vt2;
                    texCoordsFile.push_back(vt1);
                    texCoordsFile.push_back(vt2);
                } else if (line.compare("vn") == 0){
                    file >> x >> y >> z;
                    normalsFile.push_back(x);
                    normalsFile.push_back(y);
                    normalsFile.push_back(z);
                } else if (line.compare("f") == 0){
                    for (size_t i = 0; i < 3; i++)
                    {
                        file >> face;
                        f1 = face.substr(0, face.find("/"));
                        f2 = face.substr(face.find_first_of("/") + 1, face.find_last_of("/") - (face.find_first_of("/") + 1));
                        f3 = face.substr(face.find_last_of("/") + 1, face.length() - (face.find_last_of("/") + 1));
                        printf("%s %s %s", f1.c_str(), f2.c_str(), f3.c_str());
                        faces.push_back(stoi(f1));
                        faces.push_back(stoi(f2));
                        faces.push_back(stoi(f3));
                    }
                    
                    
                } else {
                    file.ignore(50, 10);
                }
            }
            
        }
        file.close();


        vertexCount = faces.size() / 3;
        this->vertices = new double[vertexCount * 3];
        this->texCoords = new double[vertexCount * 2];
        this->normals = new double[vertexCount * 3];

        int indv, indt, indn;

        for (size_t i = 0; i < vertexCount; i++)
        {

            indv = (faces[i * 3] - 1) * 3;
            indt = (faces[i * 3 + 1] - 1) * 2;
            indn = (faces[i * 3 + 2] - 1) * 3;

            vertices[i * 3] = verticesFile[indv];
            vertices[i * 3 + 1] = verticesFile[indv + 1];
            vertices[i * 3 + 2] = verticesFile[indv + 2];
            

            texCoords[i * 2] = texCoordsFile[indt];
            texCoords[i * 2 + 1] = texCoordsFile[indt + 1];

            normals[i * 3] = normalsFile[indn];
            normals[i * 3 + 1] = normalsFile[indn + 1];
            normals[i * 3 + 2] = normalsFile[indn + 2];
        }
        
        this->textureId = ResourcesManager::getResource<Texture>(textureName)->getId();
    }

    ~Mesh(){
        delete[] this->vertices;
        delete[] this->texCoords;
        delete[] this->normals;
    }

    void draw(){
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
        glNormalPointer(GL_DOUBLE, 0, normals);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

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

