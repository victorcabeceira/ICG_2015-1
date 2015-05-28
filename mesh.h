/*! \class mesh
    \brief Classe Mesh
 Classe Destinada a parte de textura,
 contando com cálculo de delta e imagem da textura.
*/
#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

#include "vec.h"


class Mesh
{
  public:

    Mesh();
    ~Mesh();

    void carregarArquivo(string nomeArquivo);
    void redimensionar();
    void normalizar();
    void transladar();


    vector<Vertex> getVertex();
    vector<unsigned int> getIndice();

  private:
    void carregarMaterial(string nomeArquivo);
    string getPath(string fileName);
    int loadImage(string imageName);
    double encontrarDeltaX();
    double encontrarDeltaY();
    double encontrarDeltaZ();

    double deltaX, deltaY, deltaZ, xMin, yMin, zMin;
    int qtdPontos, qtdArestas, qtdTextura;
    vector<Vertex> vertex;
    vector<Vertex> normal;
    vector<Vertex2D> texture;
    vector<unsigned int> vertexIndex;
    vector<unsigned int> normalIndex;
    vector<unsigned int> textureIndex;
    vector<unsigned int> indice;
    string fileMtl;
    string fileName;
    vector<Material> material;
    SDL_Surface * m_pImage;
    std::string m_fileName;

};

#endif
