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
    GLuint axis_VAO;
    GLuint axis_VBO[2];

public:
    Background();
    Background(float w1, float l1, float h1, float x1, float y1, float z1);
    ~Background();
    void push_vert_walls (vert corner);
    void push_vert_floor (vert corner);
    void create_walls();
    void fill_walls();
    void create_floor();
    void fill_floor();
    void update();
    vector<float> fill(float r, float g, float b);
    void buffer();
    void display();
    
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
float x, y, z;
GLuint rec_VAO;
GLuint rec_VBO[2];

public:
    Rectangle(); // Constructor
    Rectangle(float w1, float l1, float h1, float x1, float y1, float z1);
    ~Rectangle(); // Deconstructor

    void push_vert (vert corner);
    void update();
    vector<float> fill(float r, float g, float b);
    void print();
    void buffer();
    void display();
    void delete_vertices();
};

///////////////////////////////// Sphere /////////////////////////////////

class Sphere{
    vector <float> vertices;
    vector <float> color;
    struct vert {float x, y, z, w;};
    float r, n, u, v;
    float tempX, tempY, tempZ;
    float x, y, z;
    GLuint sp_VAO;
    GLuint sp_VBO[2];

public:
    Sphere();
    Sphere(float r1, float n1, float x1, float y1, float z1);
    ~Sphere();
    void push_vert(vert corner);
    vector <float> points(int i, int j);
    void sort_verts(vector<vector<float>> temp);
    void update();
    vector<float> fill(float r, float g, float b);
    void print();
    void buffer();
    void display();
    void delete_vertices();
};

///////////////////////////////// Cone /////////////////////////////////



///////////////////////////////// Pyramid /////////////////////////////////

class Pyramid{
vector <float> vertices; // Vector used to store the vertices
vector <float> color; // Vector used to store the color of the vertices
struct vert {float x, y, z, w;}; // Struct used to store 4 variables of the point
float l, w, h;
float x, y, z;
GLuint py_VAO;
GLuint py_VBO[2];

public:
    Pyramid(); // Constructor
    Pyramid(float w1, float l1, float h1, float x1, float y1, float z1); // Constructor

    ~Pyramid(); // Deconstructor

    void push_vert (vert corner);
    void update();
    vector<float> fill(float r, float g, float b);
    void print();
    void buffer();
    void display();
    void delete_vertices();
};
