#ifndef MODEL_H
#define MODEL_H
#include <vector>

class Model
{
    public:
        Model(float localSpace[]);
        virtual ~Model();

//        std::vector<float> getMesh();
//    private:
        std::vector<float> modelMesh;
};

#endif // MODEL_H
