#ifndef VEC_H
#define VEC_H
#include <GL/gl.h>

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

struct Shader
{
  const char* filename;
  GLenum type;
  GLchar* source;
  GLuint a;

  Shader(){}

  Shader(const char* _filename, GLenum _type, GLchar* _source)
  {
    filename = _filename;
    type = _type;
    source = _source;
  }

};

#endif

