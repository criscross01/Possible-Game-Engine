#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "box.h"
#include "renderer.h"

int main(){
Box box1({-1.0f,-1.0f,0.0f,   1.0f,-1.0f,0.0f,  1.0f,1.0f,0.0f,     -1.0f, 1.0f, 0.0f, -1.0f,-1.0f,0.0f,  1.0f,1.0f,0.0f});
Renderer renderer(800,600,"NAME");

renderer.loadModel(&box1);

return 0;
}
