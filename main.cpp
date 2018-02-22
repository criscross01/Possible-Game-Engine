#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "ObjectRender.h"
#include "renderer.h"

int main(){
std::vector<float> squareVerts =
{-1.0f,-1.0f, 0.0f,
  1.0f,-1.0f, 0.0f,
  1.0f, 1.0f, 0.0f, //Triangle 1

// -1.0f,-1.0f, 0.0f,
// -1.0f, 1.0f, 0.0f,
//  1.0f, 1.0f, 0.0f //Triangle 2
  };

ObjectRender square(squareVerts);
Renderer renderer(800,600,"GAME ENGINE");

renderer.loadModel(&square);

while (!renderer.windowShouldClose()){
    renderer.renderObjects();
}

return 0;
}
