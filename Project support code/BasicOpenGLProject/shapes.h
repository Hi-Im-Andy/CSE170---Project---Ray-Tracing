#pragma once
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;
///////////////////////////////// Background /////////////////////////////////

// Comment out to show the shapes better
class Background{
    struct vert {float x, y, z, w;};
    float w, l, h;
    float x, y, z;
    vector <float> floor;
    vector <float> floor_color;
    vector <float> walls; 
    vector <float> wall_color;

public:
    Background();
    ~Background();
    void push_vert_walls (vert corner);
    void push_vert_floor (vert corner);
    void create_walls();
    void fill_walls();
    void create_floor();
    void fill_floor();
    vector<float> update();
    vector<float> fill(float r, float g, float b);
    
};

///////////////////////////////// Shapes /////////////////////////////////
// Making the subclasses for each shape
// Shapes - Rectangle, sphere, cone, pyramid

///////////////////////////////// Rectangle Class /////////////////////////////////

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

///////////////////////////////// Sphere /////////////////////////////////

class Sphere{
    vector <float> vertices;
    vector <float> color;
    struct vert {float x, y, z, w;};
    float r, n, u, v;

public:
    Sphere();
    ~Sphere();
    void push_vert(vert corner);
    vector <float> points(int i, int j);
    void sort_verts(vector<float> temp);
    vector<float> update();
    vector<float> fill(float r, float g, float b);
    void print();
    void delete_vertices();
};

///////////////////////////////// Cone /////////////////////////////////



///////////////////////////////// Pyramid /////////////////////////////////

class Pyramid{
vector <float> vertices; // Vector used to store the vertices
vector <float> color; // Vector used to store the color of the vertices
struct vert {float x, y, z, w;}; // Struct used to store 4 variables of the point
float l, w, h;

public:
    Pyramid(); // Constructor
    ~Pyramid(); // Deconstructor

    void push_vert (vert corner);
    vector<float> update();
    vector<float> fill(float r, float g, float b);
    void print();
    void delete_vertices();
};
