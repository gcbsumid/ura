#include <QtWidgets>
#include <QtOpenGL>
#include "AppWindow.hpp"
#include "SoundManager.h"
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define MICKEY 1
#define LEFT_BUTTON 0
#define RIGHT_BUTTON 1

AppWindow::AppWindow(QWidget *parent) 
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) 
{
    cur_x = -1;
    cur_y = 0;
    xpos = 0;
    ypos = -0.4;
    zpos = -4.0;
    loop = false;

    BUF_1 = SM.LoadWav("moo.wav");
    BUF_2 = SM.LoadWav("OBS.wav");
    BUF_3 = SM.LoadWav("booyah.wav");

    EAR_SRC1 = SM.MakeSource();
    HEAD_SRC = SM.MakeSource();
    EAR_SRC2 = SM.MakeSource();

    SM.QueueBuffer(EAR_SRC1, BUF_1);
    SM.QueueBuffer(HEAD_SRC, BUF_2);
    SM.QueueBuffer(EAR_SRC2, BUF_3);
}

AppWindow::~AppWindow() {
    // Nothing to do here right now.
}

QSize AppWindow::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize AppWindow::sizeHint() const {
    return QSize(700, 700);
}

//-------------------------------------
// fix lights
//-------------------------------------

void AppWindow::lights(){
    GLfloat light_position1[] = {5.0, 5.0, 0, 1};
    GLfloat light1[] = {0.5, 0.5, 0.5, 1};
    GLfloat light2[] = {0.5, 0.5, .5, 1.0};

    // setup 
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 25);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light2);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light2);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
}

//--------------------------------------------------------------------
//  State variables
//--------------------------------------------------------------------

void AppWindow::makeMickey()
{
    GLUquadricObj* qsphere = gluNewQuadric();
    glNewList(MICKEY, GL_COMPILE);

    gluQuadricDrawStyle(qsphere, GLU_FILL);
    gluQuadricNormals(qsphere, GLU_SMOOTH);
    gluQuadricOrientation(qsphere, GLU_OUTSIDE);
    gluQuadricTexture(qsphere, GL_FALSE);

    glColor3f(1,1,0);
    gluSphere(qsphere, 1.3, 32, 32);
    glTranslatef(1.4,1.4,0);
    gluSphere(qsphere, 1.0, 32, 32);
    glTranslatef(-2.8,0,0);
    gluSphere(qsphere, 1.0, 32, 32);
    glEndList();
    gluDeleteQuadric(qsphere);

    SM.SetPosition(EAR_SRC1, -2.4, 1.4, 0);
    SM.SetPosition(HEAD_SRC, 0, 0, 0);
    SM.SetPosition(EAR_SRC2, 2.4, 1.4, 0);
}

void AppWindow::initializeGL() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);

    // Black Background
    glClearColor(0.00f, 0.80f, 0.80f, 0.0f); 
    glEnable(GL_DEPTH_TEST); 

    lights();
    makeMickey();
}

void AppWindow::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glLoadIdentity(); // Reset the view
    
    // move the scene 
    glTranslatef(xpos, ypos, zpos);
    SM.SetListenerPosition(-xpos, -ypos, -zpos);

    // draw s simple sphere
    glCallList(MICKEY);
}

void AppWindow::paintGL() {
    /* set up for perspective drawing 
     */
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width(), height());
    gluPerspective(40.0, (GLfloat)width()/(GLfloat)height(), 0.1, 1000.0);
    
    /* change to model view for drawing
     */
    glMatrixMode(GL_MODELVIEW);

    /* Reset modelview matrix
     */
    glLoadIdentity();

    /* Clear framebuffer (both colour and depth buffers)
     */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Set up light sources
     */

    // set up the track ball
    
    // enable rescalling of the normals
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    render();

    // dump the whole buffer onto the screen should fix my bug
    glFinish();
}

void AppWindow::resizeGL(int width, int height) {
    // Set up perspective projection, using current size and aspect
    // ratio of display

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(40.0, (GLfloat)width/(GLfloat)height, 0.1, 1000.0);

    // Reset to modelview matrix mode

    glMatrixMode(GL_MODELVIEW);
}

void AppWindow::mousePressEvent ( QMouseEvent * event ) {
    if (event->button() == Qt::LeftButton) {
        buttonsPressed[LEFT_BUTTON] = true;
    } else if (event->button() == Qt::RightButton) {
        buttonsPressed[RIGHT_BUTTON] = true;
    }
    cur_x = event->x();
    cur_y = event->y();
    update();
}

void AppWindow::mouseReleaseEvent ( QMouseEvent * event ) {
    if (event->button() == Qt::LeftButton) {
        buttonsPressed[LEFT_BUTTON] = false;
    } else if (event->button() == Qt::RightButton) {
        buttonsPressed[RIGHT_BUTTON] = false;
    }
    cur_x = event->x();
    cur_y = event->y();
    update();
}

void AppWindow::mouseMoveEvent ( QMouseEvent * event ) {
    // Todo

    if(buttonsPressed[LEFT_BUTTON]) {
        xpos  += (float)(event->x() - cur_x)/50.0f;
        ypos  += -(float)( event->y()-cur_y)/50.0f;
    } 
    if(buttonsPressed[RIGHT_BUTTON]) {
        zpos  += (float)(event->y() - cur_y)/50.0f;
    }

    cur_x = event->x();
    cur_y = event->y();
    update();
}

void AppWindow::keyPressEvent(QKeyEvent* event) {
    switch(event->key())
    {
    case Qt::Key_A:
        if (event->modifiers() & Qt::ShiftModifier) {
            std::cout << "Stopping left ear" << std::endl;
            SM.Stop(EAR_SRC1); 
        } else {
            std::cout << "Playing left ear" << std::endl;
            SM.Play(EAR_SRC1); 
        }
        break;
    case Qt::Key_S:
        if (event->modifiers() & Qt::ShiftModifier) {
            std::cout << "Pausing head" << std::endl;
            SM.Pause(HEAD_SRC); 
        } else {
            std::cout << "Playing head" << std::endl;
            SM.Play(HEAD_SRC); 
        }
        break;
    case Qt::Key_D:
        if (event->modifiers() & Qt::ShiftModifier) {
            std::cout << "Rewinding right ear" << std::endl;
            SM.Rewind(EAR_SRC2); 
        } else {
            std::cout << "Playing right ear" << std::endl;
            SM.Play(EAR_SRC2); 
        }
        break;
    case Qt::Key_L:
        std::cout << "Changed to " << (loop ? " looping." : " non-looping") << std::endl;
        loop = !loop;
        SM.SetLoop(EAR_SRC1, loop);
        SM.SetLoop(HEAD_SRC, loop);
        SM.SetLoop(EAR_SRC2, loop);
        break;
    }   
}