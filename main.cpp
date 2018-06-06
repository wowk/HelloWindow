#include <GLShader.h>
#include <GLApplication.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <map>

using std::map;
using std::list;
using std::cout;
using std::endl;
using glm::vec3;


class MyGLApplication : public GLApplication {
public:
    virtual void init() {
        initGL(3, 3);
        //ToDo
        glViewport(0, 0, 800, 600);
        initAnTiangle();
        pos.x = pos.y = pos.z = 0;
    }

    void initAnTiangle() {
        shader = new GLShader;
        shader->loadShaderFile(GL_VERTEX_SHADER, "../HelloWindow/triangle.vert");
        shader->loadShaderFile(GL_FRAGMENT_SHADER, "../HelloWindow/triangle.frag");
        shader->createProgram();

        bool succ = shader->compile() && shader->attach() && shader->link();
        if( !succ ){
            shader->freeProgram();
            cout << "load shader failed" << endl;
            delete shader;
            shader = nullptr;
        }
        shader->freeShader();

        GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.5f, 1.0f,
        };
        GLuint vbo;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                               5 * sizeof(GLfloat), (GLvoid*)NULL);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                               5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        SDL_Surface* img = IMG_Load("../HelloWindow/texture1.jpg");
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h,
                     0, GL_RGB, GL_UNSIGNED_BYTE, img->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void drawTriangleViaPipeline() {
        glBindVertexArray(vao);
        shader->use();
//        shader->setUniform3f(
//                    shader->uniformLocation("custColor"),
//                    fabs(sin(SDL_GetTicks()/900.0)),
//                    fabs(cos(SDL_GetTicks()/900.0)),
//                    fabs(((SDL_GetTicks() % 900)/900.0)));
//        cout << fabs(sin(SDL_GetTicks()))
//             << fabs(cos(SDL_GetTicks()))
//             << fabs(sin(SDL_GetTicks()))
//             << endl;

        glBindTexture(GL_TEXTURE_2D, texture);
        shader->setUniform3f(
                    shader->uniformLocation("move"), pos.x, pos.y, pos.z);
        cout << pos.x << pos.y << pos.z << endl;

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindTexture(GL_TEXTURE_2D, 0);
        shader->use(false);
        glBindVertexArray(0);
    }

    virtual bool handleEvent(const SDL_Event* e) {
        switch (e->type) {
        case SDL_KEYDOWN:
            switch (e->key.keysym.sym) {
            case SDLK_LEFT:
                cout << "Left" << endl;
                pos.x -= 0.3 * m_delta;
                return false;
            case SDLK_RIGHT:
                cout << "Right" << endl;
                pos.x += 0.3 * m_delta;
                return false;
            case SDLK_UP:
                cout << "Up" << endl;
                pos.y += 0.3 * m_delta;
                return false;
            case SDLK_DOWN:
                cout << "Down" << endl;
                pos.y -= 0.3 * m_delta;
                return false;
            case SDLK_ESCAPE:
                stop();
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }

        return true;
    }

    virtual void drawEvent(const SDL_Event* e) {
        //draw a triangle via pipeline
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        drawTriangleViaPipeline();
    }

    ~MyGLApplication(){
       if( vao ){
           glDeleteVertexArrays(1, &vao);
       }
    }

    static GLApplication *create() {
        static GLApplication* app = new MyGLApplication;
        return app;
    }

protected:
    GLShader* shader;
    GLuint vao;
    GLuint texture;
    vec3 pos;
    map<SDL_Keycode,bool> keymap;
};


int main(int argc, char *argv[])
{
    GLApplication* App = MyGLApplication::create();

    App->init();
    App->setTitle(argv[0]);
    App->run();

    return 0;
}
