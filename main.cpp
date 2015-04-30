#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "include/vec.h"
#include "include/CG.h"
#include "include/shader.h"



int main(int argc, char* argv[])
{
  vector<Vertex> vertex;
  
  GerenciadorGrafico gerenciador;
   
   vertex.push_back(Vertex(-0.5f, -0.5f, 0.0f, 255,0,0,255));
   
   vertex.push_back(Vertex(0.5f, -0.5f, 0.0f, 255,0,0,255));
   vertex.push_back(Vertex(0.0f, 0.5f, 0.0f, 255,0,0,255));

  gerenciador.setViewPort(800, 600);
  gerenciador.iniciarRender();

  //glewInit();

  GerenciadorShader shader;

  shader.setVertexShader("vertex.glsl");
  shader.setFragmentShader("fragment.glsl");
//  shader.setVertex(return vertex->vertex;);
//  shader.setVertex Vertices.position[1]);
//  shader.setVertex( Vertices.position[2]);

  GLuint program = shader.initShader();
  cout<< "TUDO OK!" << endl;
  glUseProgram(program);
  glClearColor(1.0, 1.0, 1.0, 1.0);

  shader.criarVertexArray();
  shader.criarBufferDeVertex();
  shader.criarBufferDeIndex();

  shader.renderizarCena();
  gerenciador.displayRender();
  gerenciador.delay(2000);

  return 0;
}

