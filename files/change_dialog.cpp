#include "change_dialog.h"
#include "ui_change_dialog.h"
#include <QMessageBox>

Change_dialog::Change_dialog(int num,int i1,int i2,int o1,int o2,int o3,QWidget *parent) :
    QDialog(parent),s1(i1),s2(i2),e1(o1),e2(o2),e3(o3),num(num),
    ui(new Ui::Change_dialog)
{
    //this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    ui->dial_s1->setSliderPosition(s1);
    ui->dial_s2->setSliderPosition(s2);
    ui->dial_e1->setSliderPosition(e1);
    ui->dial_e2->setSliderPosition(e2);
    ui->dial_e3->setSliderPosition(e3);
    ui->lcd_e1->display(e1);
    ui->lcd_e2->display(e2);
    ui->lcd_e3->display(e3);
    ui->lcd_s1->display(s1);
    ui->lcd_s2->display(s2);


    connect(ui->dial_e1,SIGNAL(valueChanged(int)),ui->lcd_e1,SLOT(display(int)));
    connect(ui->dial_e2,SIGNAL(valueChanged(int)),ui->lcd_e2,SLOT(display(int)));
    connect(ui->dial_e3,SIGNAL(valueChanged(int)),ui->lcd_e3,SLOT(display(int)));
    connect(ui->dial_s1,SIGNAL(valueChanged(int)),ui->lcd_s1,SLOT(display(int)));
    connect(ui->dial_s2,SIGNAL(valueChanged(int)),ui->lcd_s2,SLOT(display(int)));

    connect(ui->dial_s1,SIGNAL(valueChanged(int)),this,SLOT(check_valid()));
    connect(ui->dial_s2,SIGNAL(valueChanged(int)),this,SLOT(check_valid()));
    connect(ui->dial_e1,SIGNAL(valueChanged(int)),this,SLOT(check_valid()));
    connect(ui->dial_e2,SIGNAL(valueChanged(int)),this,SLOT(check_valid()));
    connect(ui->dial_e3,SIGNAL(valueChanged(int)),this,SLOT(check_valid()));


    this->show();
}

Change_dialog::~Change_dialog()
{
    delete ui;
}

void Change_dialog::on_cancel_clicked()
{
    this->close();
}
void Change_dialog::on_confirm_clicked()
{
    if(check_valid())
    {
        s1=ui->dial_s1->value();
        s2=ui->dial_s2->value();
        e1=ui->dial_e1->value();
        e2=ui->dial_e2->value();
        e3=ui->dial_e3->value();
        emit changed_data(s1,s2,e1,e2,e3);
        this->close();
    }
    else
    {
        QMessageBox msgbox;
        msgbox.setText("请检查你的输入！！！");
        msgbox.exec();
    }
}

bool Change_dialog::check_valid()
{
    if((ui->dial_s1->value())==(ui->dial_s2->value())||ui->dial_s1->value()>=num||ui->dial_s2->value()>=num)
        {
              ui->lcd_s1->setStyleSheet("QWidget{color:red}");
              ui->lcd_s2->setStyleSheet("QWidget{color:red}");
              return false;
         }
    else
        {
            ui->lcd_s1->setStyleSheet("QWidget{color:black}");
            ui->lcd_s2->setStyleSheet("QWidget{color:black}");

        }
    if(ui->dial_e1->value()==ui->dial_e2->value()||ui->dial_e1->value()==ui->dial_e3->value()||ui->dial_e2->value()==ui->dial_e3->value()||ui->dial_e1->value()>=num||ui->dial_e2->value()>=num||ui->dial_e3->value()>=num)
    {
        ui->lcd_e1->setStyleSheet("QWidget{color:red}");
        ui->lcd_e2->setStyleSheet("QWidget{color:red}");
        ui->lcd_e3->setStyleSheet("QWidget{color:red}");

        return false;
    }
    else
        {
        ui->lcd_e1->setStyleSheet("QWidget{color:black}");
        ui->lcd_e2->setStyleSheet("QWidget{color:black}");
        ui->lcd_e3->setStyleSheet("QWidget{color:black}");
        }
    return true;
}


