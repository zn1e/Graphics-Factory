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
using namespace std;

float donutPos = -5.;
float speed = 0.0005;
float white[3] = {1., 1., 1.};

// Draw the conveyor belt
void conveyor() {

    float v[11] = {-5.,-4., -3., -2., -1., 0, 1., 2., 3., 4., 5.}; // vertices of V
    int n = 11; // max length of vertices
    float w = 1.; // width of conveyor
    float height = -0.5;

    glEnable(GL_NORMALIZE);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < n; i++) 
    {
        glNormal3f(0, 1, 0); // normal pointing upward
        glVertex3f(v[i], height, 0);
        glVertex3f(v[i], height, w);
    }

    glEnd();
}

// Draw the pillars
void pillars() {

    // front-left pillar
    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(-5., 3., 0.5);
        glScalef(0.5, 10., 1.4);
        glutSolidCube(1.);
    glPopMatrix();

    // front-right pillar
    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(5., 3., 0.5);
        glScalef(0.5, 10., 1.4);
        glutSolidCube(1.);
    glPopMatrix();

    // back-left pillar
    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(-5, 3., -20.);
        glScalef(0.5, 10., 1.4);
        glutSolidCube(1.);
    glPopMatrix();


    // back-right pillar
    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(5., 3., -20.);
        glScalef(0.5, 10., 1.4);
        glutSolidCube(1.);
    glPopMatrix();

}

// Draw the cylinder between pillars
void cylinder() {
    GLUquadric *q;
    q = gluNewQuadric();

    glPushMatrix();
        gluQuadricDrawStyle(q, GLU_FILL);
        glTranslatef(-5., 6.5, 0.);
        glRotatef(90., 0., 1., 0.);
        gluCylinder(q, 0.5, 0.5, 10., 10, 10.);
    glPopMatrix();
    
}


void getDonut() {

    glPushMatrix();
        glColor3f(0.55, 0.35, 0.07);
        glTranslatef(donutPos, -0.4, 0.5);
        glRotatef(90, 0, 0, 1);
        glRotatef(90, 0, 1, 0);
        //glScalef(1., 1., 1.);
        glutSolidTorus(.1, .3, 20, 20);
    glPopMatrix();

}

// Animate objects
void animate() {
    donutPos += speed;
    if (donutPos >= 5.0f) donutPos = -5.0f;
}
