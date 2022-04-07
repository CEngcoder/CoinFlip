#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include<QPainter>
#include"mypushbutton.h"
#include"chooselevelscene.h"
#include"QTimer"
#include<QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //选择关卡窗口对象
    ChooseLevelScene* choosescene = NULL;

private:
    Ui::MainScene *ui;

};
#endif // MAINSCENE_H
