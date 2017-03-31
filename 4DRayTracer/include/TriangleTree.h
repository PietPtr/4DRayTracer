#ifndef TRIANGLETREE_H
#define TRIANGLETREE_H

#include "Triangle4D.h"
#include "vector"
class TriangleTree
{
    public:
        TriangleTree() {};

        virtual ~TriangleTree() {};

        // Calculate the tree.
        void setValues(std::vector<Triangle4D>);

        // The 4 dimensional bounding box of the triangles it contains.
        float posX;
        float posY;
        float posZ;
        float posA;
        float sizeX;
        float sizeY;
        float sizeZ;
        float sizeA;

        // Wether the node is a leaf node or not.
        bool isLeaf;

        // The child nodes if this node is not a leaf, always split in the largest size dimension.
        TriangleTree* childs;

        // The triangle if the node is a leaf.
        Triangle4D* leaftriangle;
    protected:
    private:
};

#endif // TRIANGLETREE_H
