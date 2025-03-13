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

using namespace std;

#define TO_RADIANS 3.14159/180.

GLuint txId[2]; // texture ids

// Define global variables
float eye_x, eye_z, look_x, look_z = -1, angle = 0; // camera params

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
			eye_x += 0.1 *sin(angle * TO_RADIANS);
			eye_z -= 0.1 * cos(angle * TO_RADIANS);
			break;
	}

	look_x = eye_x + 100 * sin(angle * TO_RADIANS);
	look_z = eye_z - 100 * cos(angle * TO_RADIANS);
	glutPostRedisplay();
}

//-- Draw a floor plane ----------------------------------------------------
void drawFloor() {
	glBindTexture(GL_TEXTURE_2D, txId[0]);  //replace with a texture

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 20.0f);
		glVertex3f(-30, -1, -30);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-30, -1, 30);

		glTexCoord2f(20.0f, 0.0f);
		glVertex3f(30, -1, 30);

		glTexCoord2f(20.0f, 20.0f);
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
	gluPerspective(45., 1., 1., 100.);  //The camera view volume  
	
	drawFloor();

	glutSwapBuffers();
}
// Initialize OpenGL parameters  
void initialize() {
	loadTexture();
	glEnable(GL_TEXTURE_2D);
	glClearColor(0., 1., 1., 1.);	//Background colour
	glEnable(GL_DEPTH_TEST);
}

//-- Main: Initialize glut window and register call backs ------------------
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphics Factory");
	initialize();

	glutDisplayFunc(display);
	// glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0; 
}
