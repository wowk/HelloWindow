#include <GLShader.h>
#include <GLApplication.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <list>

using std::list;
using std::cout;
using std::endl;


class MyGLApplication : public GLApplication {
public:
    virtual int init() {
        initGL(3, 3);
        //ToDo
        glViewport(0, 0, 800, 600);

        initAnTiangle();
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
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
        };
        GLuint vbo;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                               3 * sizeof(GLfloat), (GLvoid*)NULL);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    void drawTriangleViaPipeline() {
        glBindVertexArray(vao);
        shader->use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        shader->use(false);
        glBindVertexArray(0);
    }

    virtual void handleEvent(const SDL_Event* e) {
        switch (e->type) {
        case SDL_KEYDOWN:
            stop();
            break;
        default:
            break;
        }
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
};


int main(int argc, char *argv[])
{
    GLApplication* App = MyGLApplication::create();

    App->init();
    App->setTitle(argv[0]);
    return App->run();
}
