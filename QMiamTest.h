#pragma once
#include "QMiam.h"

class QMiamTest: public QMiam
{
    public:
        QMiamTest();
        void keyPressEvent(QKeyEvent *keyEvent);
        void paintGL();
    
    public slots:
        void timeOutSlot();
    
    protected:
        void paintMiam(s_miam &miam);
};
