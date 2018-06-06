#ifndef GLSHADER_H__
#define GLSHADER_H__

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class GLShader {
public:
    bool loadShader(GLuint type, const string& shaderSource);
    bool loadShaderFile(GLuint type, const string& file);
    bool compile();
    bool createProgram();
    bool attach();
    void detach();
    bool link();
    bool use(bool use_it = true);
    void freeShader();
    void freeProgram();
    GLuint program() const;
    GLShader();
    ~GLShader();

private:
    bool m_linked;
    bool m_compiled;
    bool m_attached;
    bool m_used;
    GLuint m_vertShader;
    GLuint m_fragShader;
    GLuint m_shaderProgram;
    vector<string> m_vertShaders;
    vector<string> m_fragShaders;
};

#endif  // GLSHADER_H__
