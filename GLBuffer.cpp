#include <GLBuffer.h>


GLBuffer::GLBuffer()
{
    m_created = false;
    m_bind = false;
    m_target = 0;
    create();
}

GLBuffer::~GLBuffer()
{
    release();
}

bool GLBuffer::create()
{
    if( m_created ){
        return false;
    }

    glGenBuffers(1, &m_bufferId);
    if( 0 == m_bufferId ){
        return false;
    }

    m_created = true;

    return true;
}

bool GLBuffer::bind(GLuint target)
{
    if( !m_created ){
        return false;
    }

    m_bind = true;
    m_target = target;
    glBindBuffer(target, m_bufferId);

    return true;
}

void GLBuffer::unBind(GLuint type)
{
    glBindBuffer(type, 0);
}

bool GLBuffer::bufferData(const GLvoid *data, GLsizeiptr size, GLenum usage)
{
    if( !m_created ){
        return false;
    }

    if( !m_bind ){
        m_bind = true;
        bind(m_target);
    }

    glBufferData(m_target, size, data, usage);

    return true;
}

void GLBuffer::release()
{
    if( !m_created ){
        return;
    }

    glDeleteBuffers(1, &m_bufferId);
    m_bufferId = 0;
    m_bind = false;
    m_created = false;
    m_target = 0;
}
