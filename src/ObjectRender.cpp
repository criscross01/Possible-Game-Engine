#include "ObjectRender.h"

ObjectRender::ObjectRender(float pos[3], float scale[3], float rot[3], float colors[3], std::vector<float> vert)
{
    //ctor
    verts = vert;

    trans.xPos = pos[0];
    trans.yPos = pos[1];
    trans.zPos = pos[2];

    trans.xScale = scale[0];
    trans.yScale = scale[1];
    trans.zScale = scale[2];

    trans.xRot = rot[0];
    trans.yRot = rot[1];
    trans.zRot = rot[2];

    color.red = colors[0];
    color.green = colors[1];
    color.blue = colors[2];
}

ObjectRender::ObjectRender(std::vector<float> vert)
{
    verts = vert;
}

ObjectRender::~ObjectRender()
{
    //dtor
}


std::vector<float> ObjectRender::getVerts(){
    return verts;
}

int ObjectRender::getVertsSize(){
    return verts.size();
}
