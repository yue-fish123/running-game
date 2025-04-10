#include "mainwindow.h"
#include "startscence.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Startscence start_scence;
    if(start_scence.exec()==Startscence::Accepted){
        MainWindow w;
        w.show();
        return a.exec();
    }
    else{
        return 0;
    }
}
