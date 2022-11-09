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
    double *verticesBox = new double[72];
    double *texCoordsBox = new double[72];

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
        
        box();
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

        for(int i = 0; i < 36; i++){
            x = verticesBox[i * 3];
            y = verticesBox[i * 3 + 1];
            z = verticesBox[i * 3 + 2];

            verticesBox[i * 3] = x * matrix.e11 + y * matrix.e21 + z * matrix.e31;
            verticesBox[i * 3 + 1] = x * matrix.e12 + y * matrix.e22 + z * matrix.e32;
            verticesBox[i * 3 + 2] = x * matrix.e13 + y * matrix.e23 + z * matrix.e33;
        }
        //box();
    }

    void localTransform(const Matrix44d& matrix){
        double x, y, z, x2, y2, z2;
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

        for(int i = 0; i < 24; i++){
            x = verticesBox[i * 3] - matrix.e14;
            y = verticesBox[i * 3 + 1] - matrix.e24;
            z = verticesBox[i * 3 + 2] - matrix.e34;

            verticesBox[i * 3] = (x * matrix.e11 + y * matrix.e21 + z * matrix.e31) + matrix.e14;
            verticesBox[i * 3 + 1] = (x * matrix.e12 + y * matrix.e22 + z * matrix.e32) + matrix.e24;
            verticesBox[i * 3 + 2] = (x * matrix.e13 + y * matrix.e23 + z * matrix.e33) + matrix.e34;
        }

        //box();
    }

    void translate(double x, double y, double z){
        for(int i = 0; i < 24; i++){
            vertices[i * 3] += x;
            vertices[i * 3 + 1] += y;
            vertices[i * 3 + 2] += z;
        }
        box();
    }

    void box(){
        double minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;
        for (size_t i = 0; i < vertexCount; i++){
            if (vertices[i * 3] < minX) {
                minX = vertices[i * 3];
            } else if (vertices[i * 3] > maxX) {
                maxX = vertices[i * 3];
            } 
               
            if (vertices[i * 3 + 1] < minY) {
                minY = vertices[i * 3 + 1];
            } else if (vertices[i * 3 + 1] > maxY) {
                maxY = vertices[i * 3 + 1];
            }      
            
            if (vertices[i * 3 + 2] < minZ) {
                minZ = vertices[i * 3 + 2];
            } else if (vertices[i * 3 + 2] > maxZ) {
                maxZ = vertices[i * 3 + 2];
            }
            
        }

        //double *verticesBoxTemp = new double[24] {0.500000, 0.500000, -0.500000, 0.500000, -0.500000, -0.500000, 0.500000, 0.500000, 0.500000, 0.500000, -0.500000, 0.500000, -0.500000, 0.500000, -0.500000, -0.500000, -0.500000, -0.500000, -0.500000, 0.500000, 0.500000, -0.500000, -0.500000, 0.500000};
        double *verticesBoxTemp = new double[24];
        //double *texCoordsBoxTemp = new double[32] {0.000000, 1.000000, 1.000000, 0.000000, 1.000000, 1.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 1.000000, 1.000000, 0.000000, 1.000000, 0.000000, 0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000, 1.000000};
        int *facesBox = new int[36] {5, 3, 1, 3, 8, 4, 7, 6, 8, 2, 8, 6, 1, 4, 2, 5, 2, 6, 5, 7, 3, 3, 7, 8, 7, 5, 6, 2, 4, 8, 1, 3, 4, 5, 1, 2}; 
        //int *coordBox = new int[36] {1, 2, 3, 4, 5, 6, 7, 8, 5, 9, 5, 10, 3, 11, 12, 1, 12, 13, 1, 14, 2, 4, 7, 5, 7, 15, 8, 9, 6, 5, 3, 16, 11, 1, 3, 12};     

        verticesBoxTemp[0] = maxX;
        verticesBoxTemp[0 * 3 + 1] = maxY;
        verticesBoxTemp[0 * 3 + 2] = minZ;

        verticesBoxTemp[1 * 3] = maxX;
        verticesBoxTemp[1 * 3 + 1] = minY;
        verticesBoxTemp[1 * 3 + 2] = minZ;

        verticesBoxTemp[2 * 3] = maxX;
        verticesBoxTemp[2 * 3 + 1] = maxY;
        verticesBoxTemp[2 * 3 + 2] = maxZ;


        verticesBoxTemp[3 * 3] = maxX;
        verticesBoxTemp[3 * 3 + 1] = minY;
        verticesBoxTemp[3 * 3 + 2] = maxZ;

        verticesBoxTemp[4 * 3] = minX;
        verticesBoxTemp[4 * 3 + 1] = maxY;
        verticesBoxTemp[4 * 3 + 2] = minZ;

        verticesBoxTemp[5 * 3] = minX;
        verticesBoxTemp[5 * 3 + 1] = minY;
        verticesBoxTemp[5 * 3 + 2] = minZ;

        verticesBoxTemp[6 * 3] = minX;
        verticesBoxTemp[6 * 3 + 1] = maxY;
        verticesBoxTemp[6 * 3 + 2] = maxZ;

        verticesBoxTemp[7 * 3] = minX;
        verticesBoxTemp[7 * 3 + 1] = minY;
        verticesBoxTemp[7 * 3 + 2] = maxZ;



        for (size_t i = 0; i < 24; i++) {
            int indv = (facesBox[i] - 1) * 3;
            //int indt = (coordBox[i] - 1) * 2;
            verticesBox[i * 3] = verticesBoxTemp[indv];
            verticesBox[i * 3 + 1] = verticesBoxTemp[indv + 1];
            verticesBox[i * 3 + 2] = verticesBoxTemp[indv + 2];

            //texCoordsBox[i * 2] = texCoordsBoxTemp[indt];
            //texCoordsBox[i * 2 + 1] = texCoordsBoxTemp[indt + 1];
        }
    }

    void drawBox(){
        glEnableClientState(GL_VERTEX_ARRAY);
        //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, verticesBox);
        //glTexCoordPointer(2, GL_DOUBLE, 0, texCoordsBox);
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glDrawArrays(GL_TRIANGLES, 0, 24);
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
};

