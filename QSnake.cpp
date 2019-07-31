#include "QSnake.h"
#include <iostream>

QSnake::QSnake(QWidget *parent, s_vec2i max, int pixSize): Snake8_new(max), QFitness(50, parent, "teste"),\
m_pixSize(pixSize)
{
    m_max=max;
    setFixedSize(m_max.x*m_pixSize, m_max.y*m_pixSize);
}

void QSnake::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(0, m_max.x, 0, m_max.y, -1, 100);
    paintSnake();
}


int QSnake::evaluate(double *gene, int generation)
{
    if(m_activFoodGen>=0 && generation>=m_activFoodGen)
        set_food(true);
    evaluate(gene);
}

int QSnake::evaluate(double *gene)
{
    int finalScore=0;
    if(m_bFood)
    {
        fillNet(gene);
        randApple();
        snake_init();
        while(!m_dead)
        m_score+=m_moveNoEat/m_applePoint;
        return m_score
    }
    else
    {
        snake_init();
        fillNet(gene);
        return m_score;
    }
}

void QSnake::paintSnake()
{
    int dir=m_snake.dir, r=0;
    s_vec2i v=m_snake.head;
    glPointSize(m_pixSize);
    if(m_dead)
        glColor3ub(0x8F, 0, 0);
    else
        glColor3ub(0xFF, 0xFF, 0xFF);
    glBegin(GL_POINTS);
    for(int i=0; i<m_snake.vLen; ++i)
    {
        glVertex2i(m_snake.body[i].x, m_snake.body[i].y);
    }
    if(m_bFood)
    {
        glColor3ub(0xF0, 0x20, 0);
        glVertex2i(m_apple.x, m_apple.y);
    }
    glEnd();
}

void QSnake::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_Right:
            change_dir(3);
            break;
        case Qt::Key_Left:
            change_dir(1);
            break;
        case Qt::Key_Space:
            if(m_dead)
                snake_init();
            else
                m_dead=true;
            break;
    }
}

void QSnake::timeOutSlot()
{
    updateGL();
}
