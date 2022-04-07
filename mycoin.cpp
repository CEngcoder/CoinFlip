#include "mycoin.h"

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

//构造函数
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool flag = pix.load(btnImg);
    if (!flag)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化两个定时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听金币翻银币计时器的信号
    connect(timer1,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString path = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(path);
        //不要再设置按钮的大小的边框了
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if (this->min > 8)
        {
            timer1->stop();
            this->isaAimation=false;
            this->min=1;
        }
    });

    //监听银币翻金币计时器的信号
    connect(timer2,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString path = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(path);
        //不要再设置按钮的大小的边框了
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if (this->max < 1)
        {
            timer2->stop();
            this->isaAimation=false;
            this->max=8;
        }
    });
}

//改变金币正反面标志
void MyCoin::changeFlag()
{
    if (this->flag==true)
    {
        timer1->start(30);
        this->isaAimation=true;
        this->flag=false;
    }
    else
    {
        timer2->start(30);
        this->isaAimation=true;
        this->flag=true;
    }
}

//重写鼠标按下事件，防止鼠标点击过快使动画不连续
void MyCoin::mousePressEvent(QMouseEvent* e)
{
    if (this->isaAimation==true || this->isWin==true)
    {
        return;
    }
    return QPushButton::mousePressEvent(e);
}
