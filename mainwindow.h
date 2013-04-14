/*
  Joey Frohlinger
  for ELEC 490
  Group Members:    Bren Piper
                    Adam Bunn
                    Joey Frohlinger
  Supervisor:       Dr. Evelyn Morin

  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include "heatmap.h"
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QTimer>
#include "DataPoint.h"
#include "Communication.h"
#include <phonon/phonon>
#include <QThread>
#include <QShortcut>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    HeatMap m;
    vector<DataPoint>* vec;
    QPixmap pix;
    QGraphicsScene *scene;
    QGraphicsItem* pixItem;
    float fudger;
    QImage footMask;
    QThread* commThread;
    Communication* comm;
    Phonon::VideoPlayer *vidPlayer;
    Phonon::SeekSlider *vidSeek;
    bool vidLoaded;
    QString vidPathText;

    QShortcut *leftArrow;
    QShortcut *rightArrow;

    QString currentComPort;


    void uiInit();

 private slots:
    void update();
    void commTimer();
    void vidTime();
    void on_comPortBox_currentIndexChanged(const QString &arg1);

    void on_vidPlay_clicked();
    void on_vidPath_textEdited(const QString &arg1);
    void on_vidPause_clicked();

    void on_vidPath_returnPressed();
    void on_vidStartLoopSet_clicked();
    void on_vidEndLoopSet_clicked();
    void leftArrowSlot();
    void rightArrowSlot();
    void on_vidStop_clicked();
    void on_comPortBox_activated(const QString &arg1);


    void changeCom();
    void on_fileBrowserButton_clicked();
    void on_MainWindow_destroyed();
};

#endif // MAINWINDOW_H
