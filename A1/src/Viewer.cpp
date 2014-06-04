#include <QtWidgets>
#include <QtOpenGL>
#include "Viewer.hpp"
#include <iostream>
#include <math.h>
#include <GL/glu.h>


#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

Viewer::Viewer(QWidget *parent) 
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) 
{

}

Viewer::~Viewer() {

}

QSize Viewer::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize Viewer::sizeHint() const {
    return QSize(300, 600);
}

void Viewer::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7, 0.7, 1.0, 0.0);
}

void Viewer::paintGL() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Modify the current projection matrix so that we move the 
    // camera away from the origin.  We'll draw the game at the
    // origin, and we need to back up to see it.

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glTranslated(0.0, 0.0, -40.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Not implemented: set up lighting (if necessary)

    // Not implemented: scale and rotate the scene

    // You'll be drawing unit cubes, so the game will have width
    // 10 and height 24 (game = 20, stripe = 4).  Let's translate
    // the game so that we can draw it starting at (0,0) but have
    // it appear centered in the window.
    glTranslated(-5.0, -12.0, 0.0);

    // Not implemented: actually draw the current game state.
    // Here's some test code that draws red triangles at the
    // corners of the game board.
    glColor3d(1.0, 0.0, 0.0);

    glBegin(GL_TRIANGLES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);

    glVertex3d(9.0, 0.0, 0.0);
    glVertex3d(10.0, 0.0, 0.0);
    glVertex3d(10.0, 1.0, 0.0);

    glVertex3d(0.0, 19.0, 0.0);
    glVertex3d(1.0, 20.0, 0.0);
    glVertex3d(0.0, 20.0, 0.0);

    glVertex3d(10.0, 19.0, 0.0);
    glVertex3d(10.0, 20.0, 0.0);
    glVertex3d(9.0, 20.0, 0.0);
    glEnd();

    // We pushed a matrix onto the PROJECTION stack earlier, we 
    // need to pop it.

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

}

void Viewer::resizeGL(int width, int height) {
    // Set up perspective projection, using current size and aspect
    // ratio of display

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(40.0, (GLfloat)width/(GLfloat)height, 0.1, 1000.0);

    // Reset to modelview matrix mode

    glMatrixMode(GL_MODELVIEW);
}

void Viewer::mousePressEvent ( QMouseEvent * event ) {
    std::cerr << "Stub: button " << event->button() << " pressed\n";
}

void Viewer::mouseReleaseEvent ( QMouseEvent * event ) {
    std::cerr << "Stub: button " << event->button() << " released\n";
}

void Viewer::mouseMoveEvent ( QMouseEvent * event ) {
    std::cerr << "Stub: Motion at " << event->x() << ", " << event->y() << std::endl;
}