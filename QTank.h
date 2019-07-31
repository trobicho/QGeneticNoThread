#pragma once
#include "WinGL.h"
#include "../genetic/PoolFunc/Tank.h"

class QTank: public Tank, public WinGL
{
    public:
        QTank():QTank(30){};
        QTank(int nbPeople);
        ~QTank(){};
        void paintGL();
        void evaluate();
        void keyPressEvent(QKeyEvent *keyEvent);
    
    public slots:
        void timeOutSlot();

    protected:
        void paintTank(s_tank &tank);
        bool m_debug=true;
        int m_nbEvalPerFrame=10;
};
