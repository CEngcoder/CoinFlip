#include "mypushbutton.h"

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg,QString pressImg)//声明和实现中只能有一个默认参数
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    //加载图片
    QPixmap pix;
    bool  flag = pix.load(normalImg);
    if (!flag)
    {
        qDebug()<<"图片加载失败";
    }

    //设置按钮固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置按钮边框
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置按钮图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

//设置按钮弹跳效果
void MyPushButton::pushbuttonBounce(int dir,int distance,int duration)
{
    //定义动画
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");

    //设置动画的时间
    animation->setDuration(duration);

    //设置动画的起始位置
    if (dir==1)//向下跳
    {
        animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        animation->setEndValue(QRect(this->x(),this->y()+distance,this->width(),this->height()));

    }
    else
    {
        animation->setStartValue(QRect(this->x(),this->y()+distance,this->width(),this->height()));
        animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    }

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //开始动画
    animation->start();
}

//重写鼠标按下事件
void MyPushButton::mousePressEvent(QMouseEvent* e)
{
    if (this->pressImgPath!="")
    {
        //加载图片
        QPixmap pix;
        pix.load(this->pressImgPath);

        //设置按钮固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置按钮边框
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置按钮图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他鼠标按下事件交给父类处理
    return QPushButton::mousePressEvent(e);
}

//重写鼠标释放事件
void MyPushButton::mouseReleaseEvent(QMouseEvent* e)
{
    if (this->pressImgPath!="")
    {
        //加载图片
        QPixmap pix;
        pix.load(this->normalImgPath);

        //设置按钮固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置按钮边框
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置按钮图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    //其他鼠标释放事件交给父类处理
    return QPushButton::mouseReleaseEvent(e);
}
