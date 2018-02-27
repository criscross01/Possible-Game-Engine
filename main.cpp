#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "ObjectRender.h"
#include "renderer.h"

int main(){
std::vector<float> triVerts =
{
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f
};

std::vector<float> cubeVerts =
{-1.0f,-1.0f, 1.0f,
  1.0f,-1.0f, 1.0f,
  1.0f, 1.0f, 1.0f, //Triangle 1

 -1.0f,-1.0f, 1.0f,
 -1.0f, 1.0f, 1.0f,
  1.0f, 1.0f, 1.0f, //Triangle 2
  //Square 1

  -1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f,-1.0f,
  -1.0f,-1.0f,-1.0f,

  -1.0f,-1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,

   1.0f, 1.0f, 1.0f,
   1.0f, 1.0f,-1.0f,
   1.0f,-1.0f,-1.0f,

   1.0f,-1.0f, 1.0f,
   1.0f, 1.0f, 1.0f,
   1.0f,-1.0f,-1.0f
  };

ObjectRender triangle(triVerts);
ObjectRender cube(cubeVerts);
Renderer renderer(800,600,"GAME ENGINE");

renderer.loadModel(&cube);

while (!renderer.windowShouldClose()){
    renderer.renderObjects();
    cube.color.red = sin(glfwGetTime())+1;
}

return 0;
}
