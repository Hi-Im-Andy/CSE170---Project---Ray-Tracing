#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include "shader.h"
#include "shaderprogram.h"
#include "shapes.h"
#include "shapes.cpp"
#include <vector>

/*=================================================================================================
	DOMAIN
=================================================================================================*/

// Window dimensions
const int InitWindowWidth  = 800;
const int InitWindowHeight = 800;
int WindowWidth  = InitWindowWidth;
int WindowHeight = InitWindowHeight;

// Last mouse cursor position
int LastMousePosX = 0;
int LastMousePosY = 0;

// Arrays that track which keys are currently pressed
bool key_states[256];
bool key_special_states[256];
bool mouse_states[8];

// Other parameters
bool draw_wireframe = false;
/*=================================================================================================
	SHADERS & TRANSFORMATIONS
=================================================================================================*/

ShaderProgram PassthroughShader;
ShaderProgram PerspectiveShader;

glm::mat4 PerspProjectionMatrix( 1.0f );
glm::mat4 PerspViewMatrix( 1.0f );
glm::mat4 PerspModelMatrix( 1.0f );

float perspZoom = 1.0f, perspSensitivity = 0.35f;
float perspRotationX = 0.0f, perspRotationY = 0.0f;

/*=================================================================================================
	OBJECTS
=================================================================================================*/
// Objects included in the classes

/*=================================================================================================
	HELPER FUNCTIONS
=================================================================================================*/

void window_to_scene( int wx, int wy, float& sx, float& sy )
{
	sx = ( 2.0f * (float)wx / WindowWidth ) - 1.0f;
	sy = 1.0f - ( 2.0f * (float)wy / WindowHeight );
}

/*=================================================================================================
	SHADERS
=================================================================================================*/

void CreateTransformationMatrices( void )
{
	// PROJECTION MATRIX
	PerspProjectionMatrix = glm::perspective<float>( glm::radians( 60.0f ), (float)WindowWidth / (float)WindowHeight, 0.01f, 1000.0f );

	// VIEW MATRIX
	glm::vec3 eye   ( 0.0, 0.0, 2.0 );
	glm::vec3 center( 0.0, 0.0, 0.0 );
	glm::vec3 up    ( 0.0, 1.0, 0.0 );

	PerspViewMatrix = glm::lookAt( eye, center, up );

	// MODEL MATRIX
	PerspModelMatrix = glm::mat4( 1.0 );
	PerspModelMatrix = glm::rotate( PerspModelMatrix, glm::radians( perspRotationX ), glm::vec3( 1.0, 0.0, 0.0 ) );
	PerspModelMatrix = glm::rotate( PerspModelMatrix, glm::radians( perspRotationY ), glm::vec3( 0.0, 1.0, 0.0 ) );
	PerspModelMatrix = glm::scale( PerspModelMatrix, glm::vec3( perspZoom ) );
}

void CreateShaders( void )
{
	// Renders without any transformations
	PassthroughShader.Create( "./shaders/simple.vert", "./shaders/simple.frag" );

	// Renders using perspective projection
	PerspectiveShader.Create( "./shaders/persp.vert", "./shaders/persp.frag" );
}

/*=================================================================================================
	Classes
=================================================================================================*/
// Test
Background bg;
// Rectangle rec;
// Sphere sph;
// Pyramid pyr;

// Train
int t_x = 50;
int t_y = -10;
int t_z = -75;
Sphere end1(2, 10, t_x+30, t_y+2, t_z+1);
Sphere end2(2, 10, t_x, t_y+2, t_z+1);
Rectangle b1(6, 4, 4, t_x, t_y, t_z-1);
Rectangle b2(6, 4, 4, t_x+8, t_y, t_z-1);
Rectangle b3(6, 4, 4, t_x+16, t_y, t_z-1);
Rectangle b4(6, 4, 4, t_x+24, t_y, t_z-1);
Rectangle lower(30, 2, 2, t_x, t_y, t_z);

// Row 1
Rectangle r1b1(15, 40, 15, -50, -10, -100);
Rectangle r1b2(20, 20, 7.5, -35, -10, -100);
Rectangle r1b3(10, 50, 10, -15, -10, -100);
Rectangle r1b4(10, 40, 10, -15, -10, -90);
Rectangle r1b5(10, 30, 10, -5, -10, -100);
Rectangle r1b6(10, 20, 10, -5, -10, -90);
Rectangle r1b7(15, 40, 15, 35, -10, -100);
Rectangle r1b8(20, 20, 7.5, 10, -10, -100);

// Row 2
Rectangle r2b1(15, 25, 15, -50, -10, -65);
Rectangle r2b2(10, 40, 10, -47.5, -10, -62.5);
Rectangle r2b3(5, 55, 5, -45, -10, -60);

Pyramid r2b4();

Rectangle r2b5(15, 25, 15, 35, -10, -65);
Sphere r2b6(7.5, 30 , 42.5, 15, -57.5);

// Row 3
Sphere r3b1(10, 30, -40, -10, -10);
Rectangle r3b2(10, 10, 10, -45, -15, -20);
Rectangle r3b3(10, 20, 20, -20, -10, -20);
Rectangle r3b4(10, 20, 20, 10, -10, -20);
Rectangle r3b5(20, 60, 20, 30, -10, -20);

/*=================================================================================================
	Moving
=================================================================================================*/

void move_train(float x, float y, float z){
	end1.change_x(x);
	end2.change_x(x);
	b1.change_x(x);
	b2.change_x(x);
	b3.change_x(x);
	b4.change_x(x);
	lower.change_x(x);

	end1.change_y(y);
	end2.change_y(y);
	b1.change_y(y);
	b2.change_y(y);
	b3.change_y(y);
	b4.change_y(y);
	lower.change_y(y);

	end1.change_z(z);
	end2.change_z(z);
	b1.change_z(z);
	b2.change_z(z);
	b3.change_z(z);
	b4.change_z(z);
	lower.change_z(z);
}

/*=================================================================================================
	BUFFERS
=================================================================================================*/

void CreateAxisBuffers( void )
{
	// test
	bg.buffer();
	// rec.buffer();
	// sph.buffer();
	// pyr.buffer();

	// Row 1
	r1b1.buffer();
	r1b2.buffer();
	r1b3.buffer();
	r1b4.buffer();
	r1b5.buffer();
	r1b6.buffer();
	r1b7.buffer();
	r1b8.buffer();

	// Row 2
	r2b1.buffer();
	r2b2.buffer();
	r2b3.buffer();
	r2b5.buffer();
	r2b6.buffer();

	// Row 3
	r3b1.buffer();
	r3b2.buffer();
	r3b3.buffer();
	r3b4.buffer();
	r3b5.buffer();

	// Train
	lower.buffer();
	end1.buffer();
	end2.buffer();
	b1.buffer();
	b2.buffer();
	b3.buffer();
	b4.buffer();
}

/*=================================================================================================
	CALLBACKS
=================================================================================================*/

//-----------------------------------------------------------------------------
// CALLBACK DOCUMENTATION
// https://www.opengl.org/resources/libraries/glut/spec3/node45.html
// http://freeglut.sourceforge.net/docs/api.php#WindowCallback
//-----------------------------------------------------------------------------

void idle_func()
{
	//uncomment below to repeatedly draw new frames
	glutPostRedisplay();
}

void reshape_func( int width, int height )
{
	WindowWidth  = width;
	WindowHeight = height;

	glViewport( 0, 0, width, height );
	glutPostRedisplay();
}

void keyboard_func( unsigned char key, int x, int y )
{
	key_states[ key ] = true;

	switch( key )
	{
		case ' ': // Used for the wireframe
		{	
			draw_wireframe = !draw_wireframe;
			if( draw_wireframe == true )
				std::cout << "Wireframes on.\n";
			else
				std::cout << "Wireframes off.\n";
			break;
		}

		case 'w': // Increment r radius (by a small value)
		{
			for(int i = 0; i < 10; i++){
				move_train(-i, 0, 0);
				CreateAxisBuffers();
			}
			break;
		}

		// Exit on escape key press
		case '\x1B':
		{
			exit( EXIT_SUCCESS );
			break;
		}
	}
}

void key_released( unsigned char key, int x, int y )
{
	key_states[ key ] = false;
}

void key_special_pressed( int key, int x, int y )
{
	key_special_states[ key ] = true;
}

void key_special_released( int key, int x, int y )
{
	key_special_states[ key ] = false;
}

void mouse_func( int button, int state, int x, int y )
{
	// Key 0: left button
	// Key 1: middle button
	// Key 2: right button
	// Key 3: scroll up
	// Key 4: scroll down

	if( x < 0 || x > WindowWidth || y < 0 || y > WindowHeight )
		return;

	float px, py;
	window_to_scene( x, y, px, py );

	if( button == 3 )
	{
		perspZoom += 0.03f;
	}
	else if( button == 4 )
	{
		if( perspZoom - 0.03f > 0.0f )
			perspZoom -= 0.03f;
	}

	mouse_states[ button ] = ( state == GLUT_DOWN );

	LastMousePosX = x;
	LastMousePosY = y;
}

void passive_motion_func( int x, int y )
{
	if( x < 0 || x > WindowWidth || y < 0 || y > WindowHeight )
		return;

	float px, py;
	window_to_scene( x, y, px, py );

	LastMousePosX = x;
	LastMousePosY = y;
}

void active_motion_func( int x, int y )
{
	if( x < 0 || x > WindowWidth || y < 0 || y > WindowHeight )
		return;

	float px, py;
	window_to_scene( x, y, px, py );

	if( mouse_states[0] == true )
	{
		perspRotationY += ( x - LastMousePosX ) * perspSensitivity;
		perspRotationX += ( y - LastMousePosY ) * perspSensitivity;
	}

	LastMousePosX = x;
	LastMousePosY = y;
}


/*=================================================================================================
	RENDERING
=================================================================================================*/
void display_func( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	CreateTransformationMatrices();

	PerspectiveShader.Use();
	PerspectiveShader.SetUniform( "projectionMatrix", glm::value_ptr( PerspProjectionMatrix ), 4, GL_FALSE, 1 );
	PerspectiveShader.SetUniform( "viewMatrix", glm::value_ptr( PerspViewMatrix ), 4, GL_FALSE, 1 );
	PerspectiveShader.SetUniform( "modelMatrix", glm::value_ptr( PerspModelMatrix ), 4, GL_FALSE, 1 );

	if( draw_wireframe == true )
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	// Display the shapes
	// Test
	bg.display();
	// rec.display();
	// sph.display();
	// pyr.display();

	r1b1.display();
	r1b2.display();
	r1b3.display();
	r1b4.display();
	r1b5.display();
	r1b6.display();
	r1b7.display();
	r1b8.display();

	// Row 2
	r2b1.display();
	r2b2.display();
	r2b3.display();

	r2b5.display();
	r2b6.display();

	// Row 3
	r3b1.display();
	r3b2.display();
	r3b3.display();
	r3b4.display();
	r3b5.display();

	lower.display();
	end1.display();
	end2.display();
	b1.display();
	b2.display();
	b3.display();
	b4.display();

	glBindVertexArray( 0 );

	if( draw_wireframe == true )
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	glutSwapBuffers();
}

/*=================================================================================================
	INIT
=================================================================================================*/

void init( void )
{
	// Print some info
	std::cout << "Vendor:         " << glGetString( GL_VENDOR   ) << "\n";
	std::cout << "Renderer:       " << glGetString( GL_RENDERER ) << "\n";
	std::cout << "OpenGL Version: " << glGetString( GL_VERSION  ) << "\n";
	std::cout << "GLSL Version:   " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << "\n\n";

	// Set OpenGL settings
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); // background color
	glEnable( GL_DEPTH_TEST ); // enable depth test
	glEnable( GL_CULL_FACE ); 	// enable back-face culling // Commented out to show triangles

	// Create shaders
	CreateShaders();

	// Create buffers
	CreateAxisBuffers();

	std::cout << "Finished initializing...\n\n";
}

/*=================================================================================================
	MAIN
=================================================================================================*/
int main( int argc, char** argv )
{
	glutInit( &argc, argv );

	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( InitWindowWidth, InitWindowHeight );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

	glutCreateWindow( "CSE-170 Computer Graphics" );

	// Initialize GLEW
	GLenum ret = glewInit();
	if( ret != GLEW_OK ) {
		std::cerr << "GLEW initialization error." << std::endl;
		glewGetErrorString( ret );
		return -1;
	}

	glutDisplayFunc( display_func );
	glutIdleFunc( idle_func );
	glutReshapeFunc( reshape_func );
	glutKeyboardFunc( keyboard_func );
	glutKeyboardUpFunc( key_released );
	glutSpecialFunc( key_special_pressed );
	glutSpecialUpFunc( key_special_released );
	glutMouseFunc( mouse_func );
	glutMotionFunc( active_motion_func );
	glutPassiveMotionFunc( passive_motion_func );

	init();

	glutMainLoop();

	return EXIT_SUCCESS;
}