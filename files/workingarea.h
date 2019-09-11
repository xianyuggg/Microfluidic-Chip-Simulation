#ifndef WORKINGAREA_H
#define WORKINGAREA_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QFile>
#include <chip.h>
#include <Stack>
#include <vector>

/*
 *
 */
class WorkingArea : public QWidget
{
    Q_OBJECT
public:
    explicit WorkingArea(QWidget *parent = nullptr);

    Chip* chip;
    int tnum;      //the num of the grid
    int length;    //the length of the pipe
    int hmargin;   //the length of the horizontal margin
    int vmargin;

    int x;
    int y;
    //此处x和y为相对网格的距离
    int click_x;
    int click_y;
    int flag;     //表示上下左右的flag

    bool add;
    bool erase;


    QFile* stylesheet;
    bool edge[200];   //储存边的对应情况

    std::vector<double> velocity;
    std::vector<double> relative;
    /*
     * chip的数据
     * struct edge；
    struct node；
    vector< vector<double> >rect(200);//存储方程组(行列式)
    bool *fr; //深度搜索时判断边是否遍历过
    int n,EDGESUM,NODESUM;  //记录网格边长

    //函数功能：确定管道中某条管道的长度
    //参数含义：x，管道的编号；leng，管道的长度
    **************************************bool setedgelength(int x, double leng)

     */

    std::stack<int> steps;
    /*
     * steps总是三位数或者是两位数，那么我们用一个规则来判定前一步是添加还是去除
     * 添加1000代表添加，不添加1000代表删除
     */

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    //void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);
signals:
    void move_complete();
public slots:
    void add_is_checked(bool check);
    void erase_is_checked(bool check);
    void ctrl_c();               //全部东西都删除
    void ctrl_z();
    void get_velocity(vector<double>& temv);
    void moveData();

};

#endif // WORKINGAREA_H
