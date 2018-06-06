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
    explicit GLApplication() {
        m_running = false;
        m_window = NULL;
        m_glContext = NULL;
        m_oldTicks = SDL_GetTicks();
        m_delta = 0.0;
    }

    void run();
    virtual void stop();
    void setTitle(const string & title);
    virtual void init() = 0;
    ~GLApplication();

protected:
    virtual int initGL(GLint major, GLint minor);
    virtual bool handleEvent(const SDL_Event* e) = 0;
    virtual void drawEvent(const SDL_Event* e) = 0;

protected:
    bool m_running;
    GLuint m_glMajor;
    GLuint mglMinor;
    GLuint m_winFlags;
    GLuint m_sdlFlags;
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    GLfloat m_delta;

private:
    Uint32 m_oldTicks;
};


#endif//GLAPPLICATION_H__
