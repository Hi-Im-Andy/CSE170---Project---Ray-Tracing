#include "shapes.h"
#include <iostream>


///////////////////////////////// Background /////////////////////////////////
Background::Background(){
    w = 10;
    l = 10;
    h = 10;
    x = -5;
    y = -5;
    z = -10;
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
    bl.x = x;
    bl.y = y;

    br.x = x + w;
    br.y = y;

    fl.x = x;
    fl.y = y + l;

    fr.x = x + w;
    fr.y = y + l;

    bl.z = z;
    br.z = z;
    fl.z = z;
    fr.z = z;

    push_vert_floor(bl);
    push_vert_floor(br);
    push_vert_floor(fl);
    push_vert_floor(fr);
    push_vert_floor(fl);
    push_vert_floor(br);
}

void Background::create_floor(){
    vert bl, br, tl, tr;

    bl.x = x;
    bl.z = z;

    br.x = x + w;
    br.z = z;

    tl.x = x;
    tl.z = z + h;

    tr.x = x + w;
    tr.z = z + h;

    bl.y = y;
    br.y = y;
    tl.y = y;
    tr.y = y;

    push_vert_walls(tl);
    push_vert_walls(tr);
    push_vert_walls(br);
    push_vert_walls(br);
    push_vert_walls(bl);
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

void  Background::update(){
    walls.clear();
    floor.clear();
    create_floor();
    create_walls();
    for (auto i : floor){
        walls.push_back(i);
    }
}

vector<float> Background::fill(float r, float g, float b){
    fill_walls();
    fill_floor();
    for (auto i : floor_color){
        wall_color.push_back(i);
    }
    return wall_color;
}

void Background::buffer(){
    update(); // Getting the vector from the torus class
	std::vector<float> color = fill(1, 1, 1); // Color vector

	glGenVertexArrays( 1, &axis_VAO );
	glBindVertexArray( axis_VAO );

	glGenBuffers( 2, &axis_VBO[0] );

	glBindBuffer( GL_ARRAY_BUFFER, axis_VBO[0] );
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * walls.size(), &walls[0], GL_STATIC_DRAW); // Changed to match the vector input of the float as well as the address of the vector
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, axis_VBO[1] );
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * color.size(), &color[0], GL_STATIC_DRAW);
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 1 );

	glBindVertexArray( 0 );
}

void Background::display(){
	glBindVertexArray( axis_VAO );
	glDrawArrays( GL_TRIANGLES, 0, walls.size ()); //Similar result with GL_TRIANGLE_STRIP and GL_TRIANGLES
}





///////////////////////////////// Rectangle /////////////////////////////////
Rectangle::Rectangle(){
    length = 1;
    width = 1;
    height = 1;
    x = -3;
    y = -3;
    z = -3;
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

void Rectangle::update(){
    vertices.clear();
    vert blb, brb, flb, frb, blt, brt, flt, frt;
    // Back left bottom
    blb.x = x;
    blb.y = y;
    blb.z = z;
    // back right bottom
    brb.x = x;
    brb.y = y + width;
    brb.z = z;
    // front left bottom
    flb.x = x + width;
    flb.y = y;
    flb.z = z;
    // front rigt top
    frb.x = x + width;
    frb.y = y + length;
    frb.z = z;

    // Top corners
    blt = blb;
    blt.z = z + height;
    brt = brb;
    brt.z = z + height;
    flt = flb;
    flt.z = z + height;
    frt = frb;
    frt.z = z + height;

    // Pushing them into the vector
    // Notation front/back , left/right, top/bottom
    // ex. blb is back left bottom
    // Back face
    push_vert(blb);
    push_vert(brb);
    push_vert(flb);
    push_vert(frb);
    push_vert(flb);
    push_vert(brb);

    // Front face
    push_vert(brt);
    push_vert(blt);
    push_vert(flt);
    push_vert(flt);
    push_vert(frt);
    push_vert(brt);

    // Right face
    push_vert(frt);
    push_vert(flt);
    push_vert(frb);
    push_vert(flt);
    push_vert(flb);
    push_vert(frb);

    // Left face
    push_vert(blt);
    push_vert(brt);
    push_vert(brb);
    push_vert(blb);
    push_vert(blt);
    push_vert(brb);

    // Left face
    push_vert(flt);
    push_vert(blt);
    push_vert(blb);
    push_vert(flb);
    push_vert(flt);
    push_vert(blb);

    // Right face
    push_vert(brt);
    push_vert(frt);
    push_vert(brb);
    push_vert(frt);
    push_vert(frb);
    push_vert(brb);
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

void Rectangle::buffer(){
    update();
	vector<float> color_rec = fill(1, 1, 1); // Color vector

	glGenVertexArrays( 1, &rec_VAO );
	glBindVertexArray( rec_VAO );

	glGenBuffers( 2, &rec_VBO[0] );

	glBindBuffer( GL_ARRAY_BUFFER, rec_VBO[0] );
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // Changed to match the vector input of the float as well as the address of the vector
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, rec_VBO[1] );
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * color.size(), &color_rec[0], GL_STATIC_DRAW);
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 1 );

	glBindVertexArray( 0 );
}

void Rectangle::display(){
    glBindVertexArray( rec_VAO );
	glDrawArrays( GL_TRIANGLES, 0, vertices.size());
}

void Rectangle::delete_vertices(){
    vertices.clear();
}

///////////////////////////////// Sphere /////////////////////////////////

Sphere::Sphere(){
    r = 0.5;
    n = 10;
    x = -2;
    y = -2;
    z = -4;
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
// x = r * cos(u) * sin(v)
// y = r * sin(u) * sin(v)
// z = r * cos(v)
// u ranges from 0 to 2pi
// v ranges from 0 to pi
vector<float> Sphere::points(int i, int j){
    vector <float> combined;
        u = ((2 * M_PI / n) * i);
        v = ((M_PI / n) * j);

        tempX = r * cos(u) * sin(v);
        tempY = r * sin(u) * sin(v);
        tempZ = r * cos(v);
        combined.push_back(tempX);
        combined.push_back(tempY);
        combined.push_back(tempZ);
        return combined;
}

void Sphere::sort_verts(vector<vector<float>> temp){
    vert bl, br, tl, tr;
    bl.x = x + temp[0][0];
    bl.y = y + temp[0][1];
    bl.z = z + temp[0][2];

    br.x = x + temp[1][0];
    br.y = y + temp[1][1];
    br.z = z + temp[1][2];

    
    tl.x = x + temp[2][0];
    tl.y = y + temp[2][1];
    tl.z = z + temp[2][2];

    tr.x = x + temp[3][0];
    tr.y = y + temp[3][1];
    tr.z = z + temp[3][2];

    //Making the bottom left triangle of the rectangle
    push_vert(br);
    push_vert(bl);
    push_vert(tl);

    //Making the top right triangle
    push_vert(tl);
    push_vert(tr);
    push_vert(br);
}

void Sphere::update(){
    vertices.clear();
    vector<vector<float>> temp;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){ 
            temp.push_back(points(i, j));
            temp.push_back(points(i + 1, j));
            temp.push_back(points(i, j + 1));
            temp.push_back(points(i + 1, j + 1));
            sort_verts(temp);
            temp.clear();
        }
    }
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

void Sphere::buffer(){
	update();
	vector<float> color_sp = fill(1, 1, 1); // Color vector

	glGenVertexArrays( 1, &sp_VAO );
	glBindVertexArray( sp_VAO );

	glGenBuffers( 2, &sp_VBO[0] );

	glBindBuffer( GL_ARRAY_BUFFER, sp_VBO[0] );
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // Changed to match the vector input of the float as well as the address of the vector
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, sp_VBO[1] );
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * color_sp.size(), &color_sp[0], GL_STATIC_DRAW);
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 1 );

	glBindVertexArray( 0 );
}

void Sphere::display(){
	glBindVertexArray( sp_VAO );
	glDrawArrays( GL_TRIANGLES, 0, vertices.size ()); 
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
    x = 0;
    y = 0;
    z = 0;
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

void Pyramid::update(){
    vertices.clear();
    vert bl, br, fl, fr, top;
    // creating vertices
    // Back left
    bl.x = x;
    bl.y = y;
    bl.z = z;

    // Back right
    br.x = x + w;
    br.y = y;
    br.z = z;

    // Front left
    fl.x = x;
    fl.y = y + l;
    fl.z = z;

    // Front right
    fr.x = x + w;
    fr.y = y + l;
    fr.z = z;

    // Top point
    top.x = (x + w) / 2;
    top.y = (y + l) / 2;
    top.z = z + h;  

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

void Pyramid::buffer(){
    update();
	vector<float> color_py = fill(1, 1, 1); // Color vector
	cout << " updated " << std::endl;

	glGenVertexArrays( 1, &py_VAO );
	glBindVertexArray( py_VAO );

	glGenBuffers( 2, &py_VBO[0] );

	glBindBuffer( GL_ARRAY_BUFFER, py_VBO[0] );
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // Changed to match the vector input of the float as well as the address of the vector
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 0 );

	glBindBuffer( GL_ARRAY_BUFFER, py_VBO[1] );
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * color_py.size(), &color_py[0], GL_STATIC_DRAW);
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void*)0 );
	glEnableVertexAttribArray( 1 );

	glBindVertexArray( 0 );
}

void Pyramid::display(){
    glBindVertexArray( py_VAO );
	glDrawArrays( GL_TRIANGLES, 0, vertices.size ());
}

void Pyramid::delete_vertices(){
    vertices.clear();
}