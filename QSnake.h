#pragma once
#include <vector>
#include "QFitness.h"
#include "../genetic/fitnessFunc/Snake8_new.h"

class QSnake: public Snake8_new, public QFitness
{
    public:
        QSnake():QSnake(NULL){;}
        QSnake(s_vec2i max={50, 50}, int pixSize=5):QSnake(NULL, max, pixSize){};
        QSnake(QWidget *parent, s_vec2i max={50, 50}, int pixSize=5);
        ~QSnake(){};
        void paintGL();
        void keyPressEvent(QKeyEvent *keyEvent);
        int get_nbGene(){return Snake8_new::get_nbGene();}

        Fitness* create_newFitnessObject(void){};
        Fitness* get_fitnessObject(void){};
        void geneCopy(double *gene){};
        void geneCopy(double *gene, int gen){};

    public slots:
        void timeOutSlot();
    
    protected:
        void paintSnake();
        bool m_dbg=false;
        int m_pixSize;
};
