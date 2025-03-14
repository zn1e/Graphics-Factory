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
using namespace std;

// Draw the pillars
void pillar() {
    glColor4f(0.5, 0.7, 0.8, 1.0); 

    glPushMatrix();
        glTranslatef(0., 4., -10.);
        glScalef(1., 10., 1.);
        glutSolidCube(1.);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0., 4., 10.);
        glScalef(1., 10., 1.);
        glutSolidCube(1.);
    glPopMatrix();
}
