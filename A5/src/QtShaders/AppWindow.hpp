#ifndef CS488_APPWINDOW
#define CS488_APPWINDOW 

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QGLShader>

class AppWindow : public QGLWidget {

    Q_OBJECT

public:
    AppWindow(QWidget *parent = 0);
    virtual ~AppWindow();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:

    // Called when GL is first initialized
    virtual void initializeGL();
    // Called when our window needs to be redrawn
    virtual void paintGL();
    // Called when the window is resized (formerly on_configure_event)
    virtual void resizeGL(int width, int height);

private:
    char* textFileRead(char *fn);
    int textFileWrite(char *fn, char *s);
    void setShaders();

    QTimer* timer;
    QGLShaderProgram* program;
    QGLShader* vert;
    QGLShader* frag;
    float lpos[4];
    float a;
};

#endif