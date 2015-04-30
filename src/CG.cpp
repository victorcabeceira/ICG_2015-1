#include "CG.h"

//Inicialização da janela SDL/Inicia OpenGL
GerenciadorGrafico::GerenciadorGrafico(int largura, int altura)
{
 // Seu código vem aqui

}

GerenciadorGrafico::~GerenciadorGrafico()
{
 // Seu código vem aqui

}

void 
GerenciadorGrafico::iniciarGL()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
}

//Atualiza a viewport da tela
int 
GerenciadorGrafico::setViewPort(int largura, int altura)
{
  // Seu código vem aqui
  
}

//Delay - 
void 
GerenciadorGrafico::delay(int tempo)
{
 // Seu código vem aqui

}

// Inicia Buffers OpenGL (glClear) e crear color
void 
GerenciadorGrafico::iniciarRender()
{
 // Seu código vem aqui
	
}

void 
GerenciadorGrafico::displayRender()
{
  	SDL_GL_SwapWindow(this->janela);
}

