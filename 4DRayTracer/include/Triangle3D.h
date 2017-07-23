#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H
#include <SFML/Graphics.hpp>

using namespace sf;

class Triangle3D
{
    public:
        Triangle3D(Vector3f, Vector3f, Vector3f);
        Triangle3D();
        virtual ~Triangle3D();

        Vector3f v1;
        Vector3f v2;
        Vector3f v3;
    protected:
    private:
};

#endif // TRIANGLE3D_H
