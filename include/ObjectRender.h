#ifndef OBJECTRENDER_H
#define OBJECTRENDER_H
#include <vector>

class ObjectRender
{
    public:
        unsigned int VAO{0};
        std::vector<float> getVerts();
        int getVertsSize();
        ObjectRender(std::vector<float> vert);
        virtual ~ObjectRender();

        struct trnsform {
            double xPos{-1};
            double yPos{0};
            double zPos{-3};

            double xScale{1};
            double yScale{1};
            double zScale{1};

            double xRot{0};
            double yRot{0};
            double zRot{0};
        }trans;

        struct RGB {
            float red{0.5f};
            float green{1.0f};
            float blue{0.5f};
        }color;
    private:
        std::vector<float> verts;
};

#endif // OBJECTRENDER_H
