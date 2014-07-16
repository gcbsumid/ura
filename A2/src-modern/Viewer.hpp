#ifndef CS488_VIEWER_HPP
#define CS488_VIEWER_HPP

#include <QGLWidget>
#include "algebra.hpp"

class Viewer : public QGLWidget {
    
    Q_OBJECT

public:
    Viewer(QWidget *parent = 0);
    virtual ~Viewer();
    
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    // If you want to render a new frame, call do not call paintGL(),
    // instead, call update() to ensure that the view gets a paint 
    // event.

    // *** Fill in these functions (in viewer.cpp) ***

    // Set the parameters of the current perspective projection using
    // the semantics of gluPerspective().
    void set_perspective(double fov, double aspect,
                         double near, double far);

    // Restore all the transforms and perspective parameters to their
    // original state. Set the viewport to its initial size.
    void reset_view();

protected:

    // Events we implement

    // Called when GL is first initialized
    virtual void initializeGL();
    // Called when our window needs to be redrawn
    virtual void paintGL();
    // Called when a mouse button is pressed
    virtual void mousePressEvent ( QMouseEvent * event );
    // Called when a mouse button is released
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    // Called when the mouse moves
    virtual void mouseMoveEvent ( QMouseEvent * event );

private:

#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    QOpenGLBuffer mVertexBufferObject;
    QOpenGLVertexArrayObject mVertexArrayObject;
#else 
    QGLBuffer mVertexBufferObject;
#endif

    int mVertexLocation;
    int mMvpMatrixLocation;
    QGLShaderProgram mProgram;
    
    // *** Fill me in ***
    // You will want to declare some more matrices here
    Matrix4x4 m_projection;    
};

#endif