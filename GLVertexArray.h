#ifndef GL_VERTEX_ARRAY_H__
#define GL_VERTEX_ARRAY_H__

#include <glad/glad.h>

class GLVertexArray {
public:
    bool create();
    bool bind(bool is_bind);
    bool bufferData();
    bool setVertexAttribArray();
    bool enableVertexAttribArray(GLuint idx);

private:
    GLuint m_vao;
    GLuint m_vbo;
};

#endif//GL_VERTEX_ARRAY_H__
