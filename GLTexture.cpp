#include "GLTexture.h"

GLTexture::GLTexture(GLuint target)
{
    m_texture = 0;
    m_bind = false;
    m_target = target;
}

bool GLTexture::create()
{
    if( m_texture ){
        return false;
    }

    glGenTextures(1, &m_texture);
    if( m_texture == 0 ){
        return false;
    }

    return true;
}

bool GLTexture::bind()
{
    if( !m_texture ){
        return false;
    }
    glBindTexture(m_target, m_texture);
    m_bind = true;

    return true;
}

void GLTexture::unbind()
{
    glBindTexture(m_target, 0);
    m_bind = false;
}

bool GLTexture::genMipmap()
{
    if( m_bind ){
        glGenerateMipmap(m_target);
        return true;
    }
    return false;
}

bool GLTexture::loadImage(const char *imgName)
{
    if( !m_texture || !m_bind ){
        return false;
    }

    SDL_Surface* img = IMG_Load(imgName);
    if( !img ){
        return false;
    }

    glTexImage2D(m_target, 0, GL_RGB, img->w, img->h, 0,
                    GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*)img->pixels);

    SDL_FreeSurface(img);

    return true;
}
