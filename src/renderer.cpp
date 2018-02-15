#include "renderer.h"

Renderer::Renderer(int width, int height, const char* name)
{
    if(!glfwInit()){
        std::cerr << "Hey GLFW didn't initialize correctly!" << std::endl;
        glfwTerminate();
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width,height, name, NULL, NULL);
    if (window == NULL){
        std::cerr << "Window is NULL" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "GLAD not initialized" << std::endl;
        return;
    }

    glViewport(0,0,width,height);
}

Renderer::~Renderer()
{
    //dtor
}

void Renderer::loadModel(ObjectRender* obj){
    objects.push_back(obj);

    if (obj->VAO == 0){
        std::cout << "VAO for this object uninitialized" << std::endl;

        unsigned int VBO,VAO;
        glGenVertexArrays(1,&VAO);
        glGenBuffers(1,&VBO);

        float* verts = obj->getVerts().data();

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STATIC_DRAW);

        glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        obj->VAO=VAO;
    }
}

void Renderer::renderObjects(){


    glfwSwapBuffers(window);
    glfwPollEvents();
}
