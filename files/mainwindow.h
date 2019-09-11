#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "QSignalMapper"
#include "start.h"
#include "info.h"
#include "drawarea.h"
class QFile;
class Advanced_dialog;
namespace Ui {
class MainWindow;
}
class Chip;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool resolution_status;
    //0 for 1080
    //1 for surface
    explicit MainWindow(QWidget *parent = 0);
    Chip* chip;
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actioninformation_triggered();
    void show_advanced_dialog(int num);
    void init_chip(int,int,int,int,int,int);
    void show_draw_area();


    void change_resolution();
    //接受来自start的信号，然后改变分辨率
private:
    Start* start;
    Info* info;
    DrawArea* draw_area;
    Advanced_dialog *advanced;            //

    QFile *buttonstyle;
    Ui::MainWindow *ui;





};

#endif // MAINWINDOW_H
