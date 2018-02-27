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
            double xPos{0};
            double yPos{0};
            double zPos{-2};

            double xScale{1};
            double yScale{1};
            double zScale{1};

            double xRot{0};
            double yRot{0};
            double zRot{60};
        }trans;

        struct RGB {
            float red{1.0f};
            float green{1.0f};
            float blue{1.0f};
        }color;
    private:
        std::vector<float> verts;
};

#endif // OBJECTRENDER_H
