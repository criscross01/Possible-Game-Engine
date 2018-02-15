#ifndef OBJECTRENDER_H
#define OBJECTRENDER_H
#include <vector>

class ObjectRender
{
    public:
        unsigned int VAO;
        std::vector<float> getVerts();
        ObjectRender(std::vector<float> vert);
        virtual ~ObjectRender();
    protected:
        struct trans {
            double x{0};
            double y{0};
            double z{0};
        };
    private:
        std::vector<float> verts;
};

#endif // OBJECTRENDER_H
