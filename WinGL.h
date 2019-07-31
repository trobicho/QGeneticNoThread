#pragma once
#include <QtOpenGL>
#include <QGLWidget>
#include <GL/glu.h>

class WinGL: public QGLWidget
{
    Q_OBJECT
    public:
        explicit WinGL(int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);
        void initializeGL();
        void resizeGL(int width, int height);
        virtual void paintGL()=0;
        virtual void keyPressEvent(QKeyEvent *keyEvent);

    public slots:
        virtual void timeOutSlot();

    private:
        QTimer *t_Timer;

};

