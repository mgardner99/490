/*
  Joey Frohlinger
  for ELEC 490
  Group Members:    Bren Piper
                    Adam Bunn
                    Joey Frohlinger
  Supervisor:       Dr. Evelyn Morin

  */

#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <QPoint>
#include <QtCore/qmath.h>
class DataPoint{
public:
    DataPoint();
    DataPoint(QPoint l, qint16 v);
    DataPoint(int x, int y, qint16 v);

    qint16 getVal();
    QPoint getLocation();

    int getX();
    int getY();

    void setVal(qint16 v);
    void setLocation(QPoint p);
    void setLocation(int x, int y);

    float getDist(int x, int y); //gets the distance between the point and an image pixel.

private:
    QPoint location;
    qint16 val;
};

#endif // DATAPOINT_H
