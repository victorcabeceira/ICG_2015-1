#include "CG.h"

GerenciadorGrafico::GerenciadorGrafico(int largura, int altura)
{
    SDL_Init(SDL_INIT_VIDEO);
    this->flags = SDL_WINDOW_OPENGL;

	  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	  SDL_CreateWindowAndRenderer(largura, altura, this->flags,&this->janela, &this->render);
	  SDL_GL_CreateContext(this->janela);
    this->iniciarGL();

}

GerenciadorGrafico::~GerenciadorGrafico()
{
    SDL_Quit();
}

void
GerenciadorGrafico::iniciarGL()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
}

int
GerenciadorGrafico::setViewPort(int largura, int altura)
{
    if (altura == 0 ) altura = 1;

    glViewport( 0, 0, (GLsizei) largura, (GLsizei) altura);

    return 1;
}

void
GerenciadorGrafico::delay(int tempo)
{
	  SDL_Delay(tempo);
}

void
GerenciadorGrafico::iniciarRender()
{
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void
GerenciadorGrafico::displayRender()
{
  	SDL_GL_SwapWindow(this->janela);
}
