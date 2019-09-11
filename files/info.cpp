#include "info.h"

Info::Info(QWidget *parent) : QWidget(parent)
{
    layout_in_info=new QVBoxLayout(this);
    info =new QLabel("Xianyu's Project",this);
    info->setAlignment(Qt::AlignCenter);


    QPixmap pixmap(":/image/signature.png");
    QSize picsize(1000,1000);
    QPixmap scaled=pixmap.scaled(picsize,Qt::KeepAspectRatio);
    QLabel* signature=new QLabel(this);
    signature->setPixmap(scaled);
    layout_in_info->addWidget(signature,Qt::AlignCenter);
    layout_in_info->addWidget(info,Qt::AlignCenter);

}
