#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QFile>

/*
 * info扮演一个演示界面
 */
class Info : public QWidget
{
    Q_OBJECT
public:
    explicit Info(QWidget *parent = nullptr);
private:
    QVBoxLayout *layout_in_info;
    QLabel *info;
signals:

public slots:
};

#endif // INFO_H
