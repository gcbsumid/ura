#include <QApplication>
#include <QDesktopWidget>
// #include "appwindow.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // AppWindow window;
    // window.resize(window.sizeHint());
    // int desktopArea = QApplication::desktop()->width() * 
    //                   QApplication::desktop()->height();

    // int widgetArea = window.width() * window.height();

    // if (((float)widgetArea / (float) desktop) < 0.75f) {
    //     window.show();
    // } else {
    //     window.showMaximized();
    // }

    return app.exec();






  // // Construct our main loop
  // Gtk::Main kit(argc, argv);

  // // Initialize OpenGL
  // Gtk::GL::init(argc, argv);

  // // Construct our (only) window
  // AppWindow window;

  // // And run the application!
  // Gtk::Main::run(window);
}

