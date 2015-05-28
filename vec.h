/*! \class vec
    \brief Classe de estrutura de dados da aplicação
 Classe Destinada a criação e gerenciamento da estrutura de dados da aplicação.
*/#ifndef VEC_H
#define VEC_H

#include <string>

using namespace std;

/*struct Vertex
{
    Vector3f m_pos;
    Vector2f m_tex;
    Vector3f m_normal;

    Vertex() {}

    Vertex(Vector3f pos, Vector2f tex)
    {
        m_pos = pos;
        m_tex = tex;
	m_normal = Vector3f(0.0f, 0.0f, 0.0f);
    }
};
*/
struct Vertex
{
  float position[3];
  int color[4];

  Vertex(float x, float y, float z, int r=0, int g=0, int b=0, int a=0)
  {
    position[0] = x;
    position[1] = y;
    position[2] = z;

    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
  }

};

struct Vertex2D
{
  float position[2];

  Vertex2D(float x=0, float y=0)
  {
    position[0] = x;
    position[1] = y;
  }
};
struct Material
{
  int illum, imageID, imageWidth, imageHeight;
  GLuint textureID;
  unsigned char* imageData;
  string name;
  string fileName;
  float ns, ni, d, tr, tf[3];
  float ka[3], kd[3], ks[3], ke[3];

  Material() {};
};

#endif
