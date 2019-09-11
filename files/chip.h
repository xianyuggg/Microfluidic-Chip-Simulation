#ifndef CHIP_H
#define CHIP_H

#include <QObject>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>  
#include <math.h>
using namespace std;
#define NAX 0.000000001

class Chip: public QObject
{
    Q_OBJECT
    private:


        void init();
        /*
         * 以下数据来源于计算程序
         */

        struct node
        {          
            vector<int> elist;//点所连接的边，按照顺时针的顺序存储下来
        
        }nodes[200];
        int n,EDGESUM,NODESUM;  //记录网格边长
        bool fr[200]; //深度搜索时判断边是否遍历过


        vector< vector<double> >rect;//存储方程组(行列式)

        void addrect(vector<double> &tmp);
        int getdirline(int x, int y, int dir);
        bool existdir(int x, int y, int dir);
        void recursionline(int x, int y, int dir, vector<double> &tmp,int end);
        bool recursionrect(int x, int y, vector<double> &tmp,int end);
        void findline(int x, int y,int t);
        void findrect(int x1);
        void initrect(double v1,double v2);
        int min (int a, int b);
        double GreatestCommonDivisor(double a, double b);
        double LeastCommonMultiple (double a, double b);
        void getans();
        vector<double> caluconspeed(int num, vector<double>&length, int i1, int i2, int o1, int o2, int o3,double v1,double v2);

signals:
        void success();
        void change_success();
        void velocity(vector<double>& v);
public slots:
        void getAnswer();
        void setedgelength(int x, double leng);
        void change_data(int i1,int i2,int o1,int o2,int o3);

public:
        struct edge
        {
            double v; //流速
            double leng; //管道长度
            int n1,n2; //边所连接的两个节点，默认从n1流向n2
        }edges[200];
        int num;
        int s1;
        int s2;
        int e1;
        int e2;
        int e3;
        double answer1;
        double answer2;
        double answer3;
        explicit Chip(int a,int b,int c,int d,int e,int f);
};

#endif // CHIP_H
