#include "advanced_dialog.h"
#include "QLayout"
#include "QSpacerItem"
#include "qsizepolicy.h"
#include "QMessageBox"
#include <mainwindow.h>

Advanced_dialog::Advanced_dialog(int num1,QWidget *parent):QDialog(parent),num(num1)
{
    s_c1=-1;
    s_c2=-1;
    e_c1=-1;
    e_c2=-1;
    e_c3=-1;

    //this->setAttribute(Qt::WA_DeleteOnClose);
    QVBoxLayout *overall=new QVBoxLayout(this);
    QHBoxLayout *first=new QHBoxLayout();
    QHBoxLayout *second=new QHBoxLayout();
    QHBoxLayout *third=new QHBoxLayout();
    QHBoxLayout *fourth=new QHBoxLayout();
    QHBoxLayout *fifth=new QHBoxLayout();




    MainWindow *pp =(MainWindow*)(this->parentWidget());
    this->setModal(true);

    if(pp->resolution_status==0)
        {
        overall->addLayout(first);
        overall->addLayout(second);
        overall->addLayout(third);
        overall->addLayout(fourth);
        overall->addLayout(fifth,5);
        e_num=new QLineEdit();
        l_num=new QLabel("请输入列数/行数");

        QSpacerItem *spaceItem1 = new QSpacerItem(64,20,QSizePolicy::Minimum,QSizePolicy::Expanding);
        first->addWidget(l_num);
        first->addSpacerItem(spaceItem1);
        first->addWidget(e_num);
        if(num==0)
            e_num->setPlaceholderText("5~8");
        else
            e_num->setText(QString::number(num,10));


        l_s=new QLabel("请输入起始管道1，2的列数");
        QSpacerItem *spaceItem2 = new QSpacerItem(40,20,QSizePolicy::Minimum,QSizePolicy::Expanding);
        e_s_1=new QLineEdit();
        e_s_2=new QLineEdit();
        second->addWidget(l_s);
        second->addSpacerItem(spaceItem2);
        second->addWidget(e_s_1);
        second->addWidget(e_s_2);


        l_e=new QLabel("请输入输出管道1，2，3的列数");
        QSpacerItem *spaceItem3 = new QSpacerItem(22,20,QSizePolicy::Minimum,QSizePolicy::Expanding);
        e_e_1=new QLineEdit();
        e_e_2=new QLineEdit();
        e_e_3=new QLineEdit();
        third->addWidget(l_e);
        third->addSpacerItem(spaceItem3);
        third->addWidget(e_e_1);
        third->addWidget(e_e_2);
        third->addWidget(e_e_3);

        l_lw=new QLabel("请输入长度与宽度");
        QSpacerItem *spaceItem4 = new QSpacerItem(88,20,QSizePolicy::Minimum,QSizePolicy::Expanding);
        e_l=new QLineEdit();
        e_w=new QLineEdit();
        e_l->setReadOnly(1);
        e_w->setReadOnly(1);
        e_l->setPlaceholderText("1600微米");
        e_w->setPlaceholderText("200微米");

        fourth->addWidget(l_lw);
        fourth->addSpacerItem(spaceItem4);
        fourth->addWidget(e_l);
        fourth->addWidget(e_w);


        QSpacerItem *spaceItem5 = new QSpacerItem(150,20,QSizePolicy::Minimum,QSizePolicy::Expanding);
        cancel=new QPushButton("取消");

        start =new QPushButton("开始");

        //cancel->setSizePolicy(QSizePolicy::Preferred);
        //start ->setSizePolicy(QSizePolicy::Preferred);
        fifth->addSpacerItem(spaceItem5);

        fifth->addWidget(cancel);
        fifth->addSpacerItem(spaceItem5);
        fifth->addWidget(start);
        fifth->addSpacerItem(spaceItem5);
            start->setFixedSize(60,60);
            cancel->setFixedSize(60,60);
            this->setFixedSize(400,200);
            style = new QFile(":/style/buttonstyle_advanced.qss", this);
            style->open(QFile::ReadOnly);
            QString styleSheet = tr(style->readAll());
            this->setStyleSheet(styleSheet);
        }
    else
        {
        overall->addLayout(first,2);
        overall->addLayout(second,2);
        overall->addLayout(third,2);
        overall->addLayout(fourth,2);
        overall->addLayout(fifth,5);
        e_num=new QLineEdit();
        l_num=new QLabel("请输入列数/行数");


        first->addWidget(l_num);
        first->addSpacing(200);
        first->addWidget(e_num);

        if(num==0)
            e_num->setPlaceholderText("5~8");
        else
            e_num->setText(QString::number(num,10));


        l_s=new QLabel("请输入起始管道1，2的列数");

        e_s_1=new QLineEdit();
        e_s_2=new QLineEdit();
        second->addWidget(l_s);
        second->addSpacing(105);
        second->addWidget(e_s_1);
        second->addSpacing(20);
        second->addWidget(e_s_2);


        l_e=new QLabel("请输入输出管道1，2，3的列数");

        e_e_1=new QLineEdit();
        e_e_2=new QLineEdit();
        e_e_3=new QLineEdit();
        third->addWidget(l_e);
        third->addSpacing(73);
        third->addWidget(e_e_1);
        third->addSpacing(10);
        third->addWidget(e_e_2);
        third->addSpacing(10);
        third->addWidget(e_e_3);

        l_lw=new QLabel("请输入长度与宽度");

        e_l=new QLineEdit();
        e_w=new QLineEdit();
        e_l->setReadOnly(1);
        e_w->setReadOnly(1);
        e_l->setPlaceholderText("1600微米");
        e_w->setPlaceholderText("200微米");

        fourth->addWidget(l_lw);
        fourth->addSpacing(188);
        fourth->addWidget(e_l);
        fourth->addSpacing(15);
        fourth->addWidget(e_w);



        cancel=new QPushButton("取消");

        start =new QPushButton("开始");

        //cancel->setSizePolicy(QSizePolicy::Preferred);
        //start ->setSizePolicy(QSizePolicy::Preferred);


        fifth->addWidget(cancel);

        fifth->addWidget(start);

            start->setFixedSize(130,130);
            cancel->setFixedSize(130,130);
            this->setFixedSize(900,500);
            style = new QFile(":/style/buttonstyle_advanced_surface.qss", this);
            style->open(QFile::ReadOnly);
            QString styleSheet = tr(style->readAll());
            this->setStyleSheet(styleSheet);


        }
    //1080p显示屏设置为400，200；
    //surface设置为500，250







    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    /*
     * 动态检测用户输入数据的状况
     * 使得用户输入越界的范围变成红色（换肤？）
    */
    connect(e_num,SIGNAL(textChanged(QString)),this,SLOT(check_num_valid()));

    connect(e_s_1,SIGNAL(textChanged(QString)),this,SLOT(check_s_valid()));
    connect(e_s_2,SIGNAL(textChanged(QString)),this,SLOT(check_s_valid()));

    connect(e_e_1,SIGNAL(textChanged(QString)),this,SLOT(check_e_valid()));
    connect(e_e_2,SIGNAL(textChanged(QString)),this,SLOT(check_e_valid()));
    connect(e_e_3,SIGNAL(textChanged(QString)),this,SLOT(check_e_valid()));


    connect(start,SIGNAL(clicked()),this,SLOT(start_draw()));











}

void Advanced_dialog::start_draw()
{
    if(check_e_valid()&&check_num_valid()&&check_s_valid())
        emit data(num,s_c1,s_c2,e_c1,e_c2,e_c3);

    else
    {
        QMessageBox msgbox;
        msgbox.setText("非法输入！");
        msgbox.exec();
    }
}




bool Advanced_dialog::check_e_valid()
{
    QString tem1=e_e_1->text();
    int tem11=tem1.toInt();
    QString tem2=e_e_2->text();
    int tem21=tem2.toInt();
    QString tem3=e_e_3->text();
    int tem31=tem3.toInt();
    if(tem11>=0&&tem11<num&&tem11!=e_c2&&tem11!=e_c3)
        {
            e_e_1->setStyleSheet("QLineEdit{color:black;}");
                 e_c1=tem11;
        }
    else
        {
            e_e_1->setStyleSheet("QLineEdit{color:red;}");
            return false;
        }


    if(tem21>=0&&tem21<num&&tem21!=e_c1&&tem21!=e_c3)
        {
            e_e_2->setStyleSheet("QLineEdit{color:black;}");
                 e_c2=tem21;
        }
    else
        {
            e_e_2->setStyleSheet("QLineEdit{color:red;}");
            return false;
        }

    if(tem31>=0&&tem31<num&&tem31!=e_c1&&tem31!=e_c2)
        {
            e_e_3->setStyleSheet("QLineEdit{color:black;}");
                 e_c3=tem31;
        }
    else
        {
            e_e_3->setStyleSheet("QLineEdit{color:red;}");
            return false;
        }
    return true;
}


bool Advanced_dialog::check_s_valid()
{
    QString tem1=e_s_1->text();
    int tem11=tem1.toInt();
    QString tem2=e_s_2->text();
    int tem21=tem2.toInt();
    if(tem11>=0&&tem11<num&&tem11!=s_c2)
        {
            e_s_1->setStyleSheet("QLineEdit{color:black;}");
                 s_c1=tem11;
        }
    else
        {
            e_s_1->setStyleSheet("QLineEdit{color:red;}");
            return false;
        }

    if(tem21>=0&&tem21<num&&tem21!=s_c1)
        {
            e_s_2->setStyleSheet("QLineEdit{color:black;}");
                 s_c2=tem21;
        }
    else
        {
            e_s_2->setStyleSheet("QLineEdit{color:red;}");
            return false;
        }
    return true;
}
bool Advanced_dialog::check_num_valid()
{
    QString tem=e_num->text();
    if(tem.toInt()>8||tem.toInt()<5)
        {e_num->setStyleSheet("QLineEdit{color:red;}");
         return false;
        }
    else
        {e_num->setStyleSheet("QLineEdit{color:black;}");
         num=tem.toInt();
        }
    if(tem.isEmpty())
    {
        e_num->setStyleSheet("QLineEdit{color:black;}");
        e_num->setPlaceholderText("5~8");
    }
    return true;
}

Advanced_dialog::~Advanced_dialog()
{
    delete cancel;
    delete start;
    delete e_num;
    delete l_num;
    delete e_s_1;
    delete e_s_2;
    delete e_e_1;
    delete e_e_2;
    delete e_e_3;
    delete l_s;
    delete l_e;
    delete l_lw;
    delete e_l;
    delete e_w;
    delete style;
}





