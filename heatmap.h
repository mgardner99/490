/*
  Joey Frohlinger
  for ELEC 490
  Group Members:    Bren Piper
                    Adam Bunn
                    Joey Frohlinger
  Supervisor:       Dr. Evelyn Morin

  */

#ifndef HEATMAP_H
#define HEATMAP_H

#include <QImage>
#include <vector>
#include <QColor>
#include "DataPoint.h"
#include <iostream>
#include <QTimer>
#include <QWidget>
#include <QPainter>
#include <QRect>


using namespace std;

class HeatMap: public QImage
{

public:
    HeatMap(QSize size, QImage::Format form);

    void genMap(vector<DataPoint> vec);
    void update();
    static const float RADC = .5; //fudge factor for pressure algorithm
    void applyMask(const QImage &mask);

private:




};

#endif // HEATMAP_H
