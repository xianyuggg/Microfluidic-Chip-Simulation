#ifndef ADVANCED_DIALOG_H
#define ADVANCED_DIALOG_H
#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "QFile"

class Advanced_dialog : public QDialog
{
    Q_OBJECT
    public:
        explicit Advanced_dialog(int num1,QWidget *parent=0);
        ~Advanced_dialog();
    QPushButton* cancel;
    QPushButton* start;

    private:
        QLineEdit* e_num;
        QLabel   * l_num;
        int num;
        int s_c1;
        int s_c2;
        int e_c1;
        int e_c2;
        int e_c3;


        QLineEdit* e_s_1;        //editor for starting point;
        QLineEdit* e_s_2;
        QLineEdit* e_e_1;
        QLineEdit* e_e_2;
        QLineEdit* e_e_3;
        QLabel   * l_s;          //label for startng
        QLabel   * l_e;
        QLabel   * l_lw;
        QLineEdit* e_l;
        QLineEdit* e_w;

        QFile* style;

      private slots:
        bool check_num_valid();
        bool check_s_valid();
        bool check_e_valid();

        void start_draw();

       signals:
        void data(int,int,int,int,int,int);
        //num,s1,s2,e1,e2,e3







};

#endif // ADVANCED_DIALOG_H
