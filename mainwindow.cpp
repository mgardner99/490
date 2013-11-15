#include "mainwindow.h"
#include "ui_mainwindow.h" // do NOT remove this, screws up everything.
#include <QTime>
#include <QtMultimedia>
#include <QVideoSurfaceFormat>
#include <QGraphicsVideoItem>

using namespace std;
/*2013/2014
 *Megan Gardner
 *for ELEC 490
 *Group Members:    Kevin Cook
 *                  Megan Gardner
 *                  Cameron Kramer
 *
 *2012/2013
  Joey Frohlinger
  for ELEC 490
  Group Members:    Bren Piper
                    Adam Bunn
                    Joey Frohlinger
  Supervisor:       Dr. Evelyn Morin

  */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m(QSize(400,400),QImage::Format_RGB32)//constructor for heatmap

{
    ui->setupUi(this);

    leftArrow = new QShortcut(Qt::Key_Left,this, SLOT(leftArrowSlot()));
    rightArrow = new QShortcut(Qt::Key_Right,this,SLOT(rightArrowSlot()));

    QGridLayout *grid = new QGridLayout(ui->vidWidget);
    grid->setSpacing(20);
    //vidPlayer = new VidPlayer(ui->vidWidget); //parent for video player is ui->vidWidget
 //   vidPlayer = new Phonon::VideoPlayer(Phonon::VideoCategory, ui->vidWidget);
   // grid->addWidget(vidPlayer,1,0,3,1);
    vidLoaded = false;
    videoItem = new QGraphicsVideoItem();
    videoItem->setSize(QSizeF(640,480));

    QGraphicsScene *sceneVid = new QGraphicsScene(this);
    QGraphicsView *graphicsview = new QGraphicsView(sceneVid);

    sceneVid->addItem(videoItem);
    grid->addWidget(graphicsview,1,0,3,1); //adds video scene widget to GUI - works

    mediaPlayer.setVideoOutput(videoItem);

    QGridLayout *gridS = new QGridLayout(ui->seekWidget);
    gridS->setSpacing(20);
   // vidSeek = new Phonon::SeekSlider(vidPlayer->mediaObject(),ui->seekWidget);
    vidSeek = new QSlider(Qt::Horizontal,ui->seekWidget);
    vidSeek->setRange(0,0);
    gridS->addWidget(vidSeek,1,0,3,1);
    comm = 0;
    commThread = new QThread(this);
    uiInit();//this function is to initialize the data in the UI (boxes etc)

    //timer based interrupt for screen rendering
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/60); //60 hz frame rate (or so)

    //timer for comm thread
    QTimer* timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(commTimer()));
    timer2->start(10);

    //timer for video ticker
    QTimer* timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(vidTime()));
    timer3->start(10);

    footMask.load("c:/Users/Megan/Documents/GitHub/ELEC490/leftFootMask.png"); // location of foot mask
    scene = new QGraphicsScene(); //create empty scene

    //vec = comm->getData();
    vec = new vector<DataPoint>;
    //cout<<"before"<<endl;
    m.genMap(*vec);
   // cout<<"after"<<endl;
    scene->setSceneRect(m.rect()); //set the scene's view rectangle to the image's
    pix = QPixmap::fromImage(m); //create a pixmap from the image
    pix = pix.scaled(ui->renderView->size());
    pixItem =  scene->addPixmap(pix); //add the pixmap to the scene
    ui->renderView->setSceneRect(pix.rect()); //set the renderviews view rectangle
    ui->renderView->setScene(scene); //set the renderViews scene
    commThread->start();

}

//update called from timer thread to lock frame rate
void MainWindow::update(){

    m.genMap(*vec);
    m.applyMask(footMask);
    scene->removeItem(pixItem);
    delete pixItem; //memory leak fix (What what!)
    pix = QPixmap::fromImage(m);
    pixItem = scene->addPixmap(pix);
}


void MainWindow::uiInit(){
    ui->comPortBox->addItems(Communication::getPortsList());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comPortBox_currentIndexChanged(const QString &arg1)
{

    currentComPort = arg1;
    changeCom();


}
void MainWindow::commTimer(){
    if(!commThread->isRunning())
    commThread->start();
}

void MainWindow::changeCom(){
    if(comm != 0){
        cout<<"com open already - killing"<<endl;
        commThread->terminate();
        delete comm;
        comm = 0;
    }
//    cout<<"Called"<<arg1.toStdString()<<endl;
    comm = new Communication(currentComPort.toStdString());
    comm->moveToThread(commThread);
    connect(commThread, SIGNAL(started()), comm, SLOT(update()));
    commThread->start();
    vec = comm->getData(); //pass data pointer
}



void MainWindow::on_vidPlay_clicked()
{
   // if(!vidLoaded){
        //vidPlayer->load(Phonon::MediaSource(vidPathText));
     //   vidPlayer->play();
       // vidLoaded = true;
    //}
    //else
    //    vidPlayer->play();
    mediaPlayer.play();
}
void MainWindow::vidTime(){
    /*
    static qint64 time;
    static int h;
    static int s;
    static int m;
    static int ms;

    time = vidPlayer->currentTime(); //elapsed time in milliseconds
    ms = time%1000;
    s = (time/1000) % 60;
    m = (time/60000)%60;
    h = (time/3600000);
    QTime qtime(h,m,s,ms);
    ui->timeEdit->setTime(qtime);

    if(ui->loopBox->isChecked()){
        if(qtime > ui->vidEndLoop->time()){
            ms = ui->vidStartLoop->time().msec();
            s = ui->vidStartLoop->time().second()*1000;
            m = ui->vidStartLoop->time().minute()*60000;
            h = ui->vidStartLoop->time().hour()*360000;

            vidPlayer->seek(h+m+s+ms);
        }
    }*/
}

void MainWindow::on_vidPath_textEdited(const QString &arg1)
{/*
    vidPathText = arg1;
    vidLoaded = false;*/
}


void MainWindow::on_vidPause_clicked()
{
    //vidPlayer->pause();

}

void MainWindow::on_vidPath_returnPressed()
{
    on_vidPlay_clicked();
}

void MainWindow::on_vidStartLoopSet_clicked()
{
    ui->vidStartLoop->setTime(ui->timeEdit->time());
}

void MainWindow::on_vidEndLoopSet_clicked()
{
    ui->vidEndLoop->setTime(ui->timeEdit->time());
}

void MainWindow::leftArrowSlot(){
   // if(!vidPlayer->isPlaying())
    //vidPlayer->seek(vidPlayer->currentTime()-33); // Why is 33?
}

void MainWindow::rightArrowSlot(){
    /*if(!vidPlayer->isPlaying())
        if(vidPlayer->currentTime() +33 < vidPlayer->totalTime())
        vidPlayer->seek(vidPlayer->currentTime() + 33);*/
}

void MainWindow::on_vidStop_clicked()
{
    mediaPlayer.stop();
    vidLoaded = false;
}

void MainWindow::on_comPortBox_activated(const QString &arg1)
{/*
     //cout<<"Called"<<arg1.toStdString()<<endl;
    if(comm != 0){
        cout<<"com open already - killing"<<endl;
        commThread->terminate();
        delete comm;
        comm = 0;
    }
    else{
    }
    for(int i = 0; i < 1; i ++){
    comm = new Communication(arg1.toStdString());
    comm->moveToThread(commThread);
    connect(commThread, SIGNAL(started()), comm, SLOT(update()));
    commThread->start();
    vec = comm->getData(); //pass data pointer
    }
    cout<<"opened " << arg1.toStdString()<<endl;*/
}

void MainWindow::on_fileBrowserButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
    ui->vidPath->setText(fileName);
    vidPathText = fileName;
    mediaPlayer.setMedia(QUrl::fromLocalFile(fileName)); // load media to mediaPlayer
}

void MainWindow::on_MainWindow_destroyed()
{
    cout<<"Exit"<<endl;
}
