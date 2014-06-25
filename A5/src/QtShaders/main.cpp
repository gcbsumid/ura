/* ***************************************************************
 *
 * File :  main.cpp
 *
 * Author : Christian Sumido
 * Date   : June 21st, 2014
 *
 * Modified:
 *
 * Purpose: Simple OpenGL program to illustrate the use of Modern OpenGL with Qt
 *
 * ****************************************************************/
#include <QApplication>
#include <QDesktopWidget>
#include <GL/glut.h>
#include "AppWindow.hpp"

//-------------------------------------------------------------------
// main 
//-------------------------------------------------------------------
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    QApplication app(argc, argv);

    AppWindow window;
    window.resize(window.sizeHint());

    int desktopArea = QApplication::desktop()->width() * 
                      QApplication::desktop()->height();

    int widgetArea = window.width() * window.height();

    if (((float)widgetArea / (float) desktopArea) < 0.75f) {
        window.show();
    } else {
        window.showMaximized();
    }

    return app.exec();
}

