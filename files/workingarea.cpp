#include "workingarea.h"
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include "drawarea.h"
#include "mainwindow.h"
#include <QMessageBox>

/*
 * 槽函数设置
 */


//转移数据到chip，（来自drawarea的caculate的信号）
void WorkingArea::moveData()
{
    for(int i=0;i<2*tnum*tnum-2*tnum+5;i++)
    {

        if(edge[i]==true)
            chip->setedgelength(i,1);
        if(edge[i]==false)
            chip->setedgelength(i,0);
    }
    if(chip->s2<chip->s1)                 /*按顺序排列好*/
    {
        int tem=chip->s1;
        chip->s1=chip->s2;
        chip->s2=tem;
    }
    if(chip->e1>chip->e2)
        {
            int tem=chip->e1;
            chip->e1=chip->e2;
            chip->e2=tem;
        }
    if(chip->e1>chip->e3)
        {
            int tem=chip->e1;
            chip->e1=chip->e3;
            chip->e3=tem;
        }
    if(chip->e2>chip->e3)
        {
            int tem=chip->e2;
            chip->e2=chip->e3;
            chip->e3=tem;
        }
    qDebug() << chip->s1 << chip->s2 << chip->e1 << chip->e2 << chip->e3;
    qDebug() << "Signal from WorkingArea::moveData";

    emit move_complete();


//添加按钮被按下
}
void WorkingArea::add_is_checked(bool check)
{
    this->setCursor(Qt::CrossCursor);
   QPushButton *btn=qobject_cast<QPushButton*>(sender());    //改变按钮对应的状态
    DrawArea *p=(DrawArea*)(this->parentWidget());              //获得父窗口，获得发送者信息
    if(btn->isChecked())
        {
            add=true;
            erase=false;
            p->erase->setChecked(false);
            p->add->setChecked(true);
            this->setMouseTracking(1);
        }
    else
        {add=false;
         p->add->setChecked(false);
         this->setMouseTracking(0);
        }

}
void WorkingArea::get_velocity(vector<double> &temv)
{

    for(int i=0;i<200;i++)
    {
        velocity[i]=temv[i];
    }
    /*
     * 此处的速度用来映射，需要计算一个相对于rgba的相对值
     * 即：相对于
     */
    int tem=2*tnum*tnum-2*tnum;
    int max;
    if(velocity[tem]==0&&velocity[tem+1]==0)   //处理两个都为0的情况
        return;

    if(velocity[tem]>velocity[tem+1])
        max=velocity[tem];
    else
        max=velocity[tem+1];
    for(int i=0;i<200;i++)
    {
        relative[i]=velocity[i]/max;
    }

    update();
}
//擦除按钮被按下
void WorkingArea::erase_is_checked(bool check)
{
    QPushButton *btn=qobject_cast<QPushButton*>(sender());    //改变按钮对应的状态
    DrawArea *p=(DrawArea*)(this->parentWidget());              //获得父窗口，获得发送者信息
    if(btn->isChecked())
    {
        add=false;
        erase=true;
        p->erase->setChecked(true);
        p->add->setChecked(false);
        this->setMouseTracking(1);
    }
    else
    {
        erase=false;
        p->erase->setChecked(false);
        this->setMouseTracking(0);
    }

}
//按下撤销按钮
void WorkingArea::ctrl_z()
{
    if(steps.empty())
    {
        QMessageBox msgbox;
        msgbox.setText("不可以再撤销了！");
        msgbox.exec();
    }
    else
    {
        int tem=steps.top();
        steps.pop();
        if(tem/1000==1)    //表示上一步是添加
            {
                tem=tem-1000;
                edge[tem]=false;
            }
        else
           edge[tem]=true;


    }
    update();

}
//全部删除按钮
void WorkingArea::ctrl_c()
{
    for(int i=0;i<2*tnum*tnum-2*tnum-1;i++)
        edge[i]=0;
    while(!steps.empty())
        steps.pop();
    for(int i=0;i<200;i++)
    {
        velocity[i]=0;
        relative[i]=0;
    }
    update();
}
WorkingArea::WorkingArea(QWidget *parent) : QWidget(parent)
{

    this->setMouseTracking(0);
    DrawArea* p = (DrawArea*)(this->parentWidget());
    MainWindow * pp = (MainWindow*)(p->parentWidget());
    chip=pp->chip;
    tnum=chip->num;
    velocity.resize(200);
    relative.resize(200);
    for(int i=0;i<200;i++)
    {
        velocity[i]=0;
        relative[i]=0;
    }
    //delete pp->chip;
    //mainwindow的指针不可以删除，拷贝的是地址
    int h;
    int w;
    if(pp->resolution_status)
    {
        h=1219;
        w=1169;   //surface book设置结果
    }
    else
    {
        h=742;
        w=721;    //1080p设置结果
    }
    qDebug() << h << w;
    length=(h-h%(tnum+1))/(tnum+1);
    hmargin=(w-(tnum-1)*length)/2;
    vmargin=(h-(tnum+1)*length)/2;
    for(int i=0;i<200;i++)
        edge[i]=false;
    //对应输出管道的边
    for(int i=(2*tnum*tnum)-(2*tnum);i<2*(tnum*tnum)-(2*tnum)+5;i++)
        edge[i]=true;

    click_x=-1;
    click_y=-1;
    add=false;
    erase=false;
}

void WorkingArea::mouseMoveEvent(QMouseEvent *event)
{


    x =event->x();
    y =event->y();
    //qDebug() << "x: " << x << " y: " << y << "tnum: " << tnum;
    x=x-hmargin;
    y=y-length-vmargin;   //x为相对整个网格的位置

    update();




}

void WorkingArea::mousePressEvent(QMouseEvent *event)
{

    click_x =event->x();
    click_y =event->y();
    click_x=click_x-hmargin;
    click_y=click_y-length-vmargin;   //x为相对整个网格的位置
    flag=0;
    /*
     * 每一次开始需要将flag重置
     * 去除越界的情况
     */
    if(click_x/length>=tnum||click_x<0)
        {click_x=-1;flag=-1;}
    if(click_y/length>=tnum||click_y<0)
        {click_y=-1;flag=-1;}

    int tem_xi=click_x/length;
    int tem_yi=click_y/length;
    int tem_d_l=click_x-(click_x/length)*length;
    int tem_d_u=click_y-(click_y/length)*length;

    //由上到右的顺序依次为1234,flag
    if(flag==-1)
    {
        qDebug() << "测试：click_x：" << click_x << " click_y: " << click_y << "点击无效";
        return;
    }
    else
    {
    if(tem_d_l>tem_d_u&&tem_d_u<length-tem_d_l)
        {//painter->drawLine(hmargin+tem_xi*length,vmargin+(tem_yi+1)*length,hmargin+(tem_xi+1)*length,vmargin+(tem_yi+1)*length);
            flag=1;
        }
    if(tem_d_l<tem_d_u&&tem_d_u<length-tem_d_l)
        {//painter->drawLine(hmargin+tem_xi*length,vmargin+(tem_yi+1)*length,hmargin+tem_xi*length,vmargin+(tem_yi+2)*length);
            flag=4;
        }
    if(tem_d_l>tem_d_u&&tem_d_u>length-tem_d_l)
        {//painter->drawLine(hmargin+(tem_xi+1)*length,vmargin+(tem_yi+1)*length,hmargin+(tem_xi+1)*length,vmargin+(tem_yi+2)*length);
            flag=2;
        }
    if(tem_d_l<tem_d_u&&tem_d_u>length-tem_d_l)
        {//painter->drawLine(hmargin+tem_xi*length,vmargin+(tem_yi+2)*length,hmargin+(tem_xi+1)*length,vmargin+(tem_yi+2)*length);
            flag=3;
        }
    }


    int order=0;
    switch (flag) {
    case 1:
        order=tnum*tnum-tnum+tem_yi*(tnum-1)+tem_xi;
        break;
    case 2:
        order=(tem_xi+1)*(tnum-1)+tem_yi;
        break;
    case 3:
        order=tnum*tnum-tnum+(tem_yi+1)*(tnum-1)+tem_xi;
        break;

    case 4:
        order=tem_xi*(tnum-1)+tem_yi;
        break;
    case -1:
        return;
        break;
    default:
        break;
    }

    if(flag!=-1&&order<=(2*tnum*tnum)-(2*tnum)-1)
    {
        if(add&&!erase)                    //放到stack中
            {if(edge[order]==false)
                steps.push(order+1000);

                edge[order]=true;
                qDebug() << "序号" << order << "已添加";
            }
        if(!add&erase)
            {
            if(edge[order])
                {

                steps.push(order);
                edge[order]=false;
                qDebug() << "序号" << order << "已删除";

                }
            }
        qDebug() << "当前点击的序号为: " << order << endl;
    }
    else
    {
        qDebug() << "点击错误";

    }
    update();




}

void WorkingArea::paintEvent(QPaintEvent *event)
{
        QStyleOption opt;
        opt.init(this);

        QPainter *painter=new QPainter(this);
       // painter->setPen(Qt::BevelJoin);
       // painter->setPen(Qt::RoundCap);

        style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);  //使自定义的widget有背景颜色
        stylesheet = new QFile(":/style/style_for_workarea.qss", this);
                // 只读方式打开该文件
        stylesheet->open(QFile::ReadOnly);
                // 读取文件全部内容，使用tr()函数将其转换为QString类型
        QString styleSheet = tr(stylesheet->readAll());
                // 为QApplication设置样式表
        this->setStyleSheet(styleSheet);





        //painter->begin(this);
        painter->setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
        painter->setPen(QPen(Qt::lightGray,3,Qt::DotLine,Qt::RoundCap));
        /*
         * 画虚线网格
         */
        for(int i=0;i<tnum;i++)
            painter->drawLine(hmargin+(i)*length,vmargin+length,hmargin+(i)*length,vmargin+length*(tnum));
        for(int i=0;i<tnum;i++)
            painter->drawLine(hmargin,vmargin+length*(i+1),hmargin+(tnum-1)*length,vmargin+length*(i+1));


        /*
         * 行数从0到num-1
         * 画出入口
         */
        painter->setPen(QPen(Qt::black,4,Qt::SolidLine,Qt::RoundCap));
        //painter->setPen(QColor(0,0,0,100));

        int t=2*tnum*tnum-2*tnum;

        int length_for_se=length-5;

        painter->setPen(QPen(QColor(0,20+relative[t]*230,255,170),5,Qt::SolidLine,Qt::RoundCap));

        painter->drawLine(hmargin+(chip->s1)*length,vmargin+10,hmargin+(chip->s1)*length,vmargin+length_for_se);
        painter->setPen(QPen(QColor(0,20+relative[++t]*230,255,170),5,Qt::SolidLine,Qt::RoundCap));
        painter->drawLine(hmargin+(chip->s2)*length,vmargin+10,hmargin+(chip->s2)*length,vmargin+length_for_se);
        painter->setPen(QPen(QColor(0,20+relative[++t]*230,255,170),5,Qt::SolidLine,Qt::RoundCap));
        painter->drawLine(hmargin+(chip->e1)*length,vmargin+length*(tnum)+5,hmargin+(chip->e1)*length,vmargin+length*(tnum+1)+length_for_se);
        painter->setPen(QPen(QColor(0,20+relative[++t]*230,255,170),5,Qt::SolidLine,Qt::RoundCap));
        painter->drawLine(hmargin+(chip->e2)*length,vmargin+length*(tnum)+5,hmargin+(chip->e2)*length,vmargin+length*(tnum+1)+length_for_se);
        painter->setPen(QPen(QColor(0,20+relative[++t]*230,255,170),5,Qt::SolidLine,Qt::RoundCap));
        painter->drawLine(hmargin+(chip->e3)*length,vmargin+length*(tnum)+5,hmargin+(chip->e3)*length,vmargin+length*(tnum+1)+length_for_se);





        for(int i=0;i<=tnum*tnum-tnum-1;i++)
            {
               if(edge[i]==true)
               {
                painter->setPen(QPen(QColor(0,20+relative[i]*230,255,170),5,Qt::SolidLine,Qt::RoundCap));
                int draw_xi=i/(tnum-1);
                int draw_yi=i-(i/(tnum-1))*(tnum-1);
                painter->drawLine(hmargin+draw_xi*length,vmargin+(draw_yi+1)*length,hmargin+draw_xi*length,vmargin+(draw_yi+2)*length);
               }
            }
        for(int i=tnum*tnum-tnum;i<=2*tnum*tnum-2*tnum-1;i++)
            {
                if(edge[i]==true)
                {
                    painter->setPen(QPen(QColor(0,20+relative[i]*230,255,170),5,Qt::SolidLine,Qt::RoundCap));
                    int tem_i=i-(tnum*tnum-tnum);
                    int draw_yi=tem_i/(tnum-1);
                    int draw_xi=tem_i-draw_yi*(tnum-1);
                    //qDebug() << "draw_xi: " << draw_xi << "draw_yi: " << draw_yi << "tem_i" << tem_i;

                    painter->drawLine(hmargin+draw_xi*length,vmargin+(draw_yi+1)*length,hmargin+(draw_xi+1)*length,vmargin+(draw_yi+1)*length);
                }
            }



        painter->setPen(QPen(Qt::darkGray,3,Qt::DashDotDotLine,Qt::RoundCap));
        /*
         * 需要在鼠标跟踪前对于所有的东西进行重新绘制
         * 检验哪些地方有，哪些地方没有
         */
        int tem_xi=x/length;
        int tem_yi=y/length;
        int tem_d_l=x-(x/length)*length;
        int tem_d_u=y-(y/length)*length;
        /*
         * tem_distance_left(x)
         * tem_distance_up(y)
         */

        /*
         * 根据跟踪选择对应的预览的线
         */
        //防止越界
    if(add)
    {
        if(tem_xi>=(tnum-1)||tem_yi>=(tnum-1)||x<0||y<0)
            {
                //return;
            }
        else
        {
        if(tem_d_l>tem_d_u&&tem_d_u<length-tem_d_l)
            {painter->drawLine(hmargin+tem_xi*length,vmargin+(tem_yi+1)*length,hmargin+(tem_xi+1)*length,vmargin+(tem_yi+1)*length);

            }
        if(tem_d_l<tem_d_u&&tem_d_u<length-tem_d_l)
            {painter->drawLine(hmargin+tem_xi*length,vmargin+(tem_yi+1)*length,hmargin+tem_xi*length,vmargin+(tem_yi+2)*length);

            }
            if(tem_d_l>tem_d_u&&tem_d_u>length-tem_d_l)
            {painter->drawLine(hmargin+(tem_xi+1)*length,vmargin+(tem_yi+1)*length,hmargin+(tem_xi+1)*length,vmargin+(tem_yi+2)*length);

            }
        if(tem_d_l<tem_d_u&&tem_d_u>length-tem_d_l)
            painter->drawLine(hmargin+tem_xi*length,vmargin+(tem_yi+2)*length,hmargin+(tem_xi+1)*length,vmargin+(tem_yi+2)*length);
        }
    }
    /*
     * 设置擦除时的笔刷
     */
    if(erase)
    {
        painter->setPen(QPen(Qt::red,3,Qt::DashLine,Qt::RoundCap));
        painter->setOpacity(0.75);
        if(tem_xi>=(tnum-1)||tem_yi>=(tnum-1)||x<0||y<0)
            {
                //return;
            }
        else
        {
        if(tem_d_l>tem_d_u&&tem_d_u<length-tem_d_l)
            {painter->drawLine(hmargin+tem_xi*length,vmargin+(tem_yi+1)*length,hmargin+(tem_xi+1)*length,vmargin+(tem_yi+1)*length);

            }
        if(tem_d_l<tem_d_u&&tem_d_u<length-tem_d_l)
            {painter->drawLine(hmargin+tem_xi*length,vmargin+(tem_yi+1)*length,hmargin+tem_xi*length,vmargin+(tem_yi+2)*length);

            }
        if(tem_d_l>tem_d_u&&tem_d_u>length-tem_d_l)
            {painter->drawLine(hmargin+(tem_xi+1)*length,vmargin+(tem_yi+1)*length,hmargin+(tem_xi+1)*length,vmargin+(tem_yi+2)*length);

            }
        if(tem_d_l<tem_d_u&&tem_d_u>length-tem_d_l)
            painter->drawLine(hmargin+tem_xi*length,vmargin+(tem_yi+2)*length,hmargin+(tem_xi+1)*length,vmargin+(tem_yi+2)*length);

        }
    }
    /*
     * 在erase状态下我们需要换一种样式，比如红色？？
     */



    delete painter;
    delete stylesheet;
   // update();

}






