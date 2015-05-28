
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "ogldev_util.h"
#include "pipeline.h"
#include "camera.h"
#include "ogldev_texture.h"
#include "math_3d.h"
#include "lighting_technique.h"
#include "mesh.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

SDL_Window* displayWindow;



GLuint VBO;
GLuint IBO;
GLuint gWVPLocation;
GLuint gSampler;
Texture* pTexture = NULL;
Camera GameCamera;
PersProjInfo m_persProjInfo;
//01 - Adicione o tipo de luz na estrutura de dados
DirectionalLight m_directionalLight;

LightingTechnique* m_pEffect;

Pipeline p;

const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";


static void RenderSceneCB(Mesh mesh)
{

    glClear(GL_COLOR_BUFFER_BIT);

    static float Scale = 0.0f;

    Scale += 0.1f;


    p.WorldPos(0.0f, 0.0f, 3.0f);
    p.SetCamera(GameCamera.GetPos(), GameCamera.GetTarget(), GameCamera.GetUp());
    p.SetPerspectiveProj(m_persProjInfo);
    m_pEffect->SetWVP(p.GetWVPTrans());
    m_pEffect->SetDirectionalLight(m_directionalLight);


    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh), (const GLvoid*)12);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh), (const GLvoid*)20);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    pTexture->Bind(GL_TEXTURE0);
    //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_TRIANGLES, mesh.getIndice().size(), GL_UNSIGNED_INT,0 );
    glDrawArrays(GL_LINES, 0, mesh.getVertex().size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    SDL_GL_SwapWindow(displayWindow);
}
void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount,
                     Mesh* pVertices, unsigned int VertexCount)
    {
        /* Não precisa pois o arquivo dará
        // Accumulate each triangle normal into each of the triangle vertices
        for (unsigned int i = 0 ; i < IndexCount ; i += 3) {
            unsigned int Index0 = pIndices[i];
            unsigned int Index1 = pIndices[i + 1];
            unsigned int Index2 = pIndices[i + 2];
            Vector3f v1 = pVertices[Index1].m_pos - pVertices[Index0].m_pos;
            Vector3f v2 = pVertices[Index2].m_pos - pVertices[Index0].m_pos;
            Vector3f Normal = v1.Cross(v2);
            Normal.Normalize();

            //soma a normal de cada vertice
            pVertices[Index0].m_normal += Normal;
            pVertices[Index1].m_normal += Normal;
            pVertices[Index2].m_normal += Normal;
        }

        // Normalize all the vertex normals
        for (unsigned int i = 0 ; i < VertexCount ; i++) {
            pVertices[i].m_normal.Normalize();
        }*/
    }

static void CreateVertexBuffer(Mesh mesh)
{

 	//CalcNormals(Indices, ARRAY_SIZE_IN_ELEMENTS(Indices), mesh, ARRAY_SIZE_IN_ELEMENTS(Vertices));
 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.getVertex().size() * sizeof(Vertex), &mesh.getVertex()[0], GL_STATIC_DRAW);
}


static void CreateIndexBuffer(Mesh mesh)
{


    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndice().size() * sizeof(unsigned int), &mesh.getIndice()[0], GL_STATIC_DRAW);
}


static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(1);
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(ShaderProgram, ShaderObj);
}


static void CompileShaders()
{
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

    AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

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

    gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
    assert(gWVPLocation != 0xFFFFFFFF);
    gSampler = glGetUniformLocation(ShaderProgram, "gSampler");
    assert(gSampler != 0xFFFFFFFF);
}



 /* La�o principal */
int
main(int argc, char* argv[])
{
  Mesh mesh;
      SDL_Init(SDL_INIT_VIDEO);

    SDL_Renderer* displayRenderer;

	int flags = SDL_WINDOW_OPENGL;

	atexit(SDL_Quit);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_CreateWindowAndRenderer(1024, 768, flags,&displayWindow, &displayRenderer);

	SDL_GL_CreateContext(displayWindow);
    GLenum res = glewInit();
	if (glewIsSupported("GL_VERSION_3_3"))
		printf("Ready for OpenGL 3.3\n");
	else {
		printf("OpenGL 3.3 not supported\n");
		exit(1);
	}
    if (res != GLEW_OK) {
      fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    if(argc != 2){
        cout << "Deve-se passar o nome do arquivo .off juntamente com o nome do programa!!!" << endl;
        exit(-1);
    }
    /*mesh = new Mesh();
      mesh->carregarArquivo(fileName);
      mesh->prepareAllTexture();
      mesh->redimensionar();

      mesh->resize(scaleResize / mesh->getDeltaY());
      mesh->setPosition(x, y, z);
      mesh->rotateY(angleY);
    */

    mesh.carregarArquivo(argv[1]);
    mesh.transladar();
    mesh.redimensionar();


    CreateVertexBuffer(mesh);
    CreateIndexBuffer(mesh);
    CompileShaders();

 glUniform1i(gSampler, 0);
   m_persProjInfo.FOV = 60.0f;
   m_persProjInfo.Height = WINDOW_HEIGHT;
   m_persProjInfo.Width = WINDOW_WIDTH;
   m_persProjInfo.zNear = 1.0f;
   m_persProjInfo.zFar = 100.0f;

   m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
   m_directionalLight.AmbientIntensity = 0.5f;
   m_directionalLight.DiffuseIntensity = 1.0f;
   m_directionalLight.Direction = Vector3f(0.5f, 0.5f, 1.0f);

 m_pEffect = new LightingTechnique();

      if (!m_pEffect->Init())
        {
            return false;
        }

        m_pEffect->Enable();

        m_pEffect->SetTextureUnit(0);
    pTexture = new Texture(GL_TEXTURE_2D, "test.bmp");

    if (!pTexture->Load()) {
        return 1;
    }

	SDL_Event e;
	bool quit = false;
  float Scale = 0.0f;
  while (!quit){
    while (SDL_PollEvent(&e)){
      if (e.type == SDL_QUIT){
      quit = true;
      }
      if(e.type == SDL_KEYDOWN){

        GameCamera.OnKeyboard(e.key.keysym.sym);

        switch (e.key.keysym.sym){
          case SDLK_4:
              {
                Scale -= 1.5f;
                p.Rotate(0.0f, Scale, 0.0f);
              }
              break;
        case SDLK_6:
                {
                    Scale += 1.5f;
                    p.Rotate(0.0f, Scale, 0.0f);
                  }
                  break;

        case SDLK_0:
                    {
                      m_directionalLight.AmbientIntensity += 0.05f;
                      }
                      break;


      case SDLK_1:
                      {
                      m_directionalLight.AmbientIntensity -= 0.05f;
                      }
                      break;

      case SDLK_F1:
                                {
                                  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                                }
                                break;
                          }

      }




    }
  RenderSceneCB(mesh);
         SDL_Delay(50);
  }


    SDL_Quit();

    return 0;
}
