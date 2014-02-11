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
#include "KneeVec.h"

using namespace std;
using namespace boost::asio;

class Communication: public QObject{
    Q_OBJECT
public:
    Communication(string comPort);
    ~Communication(); //destructor

    vector<DataPoint>* getData();
    static QStringList getPortsList();
    KneeVec getAngleData1();
    KneeVec getAngleData2();

private:
    serial_port* port;
    io_service* io;
    char msg[512];
    vector<DataPoint>* data;
    QString angleData1;
    QString angleData2;
    queue<char> q;
    fstream file;
    bool startFile;
    void readData();
    void dataSet(int sense);
    bool mutex;
    void findFront();
    void getAngle(int sensor, int dir);
    KneeVec k1;
    KneeVec k2;


public slots:
    void update();

};

#endif // COMMUNICATION_H


