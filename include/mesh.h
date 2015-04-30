
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "vec.h"

using namespace std;

class Mesh
{
  public:

    Mesh();
    ~Mesh();

    void carregarArquivo(string nomeArquivo);
    void redimensionar();
    void normalizar();
    void transladar();
		Vertex calcularNormal(Vertex a, Vertex b, Vertex c);
    vector<Vertex> getVertex();
    vector<unsigned int> getIndice();

  private:

    double encontrarDeltaX();
    double encontrarDeltaY();
    double encontrarDeltaZ();

    double deltaX, deltaY, deltaZ, xMin, yMin, zMin;
    int qtdPontos, qtdArestas, qtdTextura;
    vector<Vertex> vertex;
    vector<unsigned int> indice;
};

#endif

