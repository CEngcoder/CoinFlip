#include "chooselevelscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口大小
    this->setFixedSize(390,570);

    //设置标题
    this->setWindowTitle("选择关卡");

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //菜单栏和退出按钮的实现
    QMenuBar* bar = menuBar();//创建菜单栏，这是内部的函数，也可以自己new
    setMenuBar(bar);//将bar固定在当前按钮上
    QMenu* startMenu = new QMenu("开始");//创建开始菜单
    bar->addMenu(startMenu);//将开始菜单添加到菜单栏上
    QAction* quitAction = new QAction("退出");//创建退出功能
    startMenu->addAction(quitAction);//将退出功能添加到开始菜单上
    connect(quitAction,&QAction::triggered,this,[=](){
       this->close();//这个close是关闭哪个界面？？？？？？？？？，应该是主界面
    });

    //音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);//返回按钮音效
    QSound* chooseSound = new QSound(":/res/TapButtonSound.wav",this);//选择按钮音效

    //创建返回按钮
    MyPushButton* backbtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    //返回按钮功能，点击返回按钮，发出返回信号，主窗口监听返回信号，因为主窗口无法直接监听按钮的点击信号
    connect(backbtn,&QPushButton::clicked,this,[=](){
        //播放返回按钮音效
        backSound->play();
        //qDebug()<<"返回按钮";
        QTimer::singleShot(200,this,[=](){
            emit this->backSignal();
        });
    });

    //选择关卡按钮的实现
    for (int i = 0;i < 20;i++)
    {
        //创建按钮
        MyPushButton* btn = new MyPushButton(":/res/LevelIcon.png");
        btn->setParent(this);
        btn->move(i%4*75+52,i/4*75+145);

        //设置标签
        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(btn->width(),btn->height());
        label->setText(QString::number(i+1));
        label->move(i%4*75+52,i/4*75+145);
        label->setAlignment(Qt::AlignCenter);

        //设置鼠标穿透试件，51号，或者把label的父亲设为btn，而且不要移动标签了
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        //设置按钮连接
        connect(btn,&QPushButton::clicked,this,[=](){
            //播放选择按钮音效
            chooseSound->play();
            //选择按钮特效
            btn->pushbuttonBounce(1,10,100);
            btn->pushbuttonBounce(2,10,100);
            //QString str=QString("您选择了第%1关").arg(i);
            //qDebug()<<str;
            pScene=new PlayScene(i+1);//点击了按钮才创建pScene
            QTimer::singleShot(200,this,[=](){
                this->hide();
                ////////////优化场景位置///////////
                pScene->setGeometry(this->geometry());
                ///////////////////////////////////
                pScene->show();
            });
            //选择关卡窗口监听翻金币场景发送的返回信号，这一段要写在connect里面，因为翻金币场景是在connect里面创建的
            connect(pScene,&PlayScene::backSignal,this,[=](){
                pScene->hide();
                ////////////优化场景位置///////////
                this->setGeometry(pScene->geometry());
                ///////////////////////////////////
                this->show();
                delete pScene;
                pScene=NULL;
            });

        });
    }

}


//重写绘图事件
void ChooseLevelScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);//画家对象

    //背景图片
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");

    //绘制背景图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //标题图片
    pix.load(":/res/Title.png");

    //绘制标题图片
    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,30,pix);

}
