#ifndef GLAPPLICATION_H__
#define GLAPPLICATION_H__

#include <GLObject.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>
#include <string>


using glm::vec2;
using std::string;


class GLApplication : public GLObject {
public:

    void run();
    virtual void stop();
    void setTitle(const string & title);
    virtual void init() = 0;
    ~GLApplication();

protected:
    virtual int initGL(GLint major, GLint minor);
    virtual void handleEvent(const SDL_Event* e) = 0;
    virtual void drawEvent(const SDL_Event* e) = 0;
    explicit GLApplication(){}

protected:
    bool m_running;
    Uint32 m_glMajor;
    Uint32 mglMinor;
    Uint32 m_winFlags;
    Uint32 m_sdlFlags;
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
};


#endif//GLAPPLICATION_H__
