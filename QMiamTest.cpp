#include "QMiamTest.h"

QMiamTest::QMiamTest():QMiam(1)
{
    m_map.food.resize(1);
    m_people[0]->set_pos(m_map.w/2, m_map.h/2);
    m_map.food[0].x=m_map.w/2;
    m_map.food[0].y=m_map.h/2;
    m_map.nbFood=1;
}

void QMiamTest::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(0, m_map.w, 0, m_map.h, -1, 100);
    for(int i=0; i<m_nbStablePeople; i++)
    {
        paintMiam(m_people[i]->m_miam);
    }
    glPointSize(2);
    glColor3ub(0x20, 0xF0, 0);
    glBegin(GL_POINTS);
    for(int i=0; i<m_map.nbFood; i++)
    {
        glVertex2i(m_map.food[i].x, m_map.food[i].y);
    }
    glEnd();
}

void QMiamTest::paintMiam(s_miam &miam)
{
    glPointSize(2);
    glColor3ub(0xFF, 0xFF, 0xFF);
    glBegin(GL_POINTS);
    glVertex2i(miam.x, miam.y);
    glEnd();
    
    glColor3ub(0xF0, 0x20, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2i(miam.x, miam.y);
    glVertex2i(miam.x+cos(miam.angle)*10, miam.y+sin(miam.angle)*10);
    glEnd();

    glColor3ub(0x20, 0xF0, 0);
    double alpha=0.0;
    double dist=foodDist(m_people[0]->get_pos(), m_people[0]->get_angle(), m_people[0]->get_viewAngle(), &alpha);
    alpha+=m_people[0]->get_angle();
    if(dist>=0)
    {
        glBegin(GL_LINE_STRIP);
        glVertex2i(miam.x, miam.y);
        glVertex2i(miam.x+cos(alpha)*dist, miam.y+sin(alpha)*dist);
        glEnd();
    }
}

void QMiamTest::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_Down:
            m_people[0]->move(-1);
            break;
        case Qt::Key_Up:
            m_people[0]->move(1);
            break;
        case Qt::Key_Left:
            m_people[0]->angleAdd(0.2);
            break;
        case Qt::Key_Right:
            m_people[0]->angleAdd(-0.2);
            break;
        case Qt::Key_Space:
            std::cout << foodDist(m_people[0]->get_pos(), m_people[0]->get_angle(), m_people[0]->get_viewAngle())  << " " << m_people[0]->get_angle() << std::endl;
            break;
    }
}

void QMiamTest::timeOutSlot()
{
    updateGL();
}
