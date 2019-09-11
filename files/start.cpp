#include "start.h"
#include <QSignalMapper>
#include <QGridLayout>
#include <mainwindow.h>
Start::Start(QWidget *parent) : QWidget(parent)
{
    QString b_str[4]={"8*8","7*7","6*6","5*5"};
    but1=new QPushButton(b_str[0],this);
    but2=new QPushButton(b_str[1],this);
    but3=new QPushButton(b_str[2],this);
    but4=new QPushButton(b_str[3],this);
    change_resolution=new QPushButton("ChangeResoluton\n1080p/SurfaceBook",this);


    /*
     * 设置按钮效果
     * */
    QGridLayout *layout =new QGridLayout(this);
    layout->addWidget(but1,0,0);
    layout->addWidget(but2,2,0);
    layout->addWidget(but3,0,2);
    layout->addWidget(but4,2,2);
    layout->addWidget(change_resolution,1,1);

   // but1->setGeometry(150,150,200,200);
   // but2->setGeometry(450,150,200,200);
    //but3->setGeometry(150,450,200,200);
   // but4->setGeometry(450,450,200,200);
   // detail->setGeometry(300,300,200,200);

    MainWindow *p=(MainWindow*)parentWidget();
    if(p->resolution_status)
    {

        buttonstyle = new QFile(":/style/buttonstyle_start_surface.qss", this);

        buttonstyle->open(QFile::ReadOnly);
        QString styleSheet = tr(buttonstyle->readAll());

        this->but1->setFixedSize(500,500);
        this->but2->setFixedSize(500,500);
        this->but3->setFixedSize(500,500);
        this->but4->setFixedSize(500,500);
        this->change_resolution->setFixedSize(400,400);
        change_resolution->setStyleSheet("QPushButton{border-radius:200px;background-color: #111111;border-color: #333333;color : white;font-size:50px;}QPushButton:pressed {background-color:white;}");
        this->setStyleSheet(styleSheet);





    }
    else
    {

        buttonstyle = new QFile(":/style/buttonstyle.qss", this);

        buttonstyle->open(QFile::ReadOnly);

        QString styleSheet = tr(buttonstyle->readAll());

        change_resolution->setStyleSheet("QPushButton{border-radius:90;background-color: #111111;border-color: #333333;color : white;font-size:25px;}QPushButton:pressed {background-color:white;}");
        this->setStyleSheet(styleSheet);
        but1->setFixedSize(400,400);
        but2->setFixedSize(400,400);
        but3->setFixedSize(400,400);
        but4->setFixedSize(400,400);
        change_resolution->setFixedSize(200,200);
    }






    /*
     * 连接detail与模态对话框
     * 连接四个按钮与模态对话框
     * 需要将几个按钮与对应的数字映射起来
     */
    SignalMapper =new QSignalMapper(this);
    connect(but1,SIGNAL(clicked()),SignalMapper,SLOT(map()));
    SignalMapper->setMapping(but1,8);
    connect(but2,SIGNAL(clicked()),SignalMapper,SLOT(map()));
    SignalMapper->setMapping(but2,7);
    connect(but3,SIGNAL(clicked()),SignalMapper,SLOT(map()));
    SignalMapper->setMapping(but3,6);
    connect(but4,SIGNAL(clicked()),SignalMapper,SLOT(map()));
    SignalMapper->setMapping(but4,5);
    //connect(detail,SIGNAL(clicked()),SignalMapper,SLOT(map()));
    //SignalMapper->setMapping(detail,0);

    connect(change_resolution,SIGNAL(clicked()),this,SLOT(send_signal()));
    //发射改变分辨率的信号，最终的信号由mainwindow接受
    //SignalMapper的连接在mainwindow里面与show_advanced_dialog连接
}
Start::~Start()
{
    delete buttonstyle;
    delete but1;
    delete but2;
    delete but3;
    delete but4;
    delete change_resolution;
    delete SignalMapper;

}

void Start::send_signal()
{
    emit signal_resolution();
}

