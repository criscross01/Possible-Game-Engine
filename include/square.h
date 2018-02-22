#ifndef SQUARE_H
#define SQUARE_H

#include <ObjectRender.h>


class Square : public ObjectRender
{
    public:
        Square(std::vector<float> vert);
        virtual ~Square();

    protected:

    private:
};

#endif // SQUARE_H
