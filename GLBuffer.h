#ifndef GL_BUFFER_H__
#define GL_BUFFER_H__

#include <glad/glad.h>


class GLBuffer {
public:
    explicit GLBuffer();
    ~GLBuffer();

    bool create();
    bool bind(GLuint type);
    void unBind(GLuint type);
    bool bufferData(const GLvoid * data, GLsizeiptr size, GLenum usage);
    void release();

    inline GLuint buffer() {
        return m_bufferId;
    }

    inline bool isCreated() {
        return m_created;
    }

private:
    bool m_bind;
    bool m_created;
    GLuint m_target;
    GLuint m_bufferId;
};

#endif//GL_BUFFER_H__
