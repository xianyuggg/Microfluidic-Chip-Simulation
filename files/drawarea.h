#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QLineEdit>
#include <QFile>
#include <QLayout>
#include <chip.h>
#include <QDebug>
#include <workingarea.h>
#include <stack>
#include <QPainter>
#include <QPaintEvent>

#include <QFile>
#include <change_dialog.h>
#include <mytooltip.h>
class DrawArea : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *overall;
    QHBoxLayout *first;
    QHBoxLayout *second;
    QVBoxLayout *rightcorner;

    QPushButton *clear;
    QPushButton *undo;
    QSpacerItem *spaceItem_first;

    QLineEdit *edit1;      //在空的时候显示默认值
    QLineEdit *edit2;

    QPushButton *caculate;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    WorkingArea *working_area;

    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent* event);
    QFile* file;

    Change_dialog* change_dialog;


public:
    Mytooltip* tooltip;
    QLabel *help;
    QPushButton *add;
    QPushButton *erase;
    QPushButton *change_io;
    explicit DrawArea(QWidget *parent = nullptr);
    //~DrawArea();

signals:

public slots:
    void showAnswer();
    void get_data_from_edit();
    void change_line();


};

#endif // DRAWAREA_H
