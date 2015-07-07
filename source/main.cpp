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
        m_scale = -90.0f;
        rotatecheck =0.0;
        maxspeed = 45;
        range = 4;
        checkpoint_x = listaCheckpoint[0][0];
        checkpoint_z = listaCheckpoint[0][1];
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
        delete m_mesh_checkpoint;
    }

    bool Init()
    {
        Vector3f Pos(2.109013,  8.000000, -1.613770);
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
        m_mesh_checkpoint = new Mesh();

        const bool loaded_meshes =
            m_mesh_nave->LoadMesh("../Content/BlueFalcon/blue_falcon.obj") &&
            m_mesh_mapa->LoadMesh("../Content/Mapa/mapa.obj")&&
            m_mesh_checkpoint->LoadMesh("../Content/quad_r.obj");
        return loaded_meshes;
    }

    void Run()
    {
        GLFWBackendRun(this);
    }

    virtual void RenderSceneCB() override{
        RotateCheckpoint();
        m_pGameCamera->OnRender();

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);



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
        m_pEffect->SetMatSpecularIntensity(5.0f);
        m_pEffect->SetMatSpecularPower(5);
        m_mesh_mapa->Render();

        p.Scale(1.f, 1.f, 1.f);

        if(pos[0] >= 50 ){
          pos[0]=50 ;

        }
        else if(pos[2]>= 23.3){
          pos[2]= 23.3;
        }
        else if(pos[2]<= -14.4){
          pos[2]= -14.4;
        }
        else if(pos[0]<= -12.7){
          pos[0]= -12.7;
        }

        Vector3f man(pos[0]-7.5f, 5.0f, pos[2]+7.5f);
          m_pGameCamera->SetTarget(man);

        p.Rotate(0.0f, -m_scale + 180.0 , 0.0f);
        calcPosition(flag,aceleracao);
        p.WorldPos(pos[0], 1.5f, pos[2]);

        m_pEffect->SetWVP(p.GetWVPTrans());
        m_pEffect->SetWorldMatrix(p.GetWorldTrans());
        m_pEffect->SetDirectionalLight(m_directionalLight);
        m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());
        m_pEffect->SetMatSpecularIntensity(5.0f);
        m_pEffect->SetMatSpecularPower(5);
       m_mesh_nave->Render();


        //printf ("%f %f %f\n", pos[0], pos[1], pos[2]);

        p.Scale(0.01f, 0.01f, 0.01f);
        //p.WorldPos(44.477566, 2.5f,-2.851082);
        DetectaCheckpoint();
        p.WorldPos(checkpoint_x, 2.2f,checkpoint_z);

        p.Rotate(0.0f,rotatecheck,0.0f);
        m_pEffect->SetWVP(p.GetWVPTrans());
        m_pEffect->SetWorldMatrix(p.GetWorldTrans());
        m_mesh_checkpoint->Render();
        //printf("checkpoint_x  %f  checkpoint_z  %f  \n",checkpoint_x,checkpoint_z);

        GLFWBackendSwapBuffers();
    }

    void RotateCheckpoint(){
      rotatecheck += 0.5;
        if (m_scale >= 360.0f)rotatecheck /= 360.0f;

    }
    void DetectaCheckpoint(){
    int laps = 0;
      for(int linha = 0; linha <5 ;linha++){
        if(linha < 5){
          if(pos[0]>=listaCheckpoint[linha][0] && pos[0] <= listaCheckpoint[linha][0]+range &&
             pos[2]>=listaCheckpoint[linha][1] && pos[2]<=listaCheckpoint[linha][1] +range  ){
            checkpoint_x = listaCheckpoint[linha+1][0];
            checkpoint_z = listaCheckpoint[linha+1][1];
            //printf("linha %d",linha);
         }
        }
        else {

            linha =0;
            checkpoint_x = listaCheckpoint[linha][0];
            checkpoint_z = listaCheckpoint[linha][1];
            }

    }


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
            m_scale -= 5.0f;
              if (m_scale <= -360.0f)
              m_scale /= 360.0f;
        }
        else if(OgldevKey == OGLDEV_KEY_D){
            m_scale += 5.0f;
              if (m_scale >= 360.0f)
              m_scale /= 360.0f;
        }
        else if(OgldevKey == OGLDEV_KEY_W){
            if(aceleracao >= maxspeed){
              aceleracao = maxspeed;
            }
            else{
              flag = ACELERAR;
              aceleracao *= 1.5;

            }

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
          pos[0] = 11.5;
          pos[2] = -11;

        }

        printf("aceleracao %f  \n, M_SCALE %f \n",aceleracao,m_scale);
        printf("Pos %f  %f  %f \n",pos[0],pos[1],pos[2]);


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
    Mesh* m_mesh_checkpoint;
    Camera* m_pGameCamera;
    int maxspeed;
    float checkpoint_x;
    float checkpoint_z;
    float m_scale;
    float m_front;
    bool flag;
    float aceleracao = 0.99;
    float rotatecheck;
    float listaCheckpoint[6][2]={
                                {45,1.5},
                                {20.5,20.5},
                                {6.8,19.3},
                                {-10,-7},
                                {11, -12.1},
                                {45, 1.5}
                                };

    int range;

    float pos[3] = {12.613994,0.1,-12.114205};
    DirectionalLight m_directionalLight;
};


int main(int argc, char** argv)
{
    GLFWBackendInit(argc, argv, true, false);

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
