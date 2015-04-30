#ifndef CG_H
#define CG_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

class GerenciadorGrafico
{
  public:
    
    GerenciadorGrafico(int largura=800, int altura=600);
    ~GerenciadorGrafico();

    void iniciarGL();
    int setViewPort(int,int);
    void delay(int);

    void iniciarRender();
    void displayRender();

  private:

    SDL_Window* janela;
    SDL_Renderer* render;
    int flags;
};

#endif

