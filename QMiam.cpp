#include "QMiam.h"

QMiam::QMiam(int nbPeople): Miam(nbPeople), WinGL(100, NULL, "Miam")
{
    setFixedSize(m_map.w, m_map.h);
    //nextGen();
}

void QMiam::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(0, m_map.w, 0, m_map.h, -1, 100);
    for(int i=0; i<m_nbStablePeople; i++)
    {
        if(!m_people[i]->get_death())
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

void QMiam::paintMiam(s_miam &miam)
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

    if(m_debug)
    {
        glColor3ub(0x20, 0xF0, 0);
        double alpha=0.0;
        double dist=foodDist((s_vec2d){miam.x, miam.y}, miam.angle, miam.viewAngle, &alpha);
        alpha+=miam.angle;
        if(dist>=0)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2i(miam.x, miam.y);
            glVertex2i(miam.x+cos(alpha)*dist, miam.y+sin(alpha)*dist);
            glEnd();
        }
    }
}

void QMiam::timeOutSlot()
{
    evaluate();
    updateGL();
}

void QMiam::evaluate()
{
    static int count=0;
    if(count>=5000)
        count=0;
    if(count==0)
    {
        genFinish();
        nextGen();
    }
    Miam::evaluate();
    count++;
}
