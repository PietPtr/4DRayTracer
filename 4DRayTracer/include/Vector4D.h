#ifndef VECTOR4D_H
#define VECTOR4D_H


class Vector4D
{
    public:
        Vector4D(float, float, float, float);
        Vector4D();
        virtual ~Vector4D();

        float x, y, z, a;

        float dotProduct(Vector4D);

        float length();

        bool equals(Vector4D*);

    protected:
    private:
};

#endif // VECTOR4D_H
