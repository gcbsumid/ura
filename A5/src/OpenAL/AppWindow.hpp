#ifndef CS488_APPWINDOW
#define CS488_APPWINDOW 

#include <QGLWidget>

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
    // Called when a mouse button is pressed
    virtual void mousePressEvent ( QMouseEvent * event );
    // Called when a mouse button is released
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    // Called when the mouse moves
    virtual void mouseMoveEvent ( QMouseEvent * event );
    // Called when there is a keypress event
    virtual void keyPressEvent ( QKeyEvent* event );

private:
    void lights();
    void makeMickey();
    void render();

    float cur_x, cur_y;
    float xpos, ypos, zpos;
    bool buttonsPressed[2];

    int EAR_SRC1, HEAD_SRC, EAR_SRC2;
    int BUF_1, BUF_2, BUF_3;
    bool loop;
};

#endif