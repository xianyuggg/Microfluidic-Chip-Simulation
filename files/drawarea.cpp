#include "drawarea.h"
#include <QStyle>
#include <QStyleOption>
#include <mainwindow.h>
#include <QDebug>
DrawArea::DrawArea(QWidget *parent) : QWidget(parent)
{

    MainWindow* p=(MainWindow*)parentWidget();


    change_dialog=nullptr;

    overall=new QVBoxLayout(this);
    first=new QHBoxLayout();
    second=new QHBoxLayout();
    rightcorner=new  QVBoxLayout();
    add=new QPushButton("添加");
    erase=new QPushButton("擦除");
    clear=new QPushButton("清空");
    undo=new QPushButton("撤销");
    edit1=new QLineEdit;
    edit1->setPlaceholderText("请输入输入管道1的流速");
    edit2=new QLineEdit;
    edit2->setPlaceholderText("请输入输入管道2的流速");
    caculate=new QPushButton("计算");
    label1=new QLabel("输出管道1的流速为: ");
    label2=new QLabel("输出管道2的流速为: ");
    label3=new QLabel("输出管道3的流速为: ");
    change_io=new QPushButton("更改出入口");
    overall->addLayout(first,2);
    overall->addLayout(second,15);
    overall->addSpacing(20);
    working_area=new WorkingArea(this);
    help=new QLabel(this);
    help->setMouseTracking(1);
    tooltip=new Mytooltip(0);


    QPixmap pixmap(":/image/question.png");
    QSize picSize(100,100);
    QPixmap scaledPixmap=pixmap.scaled(picSize,Qt::KeepAspectRatio);
    help->setPixmap(scaledPixmap);
    help->setFrameStyle(0);
    help->setAttribute(Qt::WA_TranslucentBackground);

    this->setMouseTracking(true);


    if(!p->resolution_status)
    {
        spaceItem_first= new QSpacerItem(300,20,QSizePolicy::Minimum,QSizePolicy::Expanding);
        erase->setFixedSize(70,70);
        add->setFixedSize(70,70);
        clear->setFixedSize(70,70);
        undo->setFixedSize(70,70);
        change_io->setFixedSize(140,70);

        first->addWidget(add);
        first->addWidget(erase);
        first->addWidget(clear);
        first->addWidget(undo);
        first->addWidget(change_io);
        first->addSpacerItem(spaceItem_first);
        first->addWidget(help);


         caculate->setFixedSize(150,60);
         edit1->setFixedSize(150,30);
         edit2->setFixedSize(150,30);

        //label1->setSizePolicy(Qt::PreferredSize);
        //label2->setSizePolicy(Qt:: );
        //label3->setSizePolicy(expanding);
        rightcorner->addWidget(edit1);
        rightcorner->addWidget(edit2);
        rightcorner->addSpacing(30);
        rightcorner->addWidget(caculate);
        rightcorner->addSpacing(30);
        rightcorner->addWidget(label1);
        rightcorner->addSpacing(30);
        rightcorner->addWidget(label2);
        rightcorner->addSpacing(30);
        rightcorner->addWidget(label3);
        rightcorner->addSpacing(30);
        //working_area->setMinimumSize(500,500);
        working_area->show();
        working_area->setStyleSheet("QWidget{background: rgb(232, 241, 252);}");
        second->setSpacing(40);
        second->addWidget(working_area,20);
        second->setSpacing(20);

        second->addLayout(rightcorner,5);
    }
    else
    {
        spaceItem_first= new QSpacerItem(500,20,QSizePolicy::Minimum,QSizePolicy::Expanding);
        erase->setFixedSize(150,130);
        add->setFixedSize(150,130);
        clear->setFixedSize(150,130);
        undo->setFixedSize(150,130);
        change_io->setFixedSize(200,130);

        first->addWidget(add);
        first->addWidget(erase);
        first->addWidget(clear);
        first->addWidget(undo);
        first->addWidget(change_io);
        first->addSpacerItem(spaceItem_first);
        first->addWidget(help);




         caculate->setFixedSize(200,200);
         edit1->setFixedHeight(60);
         edit2->setFixedHeight(60);

        //label1->setSizePolicy(Qt::PreferredSize);
        //label2->setSizePolicy(Qt:: );
        //label3->setSizePolicy(expanding);
        rightcorner->addWidget(edit1);
        rightcorner->addWidget(edit2);
        rightcorner->addSpacing(160);
        rightcorner->addWidget(caculate);
        rightcorner->addSpacing(160);
        rightcorner->addWidget(label1);
        rightcorner->addSpacing(60);
        rightcorner->addWidget(label2);
        rightcorner->addSpacing(60);
        rightcorner->addWidget(label3);
        rightcorner->addSpacing(60);
        //working_area->setMinimumSize(500,500);
        working_area->show();
        working_area->setStyleSheet("QWidget{background: rgb(232, 241, 252);}");
        second->setSpacing(40);
        second->addWidget(working_area,20);
        second->setSpacing(20);

        second->addLayout(rightcorner,5);
    }



    /*
     * 设置所有button的属性,add,erase,delete
     */
    add->setCheckable(true);
    connect(add,SIGNAL(toggled(bool)),working_area,SLOT(add_is_checked(bool)));

    erase->setCheckable(true);
    connect(erase,SIGNAL(toggled(bool)),working_area,SLOT(erase_is_checked(bool)));

    connect(change_io,SIGNAL(clicked()),this,SLOT(change_line()));
    //关联undo与workingarea中的撤销功能
    connect(undo,SIGNAL(clicked()),working_area,SLOT(ctrl_z()));
    connect(clear,SIGNAL(clicked()),working_area,SLOT(ctrl_c()));
    erase->setChecked(false);
    add->setChecked(false);

    //connect(edit1,SIGNAL(textChanged(QString)),this,SLOT(get_data_from_edit()));


    connect(caculate,SIGNAL(clicked()),working_area,SLOT(moveData()));
    connect(caculate,SIGNAL(clicked()),this,SLOT(get_data_from_edit()));
    connect(edit1,SIGNAL(textChanged(QString)),this,SLOT(get_data_from_edit()));
    connect(edit2,SIGNAL(textChanged(QString)),this,SLOT(get_data_from_edit()));
    connect(working_area,SIGNAL(move_complete()),working_area->chip,SLOT(getAnswer()));
    connect(working_area->chip,SIGNAL(success()),this,SLOT(showAnswer()));
    connect(working_area->chip,SIGNAL(velocity(vector<double>&)),working_area,SLOT(get_velocity(vector<double>&)));


}

/*
 * 交互方式：alt为（同lr）
 *         将alt换回即可切换回画笔
 *         ctrl+z为撤销
 */

void DrawArea::get_data_from_edit()
{
    int n=this->working_area->tnum;
    int order=(2*n*n)-(2*n);
    this->working_area->chip->edges[order].v=edit1->text().toDouble();
    this->working_area->chip->edges[order+1].v=edit2->text().toDouble();
    //qDebug() << "Signal from DrawArea::get_data_from_edit() received";
    //qDebug() << "v1" << this->working_area->chip->edges[order].v;
    //qDebug() << "v2" << this->working_area->chip->edges[order+1].v;

}
void DrawArea::showAnswer()
{


   label1->setText(QString::number(this->working_area->chip->answer1, 10, 4));
   label2->setText(QString::number(this->working_area->chip->answer2, 10, 4));
   label3->setText(QString::number(this->working_area->chip->answer3, 10, 4));
   qDebug() << "Signal from DrawArea::show_answer received()";
   this->working_area->chip->answer1=0;
   this->working_area->chip->answer2=0;
   this->working_area->chip->answer3=0;


}
void::DrawArea::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Alt)
       {    erase->setChecked(true);
            qDebug() << "alt键被按下";
        }
    /*
     * 按下alt代表可以进行删除操作
     */
    if(event->modifiers()==Qt::ControlModifier)
    {
        if(event->key()==Qt::Key_Z)
            this->working_area->ctrl_z();
        if(event->key()==Qt::Key_C)
            this->working_area->ctrl_c();

    }


}
void::DrawArea::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Alt)
       {    erase->setChecked(false);
            add->setChecked(true);
        }

}

void DrawArea::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);

    QPainter *painter=new QPainter(this);
   // painter->setPen(Qt::BevelJoin);
   // painter->setPen(Qt::RoundCap);
    MainWindow* p=(MainWindow*)parentWidget();
    if(!p->resolution_status)
    {
        style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);  //使自定义的widget有背景颜色
        file = new QFile(":/style/style_for_drawarea.qss", this);
                // 只读方式打开该文件
        file->open(QFile::ReadOnly);
                // 读取文件全部内容，使用tr()函数将其转换为QString类型
        QString styleSheet = tr(file->readAll());
                // 为QApplication设置样式表
        this->setStyleSheet(styleSheet);
    }
    else
    {
        style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);  //使自定义的widget有背景颜色
        file = new QFile(":/style/style_for_drawarea_surface.qss", this);
                // 只读方式打开该文件
        file->open(QFile::ReadOnly);
                // 读取文件全部内容，使用tr()函数将其转换为QString类型
        QString styleSheet = tr(file->readAll());
                // 为QApplication设置样式表
        this->setStyleSheet(styleSheet);

    }
    delete painter;
    delete file;

}


//与change_io的click连接起来
void DrawArea::change_line()
{
    change_dialog=new Change_dialog(working_area->chip->num,working_area->chip->s1,working_area->chip->s2,working_area->chip->e1,working_area->chip->e2,working_area->chip->e3,this);
    MainWindow* p=(MainWindow*)parentWidget();
    connect(change_dialog,SIGNAL(changed_data(int,int,int,int,int)),this->working_area->chip,SLOT(change_data(int,int,int,int,int)));
    connect(this->working_area->chip,SIGNAL(change_success()),this->working_area,SLOT(update()));
    //if(p->resolution_status)
        //change_dialog->setFixedSize(1000,500);
    //else
        //change_dialog->setFixedSize(700,323);

    change_dialog->show();


}


/*
 * 用来实现动态的tooltip
 */
void DrawArea::mouseMoveEvent(QMouseEvent *event)
{

    int lux=help->geometry().x();
    int luy=help->geometry().y();
    int w=help->geometry().width();
    int h=help->geometry().height();


    qDebug() << "help窗口的x,y,w,h" << lux << luy << w << h;
    qDebug() << event->x() << event->y();

    /*
    qDebug() << "cursor" << point.x() << point.y();
    qDebug() << "relative" << relative_x << relative_y;
    int offsetx;
    int offsety;
    //offsetx=lux+w/2-rpoint.x();
   // offsety=luy+h/2-rpoint.y();
    tooltip->show();
    QPoint rpoint=mapFromGlobal(QPoint (tooltip->geometry().x(),tooltip->geometry().y()));
    offsetx=lux-rpoint.x();
    offsety=luy-rpoint.y();
    qDebug() <<"1" << rpoint.x() << rpoint.y() <<offsetx << offsety;
    tooltip->move(offsetx,offsety);
    offsetx=lux-rpoint.x();
    offsety=luy-rpoint.y();
    rpoint=mapFromGlobal(QPoint (tooltip->geometry().x(),tooltip->geometry().y()));
     qDebug() <<"2"<< rpoint.x() << rpoint.y() <<offsetx << offsety;
    */

    QPoint p=event->pos();

    if( event->x() >=lux&& event->x() <=(lux+w)&& event->y()<=(luy+h) && event->y() >=luy)
        {
            qDebug() << "signal";
            tooltip->move(p);

            tooltip->show();
    }
    else
        {

            tooltip->close();

        }



}





