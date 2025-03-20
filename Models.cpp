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

float conveyorSpeed = 0.001f;
float conveyorOffset = 0.0f;

// Draw the pillars
/*
void pillar() {
    glColor4f(0.5, 0.7, 0.8, 1.0); 

    glPushMatrix();
        glTranslatef(-10., 4., 0.);
        glScalef(2.5, 10., 2.5);
        glutSolidCube(1.);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(10., 4., 0.);
        glScalef(2.5, 10., 2.5);
        glutSolidCube(1.);
    glPopMatrix();
}
*/

// Draw the conveyor belt
void conveyor() {
    // float v[10] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9.}; // vertices of V
    int n = 10; // max length of vertices
    float w = 1.5; // width of conveyor
    float height = -0.5;

    glEnable(GL_NORMALIZE);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < n; i++) 
    {
        float x = fmod(i + conveyorOffset, n); // moving effect
        glNormal3f(0, 1, 0); // normal pointing upward
        glVertex3f(x, height, 0);
        glVertex3f(x, height, w);
    }
    glEnd();
}

void update() {
    conveyorOffset += conveyorSpeed;
    if (conveyorOffset >= 10.0f) {
        conveyorOffset = 0.0f;
    }
}