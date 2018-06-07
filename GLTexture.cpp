#include "GLTexture.h"

GLTexture2D::GLTexture2D() : GLTexture()
{
    m_texture = 0;
    m_bind = false;
    m_target = GL_TEXTURE_2D;
}

bool GLTexture2D::create()
{
    glGenTextures(1, &m_texture);
    return m_texture > 0;
}

bool GLTexture2D::bind(bool is_bind)
{   if( m_bind ){
        if( !is_bind ){
            glBindTexture(m_target, 0);
            m_bind = false;
        }
        return true;
    }else if( m_texture > 0 ){
        if( is_bind ){
            m_bind = true;
            glBindTexture(m_target, m_texture);
        }
        return true;
    }

    return false;
}

bool GLTexture2D::genMipmap()
{
    if( m_bind ){
        glGenerateMipmap(m_target);
        return true;
    }
    return false;
}

bool GLTexture2D::loadImage(const char *imgName)
{
    if( m_texture == 0 || !m_bind ){
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
