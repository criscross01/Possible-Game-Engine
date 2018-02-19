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

    getShader();
}

Renderer::~Renderer()
{
    glfwTerminate();
    //dtor
}

void Renderer::loadModel(ObjectRender* obj){
    objects.push_back(obj);
    objNum ++;

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

void Renderer::getShader(){
    //Inputting fragment and vertex shaders
    std::ifstream vertexInput,fragmentInput;
    vertexInput.open("vertexShader.txt");
    fragmentInput.open("fragmentShader.txt");
    std::stringstream vertexStream,fragmentStream;
    vertexStream << vertexInput.rdbuf();
    fragmentStream << fragmentInput.rdbuf();
    std::string fragmentString, vertexString;
    vertexString = vertexStream.str();
    fragmentString = fragmentStream.str();
    const char* vertexSource = vertexString.c_str();
    const char* fragmentSource = fragmentString.c_str();

    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource,NULL);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    shaderID = glCreateProgram();
    glAttachShader(shaderID,vertexShader);
    glAttachShader(shaderID,fragmentShader);
    glLinkProgram(shaderID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Renderer::renderObjects(){

    glClearColor(0.2f,0.3f,0.3f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = 0; i < objNum; i++)
    {
        renObj = objects[i];

        glUseProgram(shaderID);
        glBindVertexArray(renObj->VAO);
        glDrawArrays(GL_TRIANGLES,0,sizeof(renObj->getVerts())/sizeof(float));
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Renderer::windowShouldClose(){
    return glfwWindowShouldClose(window);
}
