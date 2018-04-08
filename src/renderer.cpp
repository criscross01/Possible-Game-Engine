#include "renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


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

    window = glfwCreateWindow(width, height, name, NULL, NULL);
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
    //glEnable(GL_DEPTH_TEST);

    glViewport(0,0,width,height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    getShader();

    perspective = glm::perspective(glm::radians(45.0f),(float)width/(float)height,0.1f,100.0f);

    view = glm::lookAt(glm::vec3(0.0f,0.0f,3.0f),
                       glm::vec3(0.0f,0.0f,0.0f),
                       glm::vec3(0.0f,1.0f,0.0f));
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
        std::cout << "VAO for this object uninitialized.  Giving object VAO" << std::endl;

        unsigned int VBO,VAO;
        glGenVertexArrays(1,&VAO);
        glGenBuffers(1,&VBO);

        std::vector<float> vertices = obj->getVerts();
        float verts[obj->getVertsSize()-1];

        for (int i{0}; i < obj->getVertsSize(); i++){
            verts[i] = vertices[i];
        }

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

//    float radius = 10.0f;
//    float camX = sin(glfwGetTime()) * radius;
//    float camZ = cos(glfwGetTime()) * radius;
//    glm::mat4 view;
//    view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    processInput(window);

    //glClearColor(0.2f,0.3f,0.5f,1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderID);

    for(int i = 0; i < objNum; i++)
    {
        glm::mat4 trans;

        renObj = objects[i];

        trans = glm::translate(trans,glm::vec3(renObj->trans.xPos,renObj->trans.yPos,renObj->trans.zPos));
        trans = glm::rotate(trans,(float)glm::radians(renObj->trans.xRot),glm::vec3(0.0,0.0,1.0));
        trans = glm::rotate(trans,(float)glm::radians(renObj->trans.yRot),glm::vec3(1.0,0.0,0.0));
        trans = glm::rotate(trans,(float)glm::radians(renObj->trans.zRot),glm::vec3(0.0,1.0,0.0));
        trans = glm::scale(trans, glm::vec3(renObj->trans.xScale,renObj->trans.yScale,renObj->trans.zScale));

        glUniformMatrix4fv(glGetUniformLocation(shaderID,"transform"),1,GL_FALSE,glm::value_ptr(trans));
        glUniformMatrix4fv(glGetUniformLocation(shaderID,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderID,"persp"),1,GL_FALSE,glm::value_ptr(perspective));
        glUniform3f(glGetUniformLocation(shaderID,"color"),renObj->color.red,renObj->color.green,renObj->color.blue);
        glUniform3f(glGetUniformLocation(shaderID,"lightPos"),3.0f,0.0f,3.0f);
        glUniform3f(glGetUniformLocation(shaderID,"viewPos"),0.0f,0.0f,3.0f);

        glBindVertexArray(renObj->VAO);
        glDrawArrays(GL_TRIANGLES,0,renObj->getVertsSize());
    }

    //std::cout << "LOOP!" << std::endl;
    glfwSwapBuffers(window);
}

bool Renderer::windowShouldClose(){
    return glfwWindowShouldClose(window);
}

GLFWwindow* Renderer::getWindow(){
    return window;
}
