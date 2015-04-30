#include "shader.h"
#include <iostream>
using namespace std;

GerenciadorShader::GerenciadorShader(){}

void
GerenciadorShader::setVertexShader(const char* vertex)
{
  this->shaders[0] = Shader(vertex, GL_VERTEX_SHADER, NULL);
}

void
GerenciadorShader::setFragmentShader(const char* fragment)
{
  this->shaders[1] = Shader(fragment, GL_FRAGMENT_SHADER, NULL);
}

void
GerenciadorShader::setVertex(vector<Vertex> vertex)
{
  this->buffer = vertex;
}

void
GerenciadorShader::setIndice(vector<unsigned int> indice)
{
  this->indice = indice;
}

// Lê o arquivo do shader e retorna o buffer com a string do código fonte
char*
GerenciadorShader::readShaderSource(const char* shaderFile)
{
 // Seu código vem aqui
  GLuint ShaderProgram = glCreateProgram();

    if (ShaderProgram == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }
    
    string vs, fs;

    if (!ReadFile(pVSFileName, vs)) {
        exit(1);
    };

    if (!ReadFile(pFSFileName, fs)) {
        exit(1);
    };

    initShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
   	initShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
	}

    glValidateProgram(ShaderProgram);
    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glUseProgram(ShaderProgram);
}

// Inicia shader: compila arquivos de shader, linkas shaders, e altera o pipeline grafico com a inserção dos shaders 
GLuint
GerenciadorShader::initShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
  GLuint program = glCreateProgram(ShaderType);
  glUseProgram(program);

      if (program == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(program, 1, p, Lengths);
    glCompileShader(program);
    GLint success;
    glGetShaderiv(program, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(program, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, program);


  return program;
}

void
GerenciadorShader::criarVertexArray()
{
 	 // Seu código vem aqui
}

void
GerenciadorShader::criarBufferDeVertex()
{
 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.getVertex().size() * sizeof(Vertex), &mesh.getVertex()[0], GL_STATIC_DRAW);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndice().size() * sizeof(unsigned int), &mesh.getIndice()[0], GL_STATIC_DRAW);



}

void
GerenciadorShader::criarBufferDeIndex()
{
 // Seu código vem aqui

}

void
GerenciadorShader::renderizarCena()
{
 glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDisableVertexAttribArray(0);

    SDL_GL_SwapWindow(displayWindow);

}

