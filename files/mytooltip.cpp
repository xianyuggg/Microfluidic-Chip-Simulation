#include "mytooltip.h"
#include <qgraphicseffect.h>
#include <QPainter>
#include <QLayout>
Mytooltip::Mytooltip(QWidget* parent):QWidget(parent)
{

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    auto shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setOffset(0, 0);
    shadowEffect->setColor(Qt::gray);
    shadowEffect->setBlurRadius(SHADOW_WIDTH);
    this->setGraphicsEffect(shadowEffect);

    this->setFixedSize(400, 400);




}
void Mytooltip::setCenterWidget(QWidget* widget)
{
        QHBoxLayout* hMainLayout = new QHBoxLayout(this);
        hMainLayout->addWidget(widget);
        hMainLayout->setSpacing(0);
        hMainLayout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH + TRIANGLE_HEIGHT, SHADOW_WIDTH, SHADOW_WIDTH);
}
// 设置小三角显示的起始位置;
void Mytooltip::setStartPos(int startX)
{
    m_startX = startX;
}

void Mytooltip::setTriangleInfo(int width, int height)
{
    m_triangleWidth = width;
    m_triangleHeight = height;
}

void Mytooltip::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255));

    // 小三角区域;
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startX, m_triangleHeight + SHADOW_WIDTH);
    trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, SHADOW_WIDTH);
    trianglePolygon << QPoint(m_startX + m_triangleWidth, m_triangleHeight + SHADOW_WIDTH);

    QPainterPath drawPath;
    drawPath.addRoundedRect(QRect(SHADOW_WIDTH, m_triangleHeight + SHADOW_WIDTH,\
                                width() - SHADOW_WIDTH * 2, height() - SHADOW_WIDTH * 2 - m_triangleHeight),\
                                BORDER_RADIUS, BORDER_RADIUS);
    // Rect + Triangle;
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}
