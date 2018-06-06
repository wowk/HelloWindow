#ifndef GLTEXTURE_H__
#define GLTEXTURE_H__

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class GLTexture2D {
public:
    GLTexture2D(const char* imgName);
    GLuint create();
private:
    GLuint m_texture;
    SDL_Surface* m_surface;
};

#endif//GLTEXTURE_H__
