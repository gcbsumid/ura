#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <cmath>
#include "Viewer.hpp"
#include "draw.hpp"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

using namespace std;

Viewer::Viewer(QWidget *parent) 
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    // Nothing to do here right now.
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

void Viewer::set_perspective(double fov, double aspect,
                             double near, double far)
{
    // Fill me in!
}

void Viewer::reset_view()
{
    // Fill me in!
}

void Viewer::initializeGL() {
    // Do some OpenGL setup
    glEnable(GL_DEPTH_TEST);
    glClearColor(.7, 0.7, 0.7, 0.0);
}

void Viewer::paintGL() {
    // Here is where your drawing code should go.
    draw_init(width(), height());
  
    /* A few of lines are drawn below to show how it's done. */
    set_colour(Colour(0.1, 0.1, 0.1));

    draw_line(Point2D(0.1*width(), 0.1*height()), 
              Point2D(0.9*width(), 0.9*height()));
    draw_line(Point2D(0.9*width(), 0.1*height()),
              Point2D(0.1*width(), 0.9*height()));

    draw_line(Point2D(0.1*width(), 0.1*height()),
              Point2D(0.2*width(), 0.1*height()));
    draw_line(Point2D(0.1*width(), 0.1*height()), 
              Point2D(0.1*width(), 0.2*height()));

    draw_complete();
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

