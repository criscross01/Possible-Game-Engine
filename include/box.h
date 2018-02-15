#ifndef BOX_H
#define BOX_H

#include "ObjectRender.h"


class Box : public ObjectRender
{
    public:
        Box(std::vector<float> vert);
        virtual ~Box();

    protected:

    private:
};

#endif // BOX_H
