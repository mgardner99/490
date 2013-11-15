/*
  Joey Frohlinger
  for ELEC 490
  Group Members:    Bren Piper
                    Adam Bunn
                    Joey Frohlinger
  Supervisor:       Dr. Evelyn Morin

  */

//#include <QtGui/QApplication> //defunct
#include <QtWidgets/QApplication> //newly moved library for 5.0 update
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int exitStat = a.exec();
    cout<<"exit"<<endl;
    w.commThread->terminate();
    delete w.comm;
    return exitStat;
}
