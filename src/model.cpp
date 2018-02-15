#include "model.h"

Model::Model(float localSpace[])
{
    for (int i = 0; i < sizeof(localSpace)/sizeof(float);i++)
    {
        modelMesh.push_back(localSpace[i]);
    }
}

Model::~Model()
{
    //dtor
}
