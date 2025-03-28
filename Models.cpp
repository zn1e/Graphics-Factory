// ---------------------------------------------------------
// COSC363: Computer Graphics (2025)
// Assignment 1: Graphics Factory
//
// Models.cpp
// Collection of functions for generating models for factory
//
// ---------------------------------------------------------

#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include "loadBMP.h"
using namespace std;

float boxPos = -5.;
float fanAngle = 0.;
float conveyorOffset = 0.;
float speed = 0.0005;
float white[3] = {1., 1., 1.};

GLuint txId[3];

// Load textures
void loadTexture() {
    glEnable(GL_TEXTURE_2D);
	glGenTextures(3, txId);   //Get 2 texture IDs 

	glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture name for the following OpenGL texture
	loadBMP("pillar.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture name for the following OpenGL texture
	loadBMP("background.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture name for the following OpenGL texture
	loadBMP("conveyor.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// Draw the conveyor belt
void conveyor() {

    float v[11] = {-5.,-4., -3., -2., -1., 0, 1., 2., 3., 4., 5.}; // vertices of V
    int n = 11; // max length of vertices
    float w = 1.; // width of conveyor
    float height = -0.5;

    glBindTexture(GL_TEXTURE_2D, txId[2]); 
    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i < n; i++) 
    {
        glNormal3f(0, 1, 0); // normal pointing upward

        glTexCoord2f((float)i / (n - 1), 0); 
        glVertex3f(v[i], height, 0);
    
        glTexCoord2f((float)i / (n - 1), 1); 
        glVertex3f(v[i], height, w);
    }

    glEnd();
}

// Draw the pillars
void pillars() {


    // front-left pillar
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    glPushMatrix();
        glTranslatef(-5., 3., 0.5);
        glScalef(0.5, 10., 1.4);
        glutSolidCube(1.);
    glPopMatrix();

    // front-right pillar
    glBindTexture(GL_TEXTURE_2D, txId[0]);
    glPushMatrix();
        glTranslatef(5., 3., 0.5);
        glScalef(0.5, 10., 1.4);
        glutSolidCube(1.);
    glPopMatrix();

}

// Draw the cylinder between pillars
void cylinder() {
    GLUquadric *q;
    q = gluNewQuadric();
    
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        gluQuadricDrawStyle(q, GLU_FILL);
        glTranslatef(-5., 6.5, 0.5);
        glRotatef(90., 0., 1., 0.);
        gluCylinder(q, 0.5, 0.5, 10., 10, 10.);
    glPopMatrix(); 

    // draw the cylinder for hanging fan
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        gluQuadricDrawStyle(q, GLU_FILL);
        glTranslatef(0., 4.5, 0.5);
        glRotatef(90, 0., 0., 1.);
        glRotatef(90., 0., 1., 0.);
        gluCylinder(q, 0.1, 0.1, 2., 10, 10.);
    glPopMatrix(); 

    gluDeleteQuadric(q);
}

// Draw fan blades
void drawBlade() {
    glBegin(GL_QUADS);
        glVertex2f(-0.05, 0.1);
        glVertex2f(0.05, 0.1);
        glVertex2f(0.15, 0.6);
        glVertex2f(-0.15, 0.6);
    glEnd();
}

// Draw the fan
void drawFan() {
    glPushMatrix();
        glColor3f(1., 0., 0.);
        for (int i = 0; i < 3; i++) {
            glPushMatrix();
                glRotatef(90, 1., 0., 0.); // rotate around x axis so it is positioned correctly
                glRotatef(i * 120, 0., 0., 1.); // even out the spacing between blades
                drawBlade();
            glPopMatrix();
        }
    glPopMatrix();
}


// Get the box in conveyor
void getBox() {

    glPushMatrix();
        glColor3f(0.55, 0.35, 0.07);
        glTranslatef(boxPos, 0., 0.5);
        glScalef(0.5, 1., 0.5);
        glutSolidCube(1.);
    glPopMatrix();

}

// Rotate the fan in a pivot
void spinFan() {

    glPushMatrix();
        glTranslatef(0., 4.5, 0.5);

        glPushMatrix();
            glRotatef(fanAngle, 0., 1., 0.);
            drawFan();
        glPopMatrix();

    glPopMatrix();

}

void drawSkySphere(float radius) {

    GLUquadric *q = gluNewQuadric();
    gluQuadricTexture(q, GL_TRUE);

    glBindTexture(GL_TEXTURE_2D, txId[1]); // Bind sky texture

    glPushMatrix();
        glRotatef(90., 0., 1., 0);
        glRotatef(-90, 1.0, 0.0, 0.0); // Rotate the sphere so that poles align with top and bottom
        gluSphere(q, 50.0, 36, 18); // Create sphere with a reasonable resolution
    glPopMatrix();

    gluDeleteQuadric(q);

}

// Draw boxes with planar shadows
void boxWithShadow() {
    float light[4] = {5., 10., 5., 1};
    float shadowMat[16] = {light[1], 0, 0, 0, 
                        -light[0], 0, -light[2], -1, 
                        0, 0, light[1], 0, 
                        0, 0, 0, light[1]};
    glLightfv(GL_LIGHT0, GL_POSITION, light);

    glEnable(GL_LIGHTING);

    // floating box
    glPushMatrix();
        glColor3f(0.55, 0.35, 0.07);
        glTranslatef(5, 0.5, 8);
        glScalef(0.5, 1., 0.5);
        glutSolidCube(1.);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.55, 0.35, 0.07);
        glTranslatef(5, -1, 10);
        glScalef(0.5, 1., 0.5);
        glutSolidCube(1.);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glColor3f(0.2, 0.2, 0.2); // shadow

    glPushMatrix();
        glTranslatef(5, -2, 8);
        glMultMatrixf(shadowMat);
        glScalef(0.5, 1., 0.5);
        glutSolidCube(1.);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(5, -2, 10);
        glMultMatrixf(shadowMat);
        glScalef(0.5, 1., 0.5);
        glutSolidCube(1.);
    glPopMatrix();

}

// Animate objects
void animate() {
    boxPos += speed;
    fanAngle += 1.;
    

    if (boxPos >= 5.0f) boxPos = -5.0f;

    if (fanAngle > 360) fanAngle -= 360;

}

// Draw a surface generated tank
void drawTank() {
    int SLICES = 50;  //slices of tank
    float RADIUS = 2.0;
    float HEIGHT = 8.0;

    float angleStep = 2 * M_PI / SLICES; // angle between each vertex

    glColor3f(1, 1, 0.);
    glPushMatrix();
        glTranslatef(12., -2., -20.);
        glRotatef(-90., 1, 0., 0.); // make it stand
        
        // draw the side surface
        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i < SLICES; i++) {
            float theta = i * angleStep;
            float x = RADIUS * cos(theta);
            float y = RADIUS * sin(theta);

            glNormal3f(cos(theta), sin(theta), 0);

            glVertex3f(x, y, 0); // bottom vertex

            glVertex3f(x, y, HEIGHT); // top vertex
        }
        glEnd();

        // draw the top cap/circle using triangle fan
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0, HEIGHT); // central top vertex
        for (int i = 0; i < SLICES; i++) {
            float theta = i * angleStep;
            float x = RADIUS * cos(theta);
            float y = RADIUS * sin(theta);
            glVertex3f(x, y, HEIGHT);
        }
        glEnd();

        // draw the bottom cap
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0, 0); // central bottom vertex
        for (int i = 0; i < SLICES; i++) {
            float theta = i * angleStep;
            float x = RADIUS * cos(theta);
            float y = RADIUS * sin(theta);
            glVertex3f(x, y, 0);
        }
        glEnd();

    glPopMatrix();

}