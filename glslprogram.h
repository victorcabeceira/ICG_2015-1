#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H


namespace GLSLShader {
    enum GLSLShaderType {
        VERTEX, FRAGMENT, GEOMETRY,
        TESS_CONTROL, TESS_EVALUATION
    };
};

class GLSLProgram
{
private:
    int  handle;
    bool linked;
    string logString;

    int  getUniformLocation(const char * name );
    bool fileExists( const string & fileName );

public:
    GLSLProgram();

    bool   compileShaderFromFile( const char * fileName, GLSLShader::GLSLShaderType type );
    bool   compileShaderFromString( const string & source, GLSLShader::GLSLShaderType type );
    bool   link();
    bool   validate();
    void   use();

    string log();

    int    getHandle();
    bool   isLinked();

    void   bindAttribLocation( GLuint location, const char * name);
    void   bindFragDataLocation( GLuint location, const char * name );

};

#endif // GLSLPROGRAM_H
