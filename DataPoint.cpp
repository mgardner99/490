/*
  Joey Frohlinger
  for ELEC 490
  Group Members:    Bren Piper
                    Adam Bunn
                    Joey Frohlinger
  Supervisor:       Dr. Evelyn Morin

  */

#include "DataPoint.h"

DataPoint::DataPoint(){
    val = 0;
    location = QPoint(0,0);
}

DataPoint::DataPoint(int x, int y, qint16 v){
    DataPoint(QPoint(x,y),v);
}
DataPoint::DataPoint(QPoint l, qint16 v){
    setLocation(l);
    setVal(v);
}

qint16 DataPoint::getVal(){
    return val;
}

QPoint DataPoint::getLocation(){
    return location;
}

int DataPoint::getX(){
    return location.x();
}

int DataPoint::getY(){
   return location.y();
}

void DataPoint::setLocation(int x, int y){
    setLocation(QPoint(x,y));
}

//should probably add some error checking here
void DataPoint::setLocation(QPoint p){
    location = p;
}

//should probably add some error checking here
void DataPoint::setVal(qint16 v){
    val = v;
}

float DataPoint::getDist(int x, int y){
    return qSqrt(qPow(y-location.y(),2)+qPow(x-location.x(),2));
}
