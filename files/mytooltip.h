#ifndef MYTOOLTIP_H
#define MYTOOLTIP_H
#include <QLabel>
#define SHADOW_WIDTH 15                 // 窗口阴影宽度;
#define TRIANGLE_WIDTH 15               // 小三角的宽度;
#define TRIANGLE_HEIGHT 10              // 小三角的高度;
#define BORDER_RADIUS 20                // 窗口边角的弧度;
class Mytooltip : public QWidget
{
    Q_OBJECT
public:

    Mytooltip(QWidget* parent);
    // 设置小三角起始位置;
       void setStartPos(int startX);

       // 设置小三角宽和高;
       void setTriangleInfo(int width, int height);

       // 设置中间区域widget;
       void setCenterWidget(QWidget* widget);


protected:
    void paintEvent(QPaintEvent *event);

private:
    int m_startX;
    int m_triangleWidth;
    int m_triangleHeight;


};

#endif // MYTOOLTIP_H
