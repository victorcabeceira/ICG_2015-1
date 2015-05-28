#include <SDL2/SDL.h>
#include "camera.h"

const static float StepScale = 0.1f;

float Scale = 0.0f;

Camera::Camera()
{
    m_pos    = Vector3f(0.0f, 0.0f, 0.0f);
    m_target = Vector3f(0.0f, 0.0f, 1.0f);
    m_up     = Vector3f(0.0f, 1.0f, 0.0f);
}


Camera::Camera(const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up)
{
    m_pos    = Pos;
    m_target = Target;
    m_target.Normalize();
    m_up     = Up;
    m_up.Normalize();
}


bool Camera::OnKeyboard(int Key)
{
    bool Ret = false;

    switch (Key) {

    case SDLK_UP:
        {
            m_pos += (m_target * StepScale);
            Ret = true;
        }
        break;

    case SDLK_DOWN:
        {
            m_pos -= (m_target * StepScale);
            Ret = true;
        }
        break;

    case SDLK_LEFT:
        {
            Vector3f Left = m_target.Cross(m_up);
            Left.Normalize();
            Left *= StepScale;
            m_pos -= Left;
            Ret = true;
        }
        break;

    case SDLK_RIGHT:
        {
            Vector3f Right = m_up.Cross(m_target);
            Right.Normalize();
            Right *= StepScale;
            m_pos -= Right;
            Ret = true;
        }
        break;

    }

    return Ret;
}
