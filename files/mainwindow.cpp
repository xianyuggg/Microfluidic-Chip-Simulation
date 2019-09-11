#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLayout"
#include "QPushButton"
#include "QFile"
#include "QLabel"
#include "QSpacerItem"
#include <QtWinExtras>
#include "advanced_dialog.h"
#include "chip.h"
#include <QFont>






MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    draw_area=nullptr;
    /*
     * 将指针先声明为空指针便于检查以释放内存
     */
    resolution_status=0;
        //the default is 1080p
    this->setWindowTitle("Microfluidic Chip Simulation");
    //this->setFixedSize(800,800);
    this->setFixedSize(900,900);


    //1080p显示屏设置为800,800;
    start  = new Start(this);
    info = new Info();
    /*
     * 设置win毛玻璃效果
     */
    if (QtWin::isCompositionEnabled()) {
        QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
        setAttribute(Qt::WA_TranslucentBackground, true);
        setAttribute(Qt::WA_NoSystemBackground, false);
        setStyleSheet("MainWindow { background: transparent; }");
    } else {

        QtWin::resetExtendedFrame(this);
        setAttribute(Qt::WA_TranslucentBackground, false);
        setStyleSheet(QString("MainWindow { background: %1; }")
                      .arg(QtWin::realColorizationColor().name()));
    }
    this->setWindowOpacity(0.97);
    this->setCentralWidget(start);


    connect(start->SignalMapper,SIGNAL(mapped(int)),this,SLOT(show_advanced_dialog(int)));

    connect(start,SIGNAL(signal_resolution()),this,SLOT(change_resolution()));
}


void MainWindow::change_resolution()
{
    if(!resolution_status)
    {
        resolution_status=1;
        this->setFixedSize(1500,1500);
        delete start;
        start=new Start(this);
        this->setCentralWidget(start);
        connect(start,SIGNAL(signal_resolution()),this,SLOT(change_resolution()));
        connect(start->SignalMapper,SIGNAL(mapped(int)),this,SLOT(show_advanced_dialog(int)));
    }
    else
    {
        this->setFixedSize(900,900);
        resolution_status=0;
        delete start;
        start=new Start(this);
        this->setCentralWidget(start);
        connect(start,SIGNAL(signal_resolution()),this,SLOT(change_resolution()));
        connect(start->SignalMapper,SIGNAL(mapped(int)),this,SLOT(show_advanced_dialog(int)));
    }

}

MainWindow::~MainWindow()
{

    delete ui;
    delete chip;
    delete start;
    delete info;
    delete draw_area;
    delete advanced;

}

void MainWindow::init_chip(int a,int b,int c,int d,int e,int f)
{

    chip=new Chip(a,b,c,d,e,f);

}
void MainWindow::show_draw_area()
{
    delete start;
    start=nullptr;
    draw_area=new DrawArea(this);
    this->setCentralWidget(draw_area);

    advanced->close();

}

void MainWindow::on_actionNew_triggered()
{
    if(draw_area!=nullptr)
    {delete draw_area;draw_area=nullptr;}
    start=new Start(this);
    connect(start,SIGNAL(signal_resolution()),this,SLOT(change_resolution()));
    connect(start->SignalMapper,SIGNAL(mapped(int)),this,SLOT(show_advanced_dialog(int)));
    this->setCentralWidget(start);
    if(info!=nullptr)
    {delete info;info=nullptr;}

}


void MainWindow::on_actioninformation_triggered()
{
    if(draw_area!=nullptr)
    {delete draw_area;draw_area=nullptr;}
    info=new Info(this);
    this->setCentralWidget(info);
    if(start!=nullptr)
       {delete start;start=nullptr;}
}


/*
 * 在此处connect的理由：advanced还没有被实例化
 */
void MainWindow::show_advanced_dialog(int num)
{
    advanced=new Advanced_dialog(num,this);
    advanced->show();
    connect(advanced,SIGNAL(data(int,int,int,int,int,int)),this,SLOT(init_chip(int,int,int,int,int,int)));
    connect(advanced,SIGNAL(data(int,int,int,int,int,int)),this,SLOT(show_draw_area()));
    //connect(advanced,SIGNAL(data(int,int,int,int,int,int)),draw_area->working_area,SLOT(draw_area->working_area->setnum(int,int,int,int,int,int)));
}
//警戒此时draw-area还没有进行实例化
