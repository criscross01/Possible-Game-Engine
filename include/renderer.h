#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ObjectRender.h"

class Renderer
{
    public:
        Renderer(int,int,const char*);
        virtual ~Renderer();

        void loadModel(ObjectRender*);
        void renderObjects();

        bool windowShouldClose();
    private:
        std::vector<ObjectRender*> objects;
        std::vector<unsigned int> VAOs;
        int objNum{0};
        ObjectRender* renObj;
        GLFWwindow* window;
        void getShader();
        unsigned int shaderID;
};

#endif // RENDERER_H
