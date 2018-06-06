#include <GLApplication.h>
#include <iostream>

using namespace std;

int GLApplication::initGL(GLint major, GLint minor)
{
    GLuint sdlFlags = SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_AUDIO;
    if( 0 > SDL_Init(sdlFlags) ){
        cout << "SDL init failed: " << SDL_GetError() << endl;
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                                SDL_GL_CONTEXT_PROFILE_CORE);

    GLuint winFlags = SDL_WINDOW_OPENGL|SDL_WINDOW_BORDERLESS;
    m_window = SDL_CreateWindow("", 0, 0, 800, 600, winFlags);
    if( !m_window ){
        cout << "SDL create window failed" << endl;
        return -2;
    }

    m_glContext = SDL_GL_CreateContext(m_window);
    if( !m_glContext ){
        cout << "create SDL GL context failed" << endl;
        return -3;
    }

    if( 0 == gladLoadGLLoader(SDL_GL_GetProcAddress) ){
        cout << "glad init GL failed" << endl;
        return -2;
    }
}

void GLApplication::setTitle(const string &title)
{
    if( !m_window ){
        cout << "SDL window is not created" << endl;
    }else{
        SDL_SetWindowTitle(m_window, title.c_str());
    }
}

GLApplication::~GLApplication()
{
    SDL_GL_DeleteContext(m_glContext);
    if( m_window ){
        SDL_DestroyWindow(m_window);
        m_window = NULL;
    }
    SDL_Quit();
}

int GLApplication::run()
{
    m_running = true;
    while( m_running ) {
        SDL_Event event;
        while( SDL_PollEvent(&event) ){
            handleEvent(&event);
        }
        drawEvent(&event);
        SDL_GL_SwapWindow(m_window);
    }
}

void GLApplication::stop()
{
    m_running = false;
}
