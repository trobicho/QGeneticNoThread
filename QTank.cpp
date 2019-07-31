#include "QTank.h"

QTank::QTank(int nbPeople): Tank(nbPeople), WinGL(30, NULL, "Tank")
{
    setFixedSize(m_map.w, m_map.h);
    nextGen();
}

void QTank::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(0, m_map.w, 0, m_map.h, -1, 100);
    for(int i=0; i<m_nbStablePeople; i++)
    {
        if(!m_people[i]->get_death())
        paintTank(m_people[i]->m_tank);
    }
    glPointSize(2);
    glColor3ub(0x20, 0xF0, 0);
    glBegin(GL_POINTS);
    std::list<Bullet>::iterator it=m_bullet.begin();
    for(; it!=m_bullet.end(); ++it)
    {
        s_vec2d pos=it->get_pos();
        glVertex2i(pos.x, pos.y);
    }
    glEnd();
}

void QTank::paintTank(s_tank &tank)
{
    double pi=3.1415926535;
    double wT=tank.hitbox.x, hT=tank.hitbox.y;
    glColor3ub(0x11, 0x66, 0x00);
    glBegin(GL_QUADS);
    glVertex2i(tank.x+cos(tank.angle)*hT/2.0+cos(tank.angle+pi/2)*wT/2.0, tank.y+sin(tank.angle)*hT/2.0+sin(tank.angle+pi/2)*wT/2.0);
    glVertex2i(tank.x+cos(tank.angle)*hT/2.0+cos(tank.angle-pi/2)*wT/2.0, tank.y+sin(tank.angle)*hT/2.0+sin(tank.angle-pi/2)*wT/2.0);

    glVertex2i(tank.x-cos(tank.angle)*hT/2.0+cos(tank.angle-pi/2)*wT/2.0, tank.y-sin(tank.angle)*hT/2.0+sin(tank.angle-pi/2)*wT/2.0);
    glVertex2i(tank.x-cos(tank.angle)*hT/2.0+cos(tank.angle+pi/2)*wT/2.0, tank.y-sin(tank.angle)*hT/2.0+sin(tank.angle+pi/2)*wT/2.0);
    glEnd();
    
    glColor3ub(0xF0, 0x20, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2i(tank.x, tank.y);
    glVertex2i(tank.x+cos(tank.angle)*10, tank.y+sin(tank.angle)*10);
    glEnd();

    wT=3;
    hT=22;
    glColor3ub(0xF0, 0xF0, 0);
    glBegin(GL_QUADS);
    glVertex2i(tank.x+cos(tank.gunAngle)*hT/2.0+cos(tank.gunAngle+pi/2)*wT/2.0, tank.y+sin(tank.gunAngle)*hT/2.0+sin(tank.gunAngle+pi/2)*wT/2.0);
    glVertex2i(tank.x+cos(tank.gunAngle)*hT/2.0+cos(tank.gunAngle-pi/2)*wT/2.0, tank.y+sin(tank.gunAngle)*hT/2.0+sin(tank.gunAngle-pi/2)*wT/2.0);
    glVertex2i(tank.x+cos(tank.gunAngle-pi/2)*wT/2.0, tank.y+sin(tank.gunAngle-pi/2)*wT/2.0);
    glVertex2i(tank.x+cos(tank.gunAngle+pi/2)*wT/2.0, tank.y+sin(tank.gunAngle+pi/2)*wT/2.0);
    glEnd();

    if(m_debug)
    {
        glColor3ub(0, 0x20, 0xF0);
        double alpha=0.0;
        double dist=tankDist((s_vec2d){tank.x, tank.y}, tank.gunAngle, tank.viewAngle, &alpha);
        alpha+=tank.gunAngle;
        if(dist>=0)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2i(tank.x, tank.y);
            glVertex2i(tank.x+cos(alpha)*dist, tank.y+sin(alpha)*dist);
            glEnd();
        }
    }
}

void QTank::timeOutSlot()
{
    for(int i=0; i<m_nbEvalPerFrame; i++)
        evaluate();
    updateGL();
}

void QTank::evaluate()
{
    static int count=1;
    if(count>=5000)
        count=0;
    if(count==0)
    {
        genFinish();
        nextGen();
    }
    Tank::evaluate();
    count++;
    if(m_bNewGen)
        count=1;
}

void QTank::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;

        case Qt::Key_Plus:
            if(m_nbEvalPerFrame<100)
                m_nbEvalPerFrame++;
            break;

        case Qt::Key_Minus:
            if(m_nbEvalPerFrame>1)
                m_nbEvalPerFrame--;
            break;
    }
}
