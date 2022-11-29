#include "shapes.h"
#include <iostream>


///////////////////////////////// Background /////////////////////////////////
Background::Background(){
    w = 10;
    l = 10;
    h = 10;
}

Background::~Background(){
    floor.clear();
    floor_color.clear();
    walls.clear();
    wall_color.clear();
}

void Background::push_vert_walls(vert corner){
    walls.push_back(corner.x);
    walls.push_back(corner.y);
    walls.push_back(corner.z);
    walls.push_back(1);
}
void Background::push_vert_floor(vert corner){
    floor.push_back(corner.x);
    floor.push_back(corner.y);
    floor.push_back(corner.z);
    floor.push_back(1);
}

void Background::create_walls(){
    vert bl, br, fl, fr;
    bl.x = 0;
    bl.y = 0;

    br.x = w;
    br.y = 0;

    fl.x = 0;
    fl.y = l;

    fr.x = w;
    fr.y = l;

    bl.z = 0;
    br.z = 0;
    fl.z = 0;
    fr.z = 0;

    push_vert_floor(bl);
    push_vert_floor(br);
    push_vert_floor(fl);
    push_vert_floor(fr);
    push_vert_floor(fl);
    push_vert_floor(br);
}

void Background::create_floor(){
    vert bl, br, tl, tr;

    bl.x = 0;
    bl.z = 0;

    br.x = w;
    br.z = 0;

    tl.x = 0;
    tl.z = h;

    tr.x = w;
    tr.z = h;

    bl.y = 0;
    br.y = 0;
    tl.y = 0;
    tr.y = 0;

    push_vert_walls(tr);
    push_vert_walls(tl);
    push_vert_walls(br);
    push_vert_walls(bl);
    push_vert_walls(br);
    push_vert_walls(tl);
}

void Background::fill_walls(){
    floor_color.clear();
    for (auto i : floor){
        floor_color.push_back(1.0f);
        floor_color.push_back(1.0f);
        floor_color.push_back(1.0f);
        floor_color.push_back(1.0f);
    }
}

void Background::fill_floor(){
    wall_color.clear();
    for (auto i : floor){
        wall_color.push_back(0.2f);
        wall_color.push_back(0.2f);
        wall_color.push_back(1.0f);
        wall_color.push_back(1.0f);
    }
}

vector<float> Background::update(){
    walls.clear();
    floor.clear();
    create_floor();
    create_walls();
    for (auto i : floor){
        walls.push_back(i);
    }
    return walls;
}

vector<float> Background::fill(float r, float g, float b){
    fill_walls();
    fill_floor();
    for (auto i : floor_color){
        wall_color.push_back(i);
    }
    return wall_color;
}





///////////////////////////////// Rectangle /////////////////////////////////
Rectangle::Rectangle(){
    length = 1;
    width = 1;
    height = 1;
}

Rectangle::~Rectangle(){
    vertices.clear();
    color.clear();
}

void Rectangle::push_vert(vert corner){
    vertices.push_back(corner.x);
    vertices.push_back(corner.y);
    vertices.push_back(corner.z);
    vertices.push_back(1);
}

vector<float> Rectangle::update(){
    vertices.clear();
    vert blb, brb, flb, frb, blt, brt, flt, frt;
    // Back left bottom
    blb.x = 0;
    blb.y = 0;
    blb.z = 0;
    // back right bottom
    brb.x = 0;
    brb.y = width;
    brb.z = 0;
    // front left bottom
    flb.x = width;
    flb.y = 0;
    flb.z = 0;
    // front rigt top
    frb.x = width;
    frb.y = length;
    frb.z = 0;

    // Top corners
    blt = blb;
    blt.z = height;
    brt = brb;
    brt.z = height;
    flt = flb;
    flt.z = height;
    frt = frb;
    frt.z = height;

    // Pushing them into the vector
    // Notation front/back , left/right, top/bottom
    // ex. blb is back left bottom
    // Bottom face
    push_vert(blb);
    push_vert(brb);
    push_vert(flb);
    push_vert(flb);
    push_vert(frb);
    push_vert(brb);

    // Top face
    push_vert(blt);
    push_vert(brt);
    push_vert(flt);
    push_vert(flt);
    push_vert(frt);
    push_vert(brt);

    // Front face
    push_vert(flt);
    push_vert(frt);
    push_vert(frb);
    push_vert(flt);
    push_vert(flb);
    push_vert(frb);

    // Back face
    push_vert(blt);
    push_vert(brt);
    push_vert(brb);
    push_vert(blt);
    push_vert(blb);
    push_vert(brb);

    // Left face
    push_vert(flt);
    push_vert(blt);
    push_vert(blb);
    push_vert(flt);
    push_vert(flb);
    push_vert(blb);

    // Right face
    push_vert(frt);
    push_vert(brt);
    push_vert(brb);
    push_vert(frt);
    push_vert(frb);
    push_vert(brb);
    return vertices;
}

vector<float> Rectangle::fill(float r, float g, float b){ // Populates the color vector with desired color
    color.clear();
    for (auto i : vertices){
        color.push_back(r);
        color.push_back(g);
        color.push_back(b);
        color.push_back(1.0f);
    }
    return color;
}

void Rectangle::print(){
    for (auto i : vertices){
        cout << i << ", ";
    }
}

void Rectangle::delete_vertices(){
    vertices.clear();
}

///////////////////////////////// Sphere /////////////////////////////////

Sphere::Sphere(){
    r = 1;
    n = 100;
}

Sphere::~Sphere(){
    vertices.clear();
    color.clear();
}

void Sphere::push_vert(vert corner){
    vertices.push_back(corner.x);
    vertices.push_back(corner.y);
    vertices.push_back(corner.z);
    vertices.push_back(1);
}

// Eqaution of sphere 
// x = cos(u) * sin (v) * r
// y = cos(v) * r
// z = sin(u) * sin(v) * r
vector<float> Sphere::points(int i, int j){
    vector <float> combined;
        u = 2 * M_PI * (((float)i + 1) / n);
		v = M_PI * (((float)j + 1) / n);
        combined.push_back(cos(u) * sin(v) * r);
        combined.push_back(cos(v) * r);
        combined.push_back(sin(u) * sin(v) * r);
        return combined;
}

void Sphere::sort_verts(vector<float> temp){
    vert bl, br, tl, tr;
    bl.x = temp[0];
    bl.y = temp[1];
    bl.z = temp[2];

    br.x = temp[3];
    br.y = temp[4];
    br.z = temp[5];
    
    tl.x = temp[6];
    tl.y = temp[7];
    tl.z = temp[8];

    tr.x = temp[9];
    tr.y = temp[10];
    tr.z = temp[11];

    //Making the bottom left triangle of the rectangle
    push_vert(bl);
    push_vert(br);
    push_vert(tl);

    //Making the top right triangle
    push_vert(tl);
    push_vert(tr);
    push_vert(br);
}

vector<float> Sphere::update(){
    vertices.clear();
    vector<float> temp;
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j ++){
            temp = points(i, j);
            temp = points(i + 1, j);
            temp = points(i, j + 1);
            temp = points(i + 1, j + 1);
            sort_verts(temp);
        }
    }
    return vertices;
}

vector<float> Sphere::fill(float r, float g, float b){
    color.clear();
    for (auto i : vertices){
        color.push_back(r);
        color.push_back(g);
        color.push_back(b);
        color.push_back(1.0f);
    }
    return color;
}

void Sphere::print(){
    for (auto i : vertices){
        cout << i << ", ";
    }
}

void Sphere::delete_vertices(){
    vertices.clear();
};


///////////////////////////////// Cone /////////////////////////////////



///////////////////////////////// Pyramid /////////////////////////////////

Pyramid::Pyramid(){
    l = 1;
    w = 1;
    h = 1;
}

Pyramid::~Pyramid(){
    vertices.clear();
    color.clear();
}

void Pyramid::push_vert(vert corner){
    vertices.push_back(corner.x);
    vertices.push_back(corner.y);
    vertices.push_back(corner.z);
    vertices.push_back(1);
}

vector<float> Pyramid::update(){
    vertices.clear();
    vert bl, br, fl, fr, top;
    // creating vertices
    // Back left
    bl.x = 0;
    bl.y = 0;
    bl.z = 0;

    // Back right
    br.x = w;
    br.y = 0;
    br.z = 0;

    // Front left
    fl.x = 0;
    fl.y = l;
    fl.z = 0;

    // Front right
    fr.x = w;
    fr.y = l;
    fr.z = 0;

    // Top point
    top.x = w / 2;
    top.y = l / 2;
    top.z = h;  

    // Creating triangles  
    // Base
    push_vert(bl);
    push_vert(br);
    push_vert(fl);
    push_vert(bl);
    push_vert(fr);
    push_vert(fl);

    // Face 1
    push_vert(fl);
    push_vert(top);
    push_vert(fr);

    // Face 2
    push_vert(fr);
    push_vert(top);
    push_vert(br);

    // Face 3
    push_vert(br);
    push_vert(top);
    push_vert(bl);

    // Face 4
    push_vert(bl);
    push_vert(top);
    push_vert(fl);

    return vertices;
}

vector<float> Pyramid::fill(float r, float g, float b){ // Populates the color vector with desired color
    color.clear();
    for (auto i : vertices){
        color.push_back(r);
        color.push_back(g);
        color.push_back(b);
        color.push_back(1.0f);
    }
    return color;
}

void Pyramid::print(){
    for (auto i : vertices){
        cout << i << ", ";
    }
}

void Pyramid::delete_vertices(){
    vertices.clear();
}