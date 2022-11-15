#pragma once
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

// class Background{
//     vector <float> floor;
//     vector <float> floor_color;
//     vector <float> walls; 
//     vector <float> wall_color;

// public:
//     Background();
//     ~Background();
//     vector<float> create_walls();
//     vector<float> fill_walls();
// };

///////////////////////////////// Parent Class /////////////////////////////////

class Rectangle{
vector <float> vertices; // Vector used to store the vertices
vector <float> color; // Vector used to store the color of the vertices
struct vert {float x, y, z, w;}; // Struct used to store 4 variables of the point
float length, width, height;

public:
    Rectangle(); // Constructor
    ~Rectangle(); // Deconstructor

    void push_vert (vert corner);
    vector<float> update();
    vector<float> fill(float r, float g, float b);
    void print();
    void delete_vertices();
};

///////////////////////////////// Shapes /////////////////////////////////
// Making the subclasses for each shape
// Shapes - Rectangle, sphere, cone, pyramide, cylinder


///////////////////////////////// Rectangle /////////////////////////////////

///////////////////////////////// Sphere /////////////////////////////////

///////////////////////////////// Cone /////////////////////////////////

///////////////////////////////// Pyramide /////////////////////////////////

///////////////////////////////// Cylinder /////////////////////////////////

