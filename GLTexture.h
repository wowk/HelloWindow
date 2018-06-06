#ifndef GLTEXTURE_H__
#define GLTEXTURE_H__

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using std::cout;
using std::endl;

class GLTexture {
protected:
    explicit GLTexture(){}
    GLuint m_target;
};

class GLTexture2D : public GLTexture {
public:
    GLTexture2D(const char* imgName = nullptr);
    void create();
    bool bind();
    void unbind();
    bool loadImage(const char* imgName);

    inline void setTexParameterf(GLenum pname, GLfloat param) {
        if( m_bind || bind() ){
            glTexParameterf(m_target, pname, param);
        }else{
            cout << "1-cant bind texture" << endl;
        }
    }

    inline void setTexParameteri(GLenum pname, GLint param) {
        if( m_bind || bind() ){
            glTexParameteri(m_target, pname, param);
        }else{
            cout << "2-cant bind texture" << endl;
        }
    }

    inline void setTexParameterfv(GLenum pname, const GLfloat * params) {
        if( m_bind || bind() ){
            glTexParameterfv(m_target, pname, params);
        }else{
            cout << "3-cant bind texture" << endl;
        }
    }

    inline void setTexParameteriv(GLenum pname, const GLint * params) {
        if( m_bind || bind() ){
            glTexParameteriv(m_target, pname, params);
        }else{
            cout << "4-cant bind texture" << endl;
        }
    }

    inline void setTexParameterIiv(GLenum pname, const GLint * params) {
        if( m_bind || bind() ){
            glTexParameterIiv(m_target, pname, params);
        }else{
            cout << "5-cant bind texture" << endl;
        }
    }

    inline void setTexParameterIuiv(GLenum pname, const GLuint * params) {
        if( m_bind || bind() ){
            glTexParameterIuiv(m_target, pname, params);
        }else{
            cout << "6-cant bind texture" << endl;
        }
    }

    void draw();

private:
    bool m_bind;
    GLuint m_texture;
    GLuint* m_textures;
};

#endif//GLTEXTURE_H__
