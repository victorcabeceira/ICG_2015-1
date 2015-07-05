#include <iostream>
#include <math.h>
#include <cmath>
#include <GL/glew.h>

#include "pipeline.h"
#include "ogldev_camera.h"
#include "texture.h"
#include "ogldev_basic_lighting.h"
#include "ogldev_glfw_backend.h"
#include "ogldev_util.h"
#include "mesh.h"
#include <GLFW/glfw3.h>

static constexpr int WINDOW_WIDTH  = 960;
static constexpr int WINDOW_HEIGHT = 540;

#define ACELERAR true
#define FREIAR false


class Main : public ICallbacks
{
public:

    Main()
    {
        m_pGameCamera = NULL;
        m_pEffect = NULL;
        m_scale = 0.0f;
        m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
        m_directionalLight.AmbientIntensity = 1.0f;
        m_directionalLight.DiffuseIntensity = 0.01f;
        m_directionalLight.Direction = Vector3f(1.0f, 0.0f, 1.0f);
    }

    virtual ~Main()
    {
        delete m_pEffect;
        delete m_pGameCamera;
        delete m_mesh_nave;
        delete m_mesh_mapa;
        delete m_mesh_quad;
    }

    bool Init()
    {
        Vector3f Pos(-12.776764f, 6.532981f, 16.077847f);
        Vector3f Target( pos[0]+0.777163f, -0.133986f, pos[2]+(-0.614871f));
        Vector3f Up( 0.105076, 0.990983f, -0.083134f);
        m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);

        m_pEffect = new BasicLightingTechnique();

        if (!m_pEffect->Init()){
            printf("Error initializing the lighting technique\n");
            return false;
        }

        m_pEffect->Enable();

        m_pEffect->SetColorTextureUnit(0);

        m_mesh_nave = new Mesh();
        m_mesh_mapa = new Mesh();
        m_mesh_quad = new Mesh();

        // return m_mesh_nave->LoadMesh("../Content/phoenix_ugv.md2");
        const bool loaded_meshes =
            m_mesh_nave->LoadMesh("../Content/BlueFalcon/blue_falcon.obj") &&
            m_mesh_mapa->LoadMesh("../Content/Mapa/mapa.obj");
            //m_mesh_quad->LoadMesh("../Content/quad2.obj");
            // m_mesh_mapa->LoadMesh("../Content/guard/boblampclean.md5mesh");
        return loaded_meshes;
    }

    void Run()
    {
        GLFWBackendRun(this);
    }

    virtual void RenderSceneCB() override
    {
        m_pGameCamera->OnRender();

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        //m_scale = 286.5f;
        // std::cout << "scale: " << m_scale << std::endl;

        Pipeline p;
        p.Scale(1.0f, 1.0f, 1.0f);
        p.Rotate(0.0f, 0.0f, 0.0f);
        p.WorldPos(0.0f, 0.0f, 0.0f);
        //printf("%f\n",m_scale);
        p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
        p.SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);
        m_pEffect->SetWVP(p.GetWVPTrans());
        m_pEffect->SetWorldMatrix(p.GetWorldTrans());
        m_pEffect->SetDirectionalLight(m_directionalLight);
        m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());
        m_pEffect->SetMatSpecularIntensity(0.0f);
        m_pEffect->SetMatSpecularPower(0);
        m_mesh_mapa->Render();


        Vector3f man(pos[0]-10.5f, 8.0f, pos[2]+10.5f);
          m_pGameCamera->SetTarget(man);

        p.Scale(1.f, 1.f, 1.f);
        p.Rotate(0.0f, -m_scale + 180.0 , 0.0f);
        calcPosition(flag,aceleracao);
        p.WorldPos(pos[0], 1.5f, pos[2]);
        m_pEffect->SetWVP(p.GetWVPTrans());
        m_pEffect->SetWorldMatrix(p.GetWorldTrans());
        m_mesh_nave->Render();

        /*angle = atan2(pos[2],pos[0]) - atan2(posAntiga[2],posAntiga[0]);
        angle = (angle*180.f)/M_PI;
        printf ("%f\n", angle);*/
        //printf ("%f %f %f\n", pos[0], pos[1], pos[2]);

        /*p.Scale(5.0f, 0.0f, 25.0f);
        p.WorldPos(0.2f, -0.5f, 9.2f);
        m_pEffect->SetWVP(p.GetWVPTrans());
        m_pEffect->SetWorldMatrix(p.GetWorldTrans());
        m_mesh_quad->Render();*/

        GLFWBackendSwapBuffers();
    }


    virtual void KeyboardCB(OGLDEV_KEY OgldevKey) override
    {

        if(OgldevKey == OGLDEV_KEY_Q) {
            glfwSetWindowShouldClose(Window(), GL_TRUE);
        }
        else if(OgldevKey == OGLDEV_KEY_P) {
            m_directionalLight.AmbientIntensity += 0.05f;
        }
        else if(OgldevKey == OGLDEV_KEY_O) {
            m_directionalLight.AmbientIntensity -= 0.05f;
        }
        else if(OgldevKey == OGLDEV_KEY_A){
            m_scale -= 4.0f;
              if (m_scale <= -360.0f)
              m_scale /= 360.0f;
        }
        else if(OgldevKey == OGLDEV_KEY_D){
            m_scale += 4.0f;
              if (m_scale >= 360.0f)
              m_scale /= 360.0f;
        }
        else if(OgldevKey == OGLDEV_KEY_W){
            flag = ACELERAR;
            aceleracao *= 1.75;
        }
        else if(OgldevKey == OGLDEV_KEY_S){
          if(aceleracao >= 1.521){
            if(aceleracao >1.75){
              flag = ACELERAR;
              aceleracao /= 1.25;
            }
            else{
              aceleracao = 1.0;
            }
          }
          else{
            flag = FREIAR;
            aceleracao *= 1.15;
          }

        }

        /*else if(OgldevKey == OGLDEV_KEY_S){
          flag =ACELERAR;

          if(aceleracao >= 0.0){
            aceleracao /= 1.25;
          }
          else{
            aceleracao = 0.99;
          }

        }

        */
        else if(OgldevKey == OGLDEV_KEY_Z){
          flag =FREIAR;

          if(aceleracao >= 0.0){
            aceleracao *= 1.25;
          }
          else{
            aceleracao = 0.99;
          }

        }

        else if(OgldevKey == OGLDEV_KEY_R){
          pos[0] = 0;
          pos[2] = 0;

        }
      //  m_pGameCamera->OnKeyboard(OgldevKey);


/*        printf("GetPos %f,%f,%f",m_pGameCamera->GetPos().x,m_pGameCamera->GetPos().y,m_pGameCamera->GetPos().z);
        printf("GetTarget %f,%f,%f",m_pGameCamera->GetTarget().x,m_pGameCamera->GetTarget().y,m_pGameCamera->GetTarget().z);
        printf("GetUp %f,%f,%f\n",m_pGameCamera->GetUp().x,m_pGameCamera->GetUp().y,m_pGameCamera->GetUp().z);*/

        printf("aceleracao %f  \n, M_SCALE %f \n",aceleracao,m_scale);
        printf("Pos %f   %f \n",pos[0],pos[2]);

    }
    void calcPosition(bool flag,int aceleracao){
      int sinal = 1;
      if(flag == true){
        sinal = -1;
      }
      else{
        sinal = 1;
      }

      pos[0] += ((sin(M_PI * (m_scale) / 180) *.005)* sinal)*aceleracao;
      pos[2] += ((cos(M_PI * (m_scale) / 180) *.005)* sinal)*aceleracao;

    }

    virtual void PassiveMouseCB(int x, int y) override
    {
       //  m_pGameCamera->OnMouse(x, y);
    }

private:

    GLuint m_VBO;
    GLuint m_IBO;
    BasicLightingTechnique* m_pEffect;
    Mesh* m_mesh_nave;
    Mesh* m_mesh_mapa;
    Mesh* m_mesh_quad;
    Camera* m_pGameCamera;
    float m_scale=0;
    float m_front;
    bool flag;
    float aceleracao = 0.99;
//  float angle;
//    float pos[3] = {16.5,1.5,16.5};
    float pos[3] = {0.1,0.1,0.1};
    DirectionalLight m_directionalLight;
};


int main(int argc, char** argv)
{
    GLFWBackendInit(argc, argv, true, false);

    //bool GLFWBackendCreateWindow(unsigned int Width, unsigned int Height, bool isFullScreen, const char* pTitle);
    if (!GLFWBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, "Nave hardcore")) {
        return 1;
    }

    Main* pApp = new Main();

    if (!pApp->Init()) {
        return 1;
    }

    pApp->Run();

    delete pApp;

    return 0;
}
