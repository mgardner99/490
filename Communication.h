#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include "DataPoint.h"
#include <queue>
#include <sstream>
#include <QStringList>
#include <fstream>
#include <time.h>

using namespace std;
using namespace boost::asio;

class Communication: public QObject{
    Q_OBJECT
public:
    Communication(string comPort);
    ~Communication();

    vector<DataPoint>* getData();
    static QStringList getPortsList();

private:
    serial_port* port;
    io_service* io;
    char msg[512];
    vector<DataPoint>* data;
    queue<char> q;
   // int valNum;
    fstream file;
    void readData();
    void dataSet(int sense);
    bool mutex;
    void findFront();

public slots:
    void update();

};

#endif // COMMUNICATION_H


