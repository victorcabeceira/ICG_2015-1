/*! \class technique
    \brief Classe de técnicas da aplicação
 Classe Destinada ao gerenciamento e utilização do shader da aplicação e os objetos.
*/
#ifndef TECHNIQUE_H
#define	TECHNIQUE_H

#include <list>
#include <GL/glew.h>

class Technique
{
public:

    Technique();

    virtual ~Technique();

    virtual bool Init();

    void Enable();

protected:

    bool AddShader(GLenum ShaderType, const char* pFilename);

    bool Finalize();

    GLint GetUniformLocation(const char* pUniformName);

    GLint GetProgramParam(GLint param);

    GLuint m_shaderProg;

private:

    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;
};

#endif	/* TECHNIQUE_H */

