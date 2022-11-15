#pragma once
#include <math.h>
#include <vector>

//R is the radius of the torus
//r is the radius of the tube
//X(theta, phi) = (R + r cos(theta)) cos(phi) 
//Y(theta, phi) = (R + r cos(theta)) sin(phi)
//Z(theta, phi) =  r sin(theta)
//Theta and phi are the values that make a full cirlce and start and end at the same point

// Alternative functions
// X = Rcos(u) + rcos(u) cos(v)
// Y = Rsin(u) + rsin(u) cos(v)
// Z = rsin(v)
// v all values from 0 - 2pi
// u all values from 0 - 2pi
// u = 2pi ((index i + 1) / n)
// v = 2pi ((index j + 1) / n)

// Relationship between n, torus_vertices[], and X[] Y[] Z[]
// X[n*n] since there is a nested for loop that loops n times
// torus_vertices[] holds X[] Y[] Z[], therefore it needs to hold 3 * (n*n)


class torus{
    float r, R;
    float n, sides;
    std::vector <float> vec; // Vector used to store the vertices
    std::vector <float> color; // Vector used to store the color of the vertices
    const double PI = M_PI; // Used to store pi for later use
    struct Vertice {float x, y, z, w;};
    public:

        torus(){ //Arbitrary starting points for the torus
            r = 1;
            R = 3;
            n = 20;
            sides = n*n;
        }

        Vertice points(int i, int j){
            Vertice combined; // Used to the x, y, z values that make up a point
            float u, v; // Alternatively theta and phi
            u = 2 * PI * (((float)i + 1) / n);
			v = 2 * PI * (((float)j + 1) / n);
            //Calculation explinations are at the top
            combined.x = R * cos(u) + r * cos(u) * cos(v); 
            combined.y = R * sin(u) + r * sin(u) * cos(v);
            combined.z = r * sin(v);
            // std::cout << combined.x << ", " << combined.y << ", " << combined.z << std::endl; // Printing out the x, y, z
            return combined;
        };

        void push_vert (Vertice combined){
            vec.push_back(combined.x);
            vec.push_back(combined.y);
            vec.push_back(combined.z);
            vec.push_back(1); // Acts as a spacer
        };

        std::vector<float> update(){ // Method used to calculate and store the vertices
	        // int  count = 0;
	        vec.clear(); //Have to clear the vector if it is updated so that previous values will be removed

            for(int i = 0; i < n; i++){
		        for (int j = 0; j < sides; j++){
                    // Store this information into a point
                    // As their names suggest, there are 4 points that make up a rectangle
                    // Later on used to make two attached triangles

                    Vertice bottom_left = points(i, j);
                    Vertice bottom_right = points(i + 1, j);
                    Vertice top_left = points(i, j + 1);
                    Vertice top_right = points(i + 1, j + 1);

                    //Making the bottom left triangle of the rectangle
                    push_vert(bottom_left);
                    push_vert(bottom_right);
                    push_vert(top_left);

                    //Making the top right triangle
                    push_vert(top_left);
                    push_vert(top_right);
                    push_vert(bottom_right);

                    // Populating the coordinates for the vertices
                    // Populating the array as [x1...y1...z1...] 
			        // X[count] = x;
			        // Y[count] = y;
			        // Z[count] = z;
			        // count++;
                    // Had to change this so that I could make the 4 point rectangle and not all in order
		        }
            }

            return vec;  // Returns the vector storing vertices
        }

        std::vector<float> color_fill(){ //giving an rgb value to the vertices
            color.clear();
            for (auto i : vec) { // For every vertice, gives an rgb value in this case white
		        color.push_back(1.f);
		        color.push_back(1.f);
		        color.push_back(1.f);
		        color.push_back(1.f);
	        }
            return color;
        }

        // The rest of these methods are modifiers / do what the methods say
        void print(){
            for (auto i : vec){
                std::cout << i << ", ";
            }
        }

        void change_n(int new_n){
            if (new_n > 0){
                n = new_n;
                sides = n * n;
            }
        }

        void change_R(double new_R){
            if(new_R > 0){
                R = new_R;
            }
        }

        void change_r(double new_r){
            if(new_r > 0){
                r = new_r;
            }
        } 

        int get_n(){
            return n;
        }

        int get_sides(){
            return sides;
        }

        float get_R(){
            return R;
        }
        float get_r(){
            return r;
        }
        void delete_vec(){
            vec.clear();
        }
};
