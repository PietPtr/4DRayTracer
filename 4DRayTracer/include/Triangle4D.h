#ifndef TRIANGLE4D_H
#define TRIANGLE4D_H
#include "Vector4D.h"

class Triangle4D
{
    public:
        Triangle4D(Vector4D, Vector4D, Vector4D);
        Triangle4D();
        virtual ~Triangle4D();



        Vector4D v1;
        Vector4D v2;
        Vector4D v3;
    protected:
    private:
};

#endif // TRIANGLE_H
