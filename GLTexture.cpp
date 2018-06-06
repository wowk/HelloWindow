#include "GLTexture.h"

GLTexture2D::GLTexture2D(const char *imgName) : GLTexture()
{
    m_textures = nullptr;
    m_bind = false;
    m_target = GL_TEXTURE_2D;

    if( !imgName ){
        return;
    }

    create();
}

void GLTexture2D::create()
{

}

bool GLTexture2D::loadImage(const char *imgName)
{

}
