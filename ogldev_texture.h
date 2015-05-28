/*! \class ogldev_texture
    \brief Classe de textura
 Classe Destinada a parte de Gerenciamento de textura dos objetos da aplicação.
*/
#ifndef TEXTURE_H
#define	TEXTURE_H

#include <string>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture
{
public:
    Texture(GLenum TextureTarget, const std::string& FileName);

    bool Load();

    void Bind(GLenum TextureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    SDL_Surface * m_pImage;
};


#endif	/* TEXTURE_H */
