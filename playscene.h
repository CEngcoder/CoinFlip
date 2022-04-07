#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>


class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    //构造函数
    PlayScene(int level);

    //关卡数
    int levelIndex;

    //重写绘图事件
    void paintEvent(QPaintEvent*);

    //关卡数据
    int gameArray[4][4];

    //用一个二维数组维护住16个金币按钮
    MyCoin* coinbtn[4][4];

    //延时翻转周围的硬币，单独封装成一个函数
    void flipAroundCoin(int i,int j);//ij表示中心的硬币

    //判断是否胜利并且执行操作
    void IsWin();

    //胜利标签
    QLabel* winlabel;

    //成功音效，因为我判断成功是在成员函数中
    QSound* successSound = new QSound(":/res/LevelWinSound.wav",this);//成功

    ////////解决Bug1///////
    //屏蔽所有硬币
    void shieldAllCoin();
    //解除屏蔽所有银币
    void freeshielAllCoin();
    ///////////////////////

signals:
    //返回上个界面信号
    void backSignal();

};

#endif // PLAYSCENE_H
