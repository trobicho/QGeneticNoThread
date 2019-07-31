#pragma once
#include "WinGL.h"
#include "../genetic/PoolFunc/Miam.h"

class QMiam: public Miam, public WinGL
{
    public:
        QMiam():QMiam(20){};
        QMiam(int nbPeople);
        ~QMiam(){};
        void paintGL();
        void evaluate();
    
    public slots:
        void timeOutSlot();

    protected:
        void paintMiam(s_miam &miam);
        bool m_debug=false;
};
