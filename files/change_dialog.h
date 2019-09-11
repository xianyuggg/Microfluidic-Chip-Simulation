#ifndef CHANGE_DIALOG_H
#define CHANGE_DIALOG_H

#include <QDialog>

namespace Ui {
class Change_dialog;
}

class Change_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Change_dialog(int num,int i1,int i2,int o1,int o2,int o3,QWidget *parent = 0);
    ~Change_dialog();

private slots:
    void on_cancel_clicked();
    void on_confirm_clicked();
    bool check_valid();
signals:
    void changed_data(int,int,int,int,int);
private:
    int num;
    int s1;
    int s2;
    int e1;
    int e2;
    int e3;
    Ui::Change_dialog *ui;
};

#endif // CHANGE_DIALOG_H
