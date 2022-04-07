#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include<QPropertyAnimation>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数
    MyPushButton(QString normalImg,QString pressImg="");

    QString normalImgPath="";
    QString pressImgPath="";

    //设置按钮弹跳效果
    //第一个参数为弹跳的方向，1为往下跳，其他为往上跳，第二个为弹跳距离，第三个为时间间隔
    void pushbuttonBounce(int dir,int distance,int duration);

    //重写鼠标按下和鼠标释放事件
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);



signals:

};

#endif // MYPUSHBUTTON_H
