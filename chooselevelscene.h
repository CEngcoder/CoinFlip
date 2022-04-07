#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QLabel>
#include"playscene.h"
#include<QSound>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent*);

    //翻金币场景对象
    PlayScene* pScene = NULL;

signals:
    //选择关卡的返回信号
    void backSignal();//自定义信号不用写实现

};

#endif // CHOOSELEVELSCENE_H
