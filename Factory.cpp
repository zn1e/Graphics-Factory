// ---------------------------------------------------------
// COSC363: Computer Graphics (2025)
// Assignment 1: Graphics Factory
//
// <Description of the scene>
//
//
// ---------------------------------------------------------

#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include "loadTGA.h"
#include "Models.h"

using namespace std;

#define TO_RADIANS 3.14159/180.

GLuint txId[2]; // texture ids

// Define global variables
float eye_x, eye_z, look_x, look_z, angle = 0; // camera params

// Load and bind textures
void loadTexture() {
	glGenTextures(2, txId); // Create 2 texture ids

	glBindTexture(GL_TEXTURE_2D, txId[0]);	//Use this texture
	loadTGA("floor.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

// Keyboard key event call back
void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
		case 'a': angle -= 5; break; // turn direction
		case 'd': angle += 5; break;
		case 's': // move backward
			eye_x -= 0.1 * sin(angle * TO_RADIANS);
			eye_z += 0.1 * cos(angle * TO_RADIANS);
			break;
		case 'w': // move forward
			eye_x += 0.1 * sin(angle * TO_RADIANS);
			eye_z -= 0.1 * cos(angle * TO_RADIANS);
			break;
	}

	look_x = eye_x + 100 * sin(angle * TO_RADIANS);
	look_z = eye_z - 100 * cos(angle * TO_RADIANS);
	glutPostRedisplay();
}

//-- Draw a floor plane ----------------------------------------------------
void floor() {
	glBindTexture(GL_TEXTURE_2D, txId[0]);  //replace with a texture

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 16.0f);
		glVertex3f(-30, -1, -30);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-30, -1, 30);

		glTexCoord2f(16.0f, 0.0f);
		glVertex3f(30, -1, 30);

		glTexCoord2f(16.0f, 16.0f);
		glVertex3f(30, -1, -30);
	glEnd();
}

// Main display module that generates the scene.
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//GL_LINE = Wireframe;   GL_FILL = Solid

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_x, 0., eye_z, look_x, 0., look_z, 0., 1., 0.);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45., 1., 1., 500.);  //The camera view volume  
	
	glDisable(GL_LIGHTING);
	floor();

	pillar();
	glEnable(GL_LIGHTING);

	glutSwapBuffers();
}

// Initialize OpenGL parameters  
void initialize() {
	glClearColor(0., 1., 1., 1.);	//Background colour
	
	loadTexture();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

}

// Main: Initialize glut window and register call backs 
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1280)/2, (glutGet(GLUT_SCREEN_HEIGHT) - 480)/2); // center window with 1280 x 480 size
	glutCreateWindow("Graphics Factory");
	initialize();

	glutDisplayFunc(display);
	// glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0; 
}
