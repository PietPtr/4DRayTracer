#include "TriangleTree.h"
#include <limits>
#include <iostream>





void TriangleTree::setValues(std::vector<Triangle4D*> triangles) {
    this->isLeaf = true;

    Vector4D* v1 = &triangles[0]->v1;
    Vector4D* v2 = &triangles[0]->v2;
    Vector4D* v3 = &triangles[0]->v3;

    for (int i = 1; i < triangles.size(); i++) {
        if (triangles[i]->v1.equals(v1) || triangles[i]->v1.equals(v2) || triangles[i]->v1.equals(v3)) {
            continue;
        }
        if (triangles[i]->v2.equals(v1) || triangles[i]->v2.equals(v2) || triangles[i]->v2.equals(v3)) {
            continue;
        }
        if (triangles[i]->v3.equals(v1) || triangles[i]->v3.equals(v2) || triangles[i]->v3.equals(v3)) {
            continue;
        }

        isLeaf = false;
        break;
    }



    if (triangles.size() <= 1 || isLeaf) {
        isLeaf = true;
        return;
    }


    posX = std::numeric_limits<float>::infinity();
    posY = std::numeric_limits<float>::infinity();
    posZ = std::numeric_limits<float>::infinity();
    posA = std::numeric_limits<float>::infinity();

    sizeX = 0;
    sizeY = 0;
    sizeZ = 0;
    sizeA = 0;

    // Check the lowest bound of the triangles
    for (int i = 0; i < triangles.size(); i++) {
    //for (std::vector<Triangle4D>::iterator triangle = triangles.begin() ; triangle != triangles.end(); ++triangle) {
        Triangle4D* triangle = triangles[i];
        //std::cout << triangle->v1.x << std::endl;

        if (triangle->v1.x < posX) {
            posX = triangle->v1.x;
        }
        if (triangle->v1.y < posY) {
            posY = triangle->v1.y;
        }
        if (triangle->v1.z < posZ) {
            posZ = triangle->v1.z;
        }
        if (triangle->v1.a < posA) {
            posA = triangle->v1.a;
        }

        if (triangle->v2.x < posX) {
            posX = triangle->v2.x;
        }
        if (triangle->v2.y < posY) {
            posY = triangle->v2.y;
        }
        if (triangle->v2.z < posZ) {
            posZ = triangle->v2.z;
        }
        if (triangle->v2.a < posA) {
            posA = triangle->v2.a;
        }

        if (triangle->v3.x < posX) {
            posX = triangle->v3.x;
        }
        if (triangle->v3.y < posY) {
            posY = triangle->v3.y;
        }
        if (triangle->v3.z < posZ) {
            posZ = triangle->v3.z;
        }
        if (triangle->v3.a < posA) {
            posA = triangle->v3.a;
        }
        //std::cout << posX << std::endl;
    }


    for (int i = 0; i < triangles.size(); i++) {
        Triangle4D* triangle = triangles[i];
        if (triangle->v1.x - posX > sizeX) {
            sizeX = triangle->v1.x - posX;
        }
        if (triangle->v1.y - posY > sizeY) {
            sizeY = triangle->v1.y - posY;
        }
        if (triangle->v1.z - posZ > sizeZ) {
            sizeZ = triangle->v1.z - posZ;
        }
        if (triangle->v1.a - posA > sizeA) {
            sizeA = triangle->v1.a - posA;
        }

        if (triangle->v2.x - posX > sizeX) {
            sizeX = triangle->v2.x - posX;
        }
        if (triangle->v2.y - posY > sizeY) {
            sizeY = triangle->v2.y - posY;
        }
        if (triangle->v2.z - posZ > sizeZ) {
            sizeZ = triangle->v2.z - posZ;
        }
        if (triangle->v2.a - posA > sizeA) {
            sizeA = triangle->v2.a - posA;
        }

        if (triangle->v3.x - posX > sizeX) {
            sizeX = triangle->v3.x - posX;
        }
        if (triangle->v3.y - posY > sizeY) {
            sizeY = triangle->v3.y - posY;
        }
        if (triangle->v3.z - posZ > sizeZ) {
            sizeZ = triangle->v3.z - posZ;
        }
        if (triangle->v3.a - posA > sizeA) {
            sizeA = triangle->v3.a - posA;
        }
    }


    std::vector<Triangle4D*> part1(0);
    std::vector<Triangle4D*> part2(0);

    if (sizeX > sizeY && sizeX > sizeZ && sizeX > sizeA) {
        for (int i = 0; i < triangles.size(); i++) {
            Triangle4D* triangle = triangles[i];
            bool added_to_1 = false;
            bool added_to_2 = false;

            if (triangle->v1.x < posX + (sizeX / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }

           if (triangle->v2.x < posX + (sizeX / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }

            if (triangle->v3.x < posX + (sizeX / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }
        }
    } else if (sizeY > sizeZ && sizeY > sizeA) {
        for (int i = 0; i < triangles.size(); i++) {
            Triangle4D* triangle = triangles[i];
            bool added_to_1 = false;
            bool added_to_2 = false;

            if (triangle->v1.y < posY + (sizeY / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }

           if (triangle->v2.y < posY + (sizeY / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }

            if (triangle->v3.y < posY + (sizeY / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }
        }
    } else if (sizeZ > sizeA) {
        for (int i = 0; i < triangles.size(); i++) {
            Triangle4D* triangle = triangles[i];
            bool added_to_1 = false;
            bool added_to_2 = false;

            if (triangle->v1.z < posZ + (sizeZ / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }

           if (triangle->v2.z < posZ + (sizeZ / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }

            if (triangle->v3.z < posZ + (sizeZ / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }
        }
    } else {
        for (int i = 0; i < triangles.size(); i++) {
            Triangle4D* triangle = triangles[i];
            bool added_to_1 = false;
            bool added_to_2 = false;

            if (triangle->v1.a < posA + (sizeA / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }

           if (triangle->v2.a < posA + (sizeA / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }

            if (triangle->v3.a < posA + (sizeA / 2.0)) {
                if (!added_to_1) {
                    added_to_1 = true;
                    part1.push_back(triangle);
                }
            } else {
                if (!added_to_2) {
                    added_to_2 = true;
                    part2.push_back(triangle);
                }
            }
        }
    }
    //std::cout << "posX: " << posX << std::endl;
    //std::cout << "posY: " << posY << std::endl;
    //std::cout << "posZ: " << posZ << std::endl;
    //std::cout << "posA: " << posA << std::endl;

    //std::cout << "sizeX: " << sizeX << std::endl;
    //std::cout << "sizeY: " << sizeY << std::endl;
    //std::cout << "sizeZ: " << sizeZ << std::endl;
    //std::cout << "sizeA: " << sizeA << std::endl;

    //std::cout << "finished splitting list of " << triangles.size() << " triangles" << std::endl;
    //std::cout << "part1 has length of " << part1.size() << " triangles" << std::endl;
    //std::cout << "part2 has length of " << part2.size() << " triangles" << std::endl;

    childs = new TriangleTree[2];
    childs[0].setValues(part1);
    childs[1].setValues(part2);
}

TriangleTree::~TriangleTree() {
    delete [] (childs);
}
