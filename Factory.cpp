// ---------------------------------------------------------
// COSC363: Computer Graphics (2025)
// Assignment 1: Graphics Factory
//
// <Description of the scene>
//
//
// ---------------------------------------------------------

#include <iostream>
#include <fstream>
#include <climits>
#include <GL/freeglut.h>
using namespace std;


// Global variables
float *x, *y, *z;	// vertex coordinate arrays
int *t1, *t2, *t3;	// triangles
int nvert, ntri;	// total number of vertices and triangles
float cam_hgt = 1; 

// Loads mesh data in OFF format   
void loadMeshFile(const char* fname) {
	ifstream fp_in;
	int num, nedge;

	fp_in.open(fname, ios::in);
	if(!fp_in.is_open()) {
		cout << "Error opening mesh file" << endl;
		exit(1);
	}

	fp_in.ignore(INT_MAX, '\n');		// ignore first line
	fp_in >> nvert >> ntri >> nedge;	// read number of vertices, polygons, edges

	x = new float[nvert];				// create arrays
	y = new float[nvert];
	z = new float[nvert];

	t1 = new int[ntri];
	t2 = new int[ntri];
	t3 = new int[ntri];

	for(int i = 0; i < nvert; i++) {	// read vertex list 
		fp_in >> x[i] >> y[i] >> z[i];
	}

	for(int i = 0; i < ntri; i++) {	// read polygon list 
		fp_in >> num >> t1[i] >> t2[i] >> t3[i];
		if(num != 3) {
			cout << "ERROR: Polygon with index " << i  << " is not a triangle." << endl; // not a triangle!!
			exit(1);
		}
	}

	fp_in.close();
	cout << " File successfully read." << endl;
}

// Draws a grid of lines on the floor plane 
void drawFloor() {
	glColor3f(0., 0.5, 0.);			//Floor colour
	for (float i = -50.; i <= 50.; i++) {
		glBegin(GL_LINES);			//A set of grid lines on the xz-plane
			glVertex3f(-50., 0., i);
			glVertex3f( 50., 0., i);
			glVertex3f(i, 0., -50.);
			glVertex3f(i, 0.,  50.);
		glEnd();
	}
}

// Display:
// This is the main display module containing function calls for generating
// the scene.
void display() {
	float lpos[4] = {100., 100., 100., 1.};	//light's position

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//GL_LINE = Wireframe;   GL_FILL = Solid
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 10, 0., 0., 0., 0., 0., 1., 0.);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);	//set light position

	drawFloor();

	glFlush();
}
// Initialize OpenGL parameters 
void initialize() {
	// loadMeshFile("Cannon.off");		//Specify mesh file name here
	glClearColor(1., 1., 1., 1.);	//Background colour

	glEnable(GL_LIGHTING);			//Enable OpenGL states
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60., 1., 50., 1000.);  //The camera view volume  
}

//-- Main: Initialize glut window and register call backs ------------------
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Graphics Factory");
	initialize();

	glutDisplayFunc(display);
	// glutSpecialFunc(special);
	glutMainLoop();
	return 0; 
}
