#include "shapes.h"
#include <iostream>

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

///////////////////////////////// Rectangle /////////////////////////////////