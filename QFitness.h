#pragma once
#include "WinGL.h"
#include "../genetic/Fitness.h"

class QFitness: public WinGL
{
    Q_OBJECT
    public:
        QFitness(int fps = 0, QWidget *parent = 0, char *name = 0):WinGL(fps, parent, name){;}
        virtual Fitness* create_newFitnessObject(void)=0;
        virtual Fitness* get_fitnessObject(void)=0;
        virtual int get_nbGene()=0;
        virtual void geneCopy(double *gene)=0;
        virtual void geneCopy(double *gene, int gen)=0;
    
    signals:
        void signal_displayFinish(void);
};
