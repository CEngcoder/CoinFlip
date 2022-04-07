#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QDebug>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);

    //构造函数
    MyCoin(QString btnImg);

    //金币的属性，坐标和正反面
    int posX;
    int posY;
    bool flag;

    //改变金币正反面标志
    void changeFlag();
    //金币翻银币的定时器
    QTimer* timer1;
    //银币翻金币的定时器
    QTimer* timer2;
    //图片的名称
    int min=1;int max=8;

    //判断动画是否正在执行
    bool isaAimation = false;

    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent* e);

    //是否胜利
    bool isWin=false;

signals:

};

#endif // MYCOIN_H
