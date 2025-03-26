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
    //float gray[3] = {0.5, 0.5, 0.5};
    //float shininess[1] = {50.};
    
    float v[11] = {-5.,-4., -3., -2., -1., 0, 1., 2., 3., 4., 5.}; // vertices of V
    int n = 11; // max length of vertices
    float w = 1.; // width of conveyor
    float height = -0.5;

    //glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gray);
   // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

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

void getDonut() {

    //float brown[3] = {0.55, 0.35, 0.07};
    //float shininess[1] = {80.};
    //float light[] = {0., 50., 0., 1.};

    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, brown);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glPushMatrix();
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
