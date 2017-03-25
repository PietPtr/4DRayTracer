#include "Vector4D.h"
#include <math.h>

Vector4D::Vector4D(float x, float y, float z, float a)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->a = a;
}

Vector4D::Vector4D()
{
    x = 0;
    y = 0;
    z = 0;
    a = 0;
}

Vector4D::~Vector4D()
{
    //dtor
}

float Vector4D::dotProduct(Vector4D vec)
{
    acos((x * vec.x + y * vec.y + z * vec.z + a * vec.a) / (length() * vec.length()));
}

float Vector4D::length() {
    return sqrt(x * x + y * y + z * z + a * a);
}
