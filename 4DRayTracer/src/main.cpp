#include <iostream>
#include <vector>
#include "Triangle3D.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>

using namespace sf;


/* CONSTANTS */
// Size of all 3 Dimensions of screen
const int DIM = 100;

std::vector<Triangle3D> pointsToTriangles(std::array<Color, DIM*DIM*DIM> points);
std::string buildOBJFile(std::vector<Triangle3D>* triangles);
void writeOBJ(std::string obj, std::string file);
std::string vectorToOBJString(Vector3f v);

int main(int argc, char* argv[]) {

    // Load 4d model.


    // Convert to triangles.


    // Build triangle tree. std::vector<Triangle4D>.


    // Raytrace triangles to 3d array. Returns std::array<Color, 1000000>


    //Dummy data
    /*
    std::array<Color, DIM*DIM*DIM> points;
    for (int i = 0; i < DIM*DIM*DIM; i++)
    {
        points[i] = Color(0, 0, 0, 0);
    }
    points[0] = Color(255, 255, 255, 255);
    points[2] = Color(255, 255, 255, 255);
    points[200] = Color(255, 255, 255, 255);
    points[202] = Color(255, 255, 255, 255);
    points[20000] = Color(255, 255, 255, 255);
    */

    // Convert result to list of triangles. std::vector<Triangle3D>
    std::vector<Triangle3D> triangles = pointsToTriangles(points);

    // Build obj model.
    std::string obj = buildOBJFile(&triangles);

    // Write obj model
    writeOBJ(obj, "test2.obj");


    return 0;
}

Vector3i indexToCoords(int index)
{
    Vector3i coords;

    coords.z = index / DIM / DIM;
    coords.y = index / DIM % DIM;
    coords.x = index % DIM;
    //std::cout << "x: " << coords.x << ", y: " << coords.y << ", z: " << coords.z << "\n";

    return coords;
}

std::vector<Triangle3D> pointsToTriangles(std::array<Color, DIM*DIM*DIM> points)
{
    std::cout << "Converting point array to triangles...\n";
    std::vector<Triangle3D> triangles;

    for (int p = 0; p < DIM*DIM*DIM; p++)
    {
        Vector3i coords = indexToCoords(p);
        int posx = coords.x;
        int posy = coords.y;
        int posz = coords.z;

        if (points[p].a == 0)
        {
            continue;
        }

        std::array<Vector3f, 8> vertices;

        // generate vertices
        for (int z = 0; z < 2; z++)
        {
            vertices[z * 4 + 0] = Vector3f(posx,   posy,   posz+z);
            vertices[z * 4 + 1] = Vector3f(posx,   posy+1, posz+z);
            vertices[z * 4 + 2] = Vector3f(posx+1, posy+1, posz+z);
            vertices[z * 4 + 3] = Vector3f(posx+1, posy,   posz+z);
        }

        // Generate lower triangles
        for (int i = 0; i < 4; i++)
        {
            Triangle3D tri(vertices[i], vertices[i+1], vertices[(i+4) % 8]);
            if (i == 3)
            {
                tri.v2 = vertices[0];
            }
            triangles.push_back(tri);
        }

        // generate 4 upper triangles
        for (int i = 0; i < 4; i++)
        {
            Triangle3D tri(vertices[(i+4) % 8], vertices[(i+5) % 8], vertices[i+1]);

            triangles.push_back(tri);

        }

        // generate 2 top triangles

        for (int i = 0; i < 2; i++)
        {
            Triangle3D top1(vertices[i*4 + 0], vertices[i*4 + 1], vertices[i*4 + 2]);
            Triangle3D top2(vertices[i*4 + 0], vertices[i*4 + 3], vertices[i*4 + 2]);
            triangles.push_back(top1);
            triangles.push_back(top2);
        }

        // generate 2 bottom triangles
    }

    return triangles;
}

std::string vectorToOBJString(Vector3f v)
{
    std::string vertex = "v ";
    vertex += std::to_string(v.x) + " ";
    vertex += std::to_string(v.y) + " ";
    vertex += std::to_string(v.z) + " ";

    return vertex;
}

std::string buildOBJFile(std::vector<Triangle3D>* triangles)
{
    std::cout << "Building .OBJ file...\n";
    std::string vertices = "";
    std::string faces = "";

    for (int i = 0; i < triangles->size(); i++)
    {
        std::string vertex1 = vectorToOBJString(triangles->at(i).v1);
        vertices += vertex1 + "\n";

        std::string vertex2 = vectorToOBJString(triangles->at(i).v2);
        vertices += vertex2 + "\n";

        std::string vertex3 = vectorToOBJString(triangles->at(i).v3);
        vertices += vertex3 + "\n";

        std::string face = "f ";
        face += std::to_string(i*3 + 1) + " ";
        face += std::to_string(i*3 + 2) + " ";
        face += std::to_string(i*3 + 3) + " ";

        faces += face + "\n";
    }

    return vertices + "\n" + faces;
}

void writeOBJ(std::string obj, std::string file)
{
    std::cout << "Writing .OBJ file to file system...\n";
    std::ofstream out(file);
    out << obj;
    out.close();
}



