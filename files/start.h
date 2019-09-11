#ifndef START_H
#define START_H
#include <QFile>
#include <QWidget>
#include <QPushButton>

/*
 * class Start继承于QWidget
 * 作为一个界面在这里定义
 */
class QSignalMapper;
class Start : public QWidget
{
    Q_OBJECT
private:
    QFile *buttonstyle;

    QPushButton *but1;
    QPushButton *but2;
    QPushButton *but3;
    QPushButton *but4;
    QPushButton *change_resolution;
public:
    friend class MainWindow;
    QSignalMapper* SignalMapper;
    explicit Start(QWidget *parent = nullptr);
    ~Start();


signals:
    void signal_resolution();
public slots:
    void send_signal();
};

#endif // START_H
