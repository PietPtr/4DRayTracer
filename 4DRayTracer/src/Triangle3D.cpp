#include "Triangle3D.h"

using namespace sf;

Triangle3D::Triangle3D(Vector3f v1, Vector3f v2, Vector3f v3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}

Triangle3D::Triangle3D()
{
    v1 = Vector3f(0, 0, 0);
    v2 = Vector3f(0, 0, 0);
    v3 = Vector3f(0, 0, 0);
}

Triangle3D::~Triangle3D()
{
    //dtor
}
