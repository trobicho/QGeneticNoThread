#include "QTank.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    srand(time(NULL));
    
    QTank tank;
    tank.show();

    return app.exec();
}
