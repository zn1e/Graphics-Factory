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
#include "Models.h"

using namespace std;

#define TO_RADIANS M_PI/180.


struct Camera {
	float x, y, z; // position
	float yaw, pitch; // rotation
} camera = {0, 1, 20, 0, 0}; // initial cam position

bool toggle_wireframe = 0;

// Restrict camera pitch
void clampPitch(float &pitch) {
	if (pitch > 120.) pitch = 120.;
	if (pitch < -120.) pitch = -120.;
}

// Update camera position based on movement direction
void moveCamera(float speed) {
	camera.x += speed * sin(camera.yaw * TO_RADIANS);
	camera.z -= speed * cos(camera.yaw * TO_RADIANS);
}

// Keyboard key event call back
void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
		case 'a': camera.yaw -= 5; break; // rotate left
		case 'd': camera.yaw += 5; break; // rotate right
		case 's': moveCamera(-0.2); break; // move backward
		case 'w': moveCamera(0.2); break; // move forward
		case 'q': // toggle wireframe
			toggle_wireframe = !toggle_wireframe;
			if (toggle_wireframe) {
				glDisable(GL_LIGHTING);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			} else {
				glEnable(GL_LIGHTING);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			break;
	}

	glutPostRedisplay();
}

// Mouse motion callback for looking up/down
void mouseMotion(int x, int y) {
	static int lastX = x, lastY = y; // to store the previous motion
	float sensitivity = 0.01;

	camera.yaw += (x - lastX) * sensitivity;
	camera.pitch -= (y - lastY) * sensitivity;
	clampPitch(camera.pitch);

	lastX = x;
	lastY = y;

	glutPostRedisplay();
}


//-- Draw a floor plane ----------------------------------------------------
void floor() {
	float white[4] = {1., 1., 1., 1.};
	float black[4] = {0., 0., 0., 1.};
	glColor4f(0.7, 0.7, 0.7, 1.0);
	glNormal3f(0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);

	for(int i = -50; i <= 50; i++)  {
		glBegin(GL_LINES);      //A set of grid lines on the xz-plane
			glVertex3f(-50., -0.75, i);
			glVertex3f( 50., -0.75, i);
			glVertex3f(i, -0.75, -50.);
			glVertex3f(i, -0.75,  50.);
		glEnd();
	}

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
}

// Continuously update animation in idle
void idle() {
	animate();
	glutPostRedisplay();
}


// Main display module that generates the scene.
void display() {
	float lpos[4] = {5., 50., 5., 1.}; // light's position

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	glColor3f(1., 1., 1.);
	glEnable(GL_TEXTURE_2D);

	drawSkySphere(50.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float lookX = camera.x + cos(camera.pitch * TO_RADIANS) * sin(camera.yaw * TO_RADIANS);
	float lookY = camera.y + sin(camera.pitch * TO_RADIANS);
	float lookZ = camera.z - cos(camera.pitch * TO_RADIANS) * cos(camera.yaw * TO_RADIANS);

	gluLookAt(camera.x, camera.y, camera.z, lookX, lookY, lookZ, 0., 1., 0.);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	
	glEnable(GL_LIGHTING);
	

	//glColor3f(1., 1., 1.);
	pillars();

	//glColor3f(1., 1., 1.);
	cylinder();

	//glColor3f(0.55, 0.35, 0.07);
	conveyor();

	//glColor3f(0.55, 0.35, 0.07);
	getBox();

	//glColor3f(1., 0., 0.);
	spinFan();

	boxWithShadow();

	drawTank();

	glutSwapBuffers();
}

// Initialize OpenGL parameters  
void initialize() {
	loadTexture();

	glClearColor(1., 1., 1, 1.);	//Background colour
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45., 1., 1., 500.);  //The camera view volume  
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
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouseMotion);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0; 
}
