#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>
#include <vector>
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

    private:
        std::vector<ObjectRender*> objects;
        std::vector<unsigned int> VAOs;
        int numVAOs{0};
        GLFWwindow* window;
};

#endif // RENDERER_H
