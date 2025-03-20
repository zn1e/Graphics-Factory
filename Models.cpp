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


// Draw the conveyor belt
void conveyor() {
    float gray[3] = {0.5, 0.5, 0.5};
    float white[3] = {1., 1., 1.};
    float shininess[1] = {50.};
    float v[11] = {-5.,-4., -3., -2., -1., 0, 1., 2., 3., 4., 5.}; // vertices of V
    int n = 11; // max length of vertices
    float w = 1.; // width of conveyor
    float height = -0.5;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, gray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gray);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

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
