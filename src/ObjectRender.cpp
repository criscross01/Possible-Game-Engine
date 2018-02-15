#include "ObjectRender.h"

ObjectRender::ObjectRender(std::vector<float> vert)
{
    //ctor
    verts = vert;
}

ObjectRender::~ObjectRender()
{
    //dtor
}


std::vector<float> ObjectRender::getVerts(){
    return verts;
}
