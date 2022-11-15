#include "shapes.h"


Rectangle::Rectangle(){
    length = 1;
    width = 1;
    height = 1;
};

Rectangle::~Rectangle(){
    vertices.clear();
    color.clear();
};

void Rectangle::push_vert(vert corner){
    vertices.push_back(corner.x);
    vertices.push_back(corner.y);
    vertices.push_back(corner.z);
    vertices.push_back(1);
};

vector<float> Rectangle::update(){
    vertices.clear();
    vert point;

    // Need to calculate the 8 corners in a rectangle
    // Centered?
};

vector<float> Rectangle::fill(float r, float g, float b){ // Populates the color vector with desired color
    color.clear();
    for (auto i : vertices){
        color.push_back(r);
        color.push_back(g);
        color.push_back(b);
        color.push_back(1.0f);
    }
    return color;
}; 

void Rectangle::print(){
    for (auto i : vertices){
        cout << i << ", ";
    }
};

void Rectangle::delete_vertices(){
    vertices.clear();
};

///////////////////////////////// Rectangle /////////////////////////////////