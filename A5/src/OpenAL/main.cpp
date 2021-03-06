/* ***************************************************************
 *
 * File :  main.cpp
 *
 * Author : Tiberiu Popa
 *  	    J. Alexander Clarke
 * Date   : June 18th, 2002
 *
 * Modified:
 *
 * Purpose: Simple OpenGL program to illustrate the use of GLui with OpenGL and SDL for sound only
 *
 * ****************************************************************/
#include <QApplication>
#include <QDesktopWidget>
#include "AppWindow.hpp"

//-------------------------------------------------------------------
// main 
//-------------------------------------------------------------------
int main(int argc, char** argv){
    
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

