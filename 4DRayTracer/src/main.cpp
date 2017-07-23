#include <iostream>
#include <vector>
#include <sstream>
#include "Triangle3D.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Triangle4D.h"
#include "TriangleTree.h"

using namespace sf;


/* CONSTANTS */
// Size of all 3 Dimensions of screen
const int DIM = 100;

/* PREDEFINITIONS */
std::vector<Triangle3D> pointsToTriangles(std::vector<Color> points);
void buildOBJFile(std::vector<Triangle3D>* triangles, std::string file);
std::string vectorToOBJString(Vector3f v);
Vector3i indexToCoords(int index);
std::vector<Triangle4D> load4DModel(std::string filename);
std::array<float, 4> getVertexValues(std::string line);
std::array<int, 3> getFaceValues(std::string line);

int main() {

    // Load 4d model.
    std::vector<Triangle4D> triangles = load4DModel("test.4bj");

    // random triangles generate a test tree:
    std::vector<Triangle4D> test_triangles = std::vector<Triangle4D>(0);

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            for (int z = 0; z < 10; z++) {
                for (int a = 0; a < 1; a++) {
                    Vector4D v1 = Vector4D((float)x, (float)y, (float)z, (float)a);
                    Vector4D v2 = Vector4D((float)x, (float)y + 0.5, (float)z + 0.5, (float)a + 0.5);
                    Vector4D v3 = Vector4D((float)x, (float)y + 0.5, (float)z, (float)a);
                    //std::cout << v1.x;

                    Triangle4D triangle = Triangle4D(v1, v2, v3);
                    test_triangles.push_back(triangle);
                }
            }
        }
    }
    std::vector<Triangle4D*> reference_triangles(test_triangles.size());
    for (int i = 0; i < test_triangles.size(); i++) {
        reference_triangles[i] = &test_triangles[i];
    }
    //std::cout << "Finished generating random triangles" << std::endl;


    // Build triangle tree. std::vector<Triangle4D>.
    TriangleTree tree = TriangleTree();
    tree.setValues(reference_triangles);
    std::cout << "Finished generating random triangles" << std::endl;
    //while (true) {}


    // Raytrace triangles to 3d array. +Returns std::array<Color, 1000000>


    //Dummy data
    std::vector<Color> points;

    for (int i = 0; i < DIM*DIM*DIM; i++)
    {
        points.push_back(Color(0, 0, 0, 0));

        Vector3i coords = indexToCoords(i);

        if (random() % 2 == 1)//(coords.z - 0 < tan(coords.x / 5.0) * 5.0 * sin(coords.y / 5.0) * 5.0 + coords.x / 5.0 + coords.y / 5.0)
        {

        }
    }

    points[0] = Color(255, 255, 255, 255);

    // Convert result to list of triangles. std::vector<Triangle3D>
    std::vector<Triangle3D> triangles3D = pointsToTriangles(points);

    // Build obj model.
    buildOBJFile(&triangles3D, "test3.obj");

    return 0;
}

std::vector<Triangle4D> load4DModel(std::string filename)
{
    std::string line;
    std::ifstream file("test.4bj");
    std::vector<Vector4D> vertices;
    std::vector<Triangle4D> triangles;

    if (file.is_open()) {
        while (getline(file, line)) {
            std::cout << line << '\n';
            if (line[0] == 'v') {
                std::array<float, 4> values = getVertexValues(line);
                Vector4D vertex = Vector4D(values[0], values[1], values[2], values[3]);
                vertices.push_back(vertex);

                std::cout << "  -> vertex\n";
            }
            if (line[0] == 'f') {
                std::array<int, 3> values = getFaceValues(line);
                Triangle4D triangle = Triangle4D(vertices[values[0]], vertices[values[1]], vertices[values[2]]);
                triangles.push_back(triangle);

                std::cout << "  -> face\n";
            }
        }
        file.close();
    }

    return triangles;
}

std::array<float, 4> getVertexValues(std::string line)
{
    std::array<float, 4> values;

    std::string s;
    std::istringstream iss(line);
    int counter = -1;
    while (getline(iss, s, ' ')) {
        if (counter == -1) {
            counter++;
            continue;
        }

        values[counter] = std::stof(s);

        counter++;
    }

    return values;
}

std::array<int, 3> getFaceValues(std::string line)
{
    std::array<int, 3> values;

    std::string s;
    std::istringstream iss(line);
    int counter = -1;
    while (getline(iss, s, ' ')) {
        if (counter == -1) {
            counter++;
            continue;
        }

        values[counter] = std::stoi(s);

        counter++;
    }

    return values;
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

int coordsToIndex(Vector3i coords)
{
    int index = 0;

    index += coords.x;
    index += coords.y * DIM;
    index += coords.z * DIM * DIM;

    return index;
}

std::vector<Triangle3D> pointsToTriangles(std::vector<Color> points)
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

        if (!(posx == DIM-1 || posy == DIM-1 || posz == DIM-1 || posx == 0 || posy == 0 || posz == 0))
        {
            if ((points[coordsToIndex(Vector3i(posx+1, posy, posz))].a != 0 &&
                 points[coordsToIndex(Vector3i(posx-1, posy, posz))].a != 0 &&
                 points[coordsToIndex(Vector3i(posx, posy+1, posz))].a != 0 &&
                 points[coordsToIndex(Vector3i(posx, posy-1, posz))].a != 0 &&
                 points[coordsToIndex(Vector3i(posx, posy, posz+1))].a != 0 &&
                 points[coordsToIndex(Vector3i(posx, posy, posz-1))].a != 0))
            {
                continue;
            }
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

void buildOBJFile(std::vector<Triangle3D>* triangles, std::string file)
{
    std::cout << "Building .OBJ file...\n";
    std::string vertices = "";
    std::string faces = "";

    std::ofstream out(file);

    for (int i = 0; i < triangles->size(); i++)
    {
        if (i % 100000 == 0)
        {
            std::cout << "  Built " << ((float)i / triangles->size()) * 100.0 << "%\n";
        }
        std::string vertex1 = vectorToOBJString(triangles->at(i).v1);
        vertices += vertex1 + "\n";
        out << vertex1 << "\n";

        std::string vertex2 = vectorToOBJString(triangles->at(i).v2);
        vertices += vertex2 + "\n";
        out << vertex2 << "\n";

        std::string vertex3 = vectorToOBJString(triangles->at(i).v3);
        vertices += vertex3 + "\n";
        out << vertex3 << "\n";

        std::string face = "f ";
        face += std::to_string(i*3 + 1) + " ";
        face += std::to_string(i*3 + 2) + " ";
        face += std::to_string(i*3 + 3) + " ";

        out << face << "\n";
    }
}



