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
    // Nothing to do here right now.
}

QSize Viewer::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize Viewer::sizeHint() const {
    return QSize(300, 300);
}

void Viewer::initializeGL() {
    glShadeModel(GL_SMOOTH);
    glClearColor( 0.4, 0.4, 0.4, 0.0 );
    glEnable(GL_DEPTH_TEST);
}

void Viewer::paintGL() {

    // Set up for perspective drawing 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width(), height());
    gluPerspective(40.0, (GLfloat)width()/(GLfloat)height(), 0.1, 1000.0);

    // change to model view for drawing
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Clear framebuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up lighting

    // Draw stuff

    draw_trackball_circle();

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

void Viewer::draw_trackball_circle()
{
    int current_width = width();
    int current_height = height();

    // Set up for orthogonal drawing to draw a circle on screen.
    // You'll want to make the rest of the function conditional on
    // whether or not we want to draw the circle this time around.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, current_width, current_height);
    glOrtho(0.0, (float)current_width, 
           0.0, (float)current_height, -0.1, 0.1);

    // change to model view for drawing
    glMatrixMode(GL_MODELVIEW);

    // Reset modelview matrix
    glLoadIdentity();

    // draw a circle for use with the trackball 
    glDisable(GL_LIGHTING);
    glEnable(GL_LINE_SMOOTH);
    glColor3f(1.0, 1.0, 1.0);
    double radius = current_width < current_height ? 
    (float)current_width * 0.25 : (float)current_height * 0.25;
    glTranslated((float)current_width * 0.5, (float)current_height * 0.5, 0);
    glBegin(GL_LINE_LOOP);
    for(size_t i=0; i<40; ++i) {
    double cosine = radius * cos(i*2*M_PI/40);
    double sine = radius * sin(i*2*M_PI/40);
    glVertex2f(cosine, sine);
    }
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glDisable(GL_LINE_SMOOTH);
}
