#include <QtWidgets>
#include <QtOpenGL>
#include <QGLShader>
#include "AppWindow.hpp"

#include <cstdio>
#include <cstdlib>
#include <string>

#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define MICKEY 1
#define LEFT_BUTTON 0
#define RIGHT_BUTTON 1

AppWindow::AppWindow(QWidget *parent) 
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) 
    , lpos{1, 0.5, 1, 0}
{
    a = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/30    );
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

void AppWindow::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_CULL_FACE);
    
    setShaders();
}

void AppWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0,0.0,5.0, 
              0.0,0.0,-1.0,
              0.0f,1.0f,0.0f);

    float s[] = {0.15, 0.15, 0.05, 1 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, s);
    GLfloat shininess=100.0;
    glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glRotatef(a,0,1,1);
    // glFrontFace(GL_CW);
    glutSolidTeapot(1);
    // glFrontFace(GL_CCW);
    a+=0.1;

    // glFlush();
}

void AppWindow::resizeGL(int width, int height) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(height == 0)
        height = 1;

    float ratio = 1.0* width / height;

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, width, height);

    // Set the correct perspective.
    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);


    // // Set up perspective projection, using current size and aspect
    // // ratio of display

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glViewport(0, 0, width, height);
    // gluPerspective(40.0, (GLfloat)width/(GLfloat)height, 0.1, 1000.0);

    // // Reset to modelview matrix mode

    // glMatrixMode(GL_MODELVIEW);
}

char* AppWindow::textFileRead(char *fn) {
    FILE *fp;
    char *content = NULL;

    int count=0;

    if (fn != NULL) {
        fp = fopen(fn,"rt");

        if (fp != NULL) {
      
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
}

int AppWindow::textFileWrite(char *fn, char *s) {

    FILE *fp;
    int status = 0;

    if (fn != NULL) {
        fp = fopen(fn,"w");

        if (fp != NULL) {
            
            if (fwrite(s,sizeof(char),strlen(s),fp) == strlen(s))
                status = 1;
            fclose(fp);
        }
    }
    return(status);
}

void AppWindow::setShaders() {

    vert = new QGLShader(QGLShader::Vertex);
    frag = new QGLShader(QGLShader::Fragment);
    // QGLShader* frag2 = new QGLShader(QGLShader::Fragment);

    char *vs = NULL,*fs = NULL;//,*fs2 = NULL;
    vs = textFileRead("shader.vert");
    fs = textFileRead("shader.frag");

    
    if (!vert->compileSourceCode(vs)) {
        std::cerr << vert->log().toStdString() << std::endl;
    }

    if (!frag->compileSourceCode(fs)) {
        std::cerr << vert->log().toStdString() << std::endl;
    }

    free(vs);
    free(fs);

    program = new QGLShaderProgram(this);
    program->addShader(vert);
    program->addShader(frag);
    program->link();
    program->bind();
}