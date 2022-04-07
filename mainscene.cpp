#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置固定大小
    this->setFixedSize(390,570);

    //设置标题
    this->setWindowTitle("翻金币");

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //退出功能
    connect(ui->actionquit,&QAction::triggered,this,[=](){
        this->close();
    });

    //设置开始按钮
    MyPushButton* startbtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width()/2-startbtn->width()/2,this->height()*0.7);

    //选择关卡对象界面初始化
    this->choosescene = new ChooseLevelScene(this);

    //开始按钮音效
    QSound* startSound = new QSound(":/res/TapButtonSound.wav",this);

    //开始按钮
    connect(startbtn,&QPushButton::clicked,this,[=](){
        //播放开始音效
        //startSound->setLoops(10);//循环播放，无限循环设为-1
        startSound->play();

        //开始按钮特效
        //qDebug()<<"特效";
        startbtn->pushbuttonBounce(1,20,100);//向下跳
        startbtn->pushbuttonBounce(2,20,100);//向上跳  //有点bug，一直连续点会向下去

        //延时0.2s进入选择关卡界面
        QTimer::singleShot(200,this,[=](){
            //隐藏主界面，显示选择关卡
            this->hide();
            ///////////优化场景位置/////////////////
            choosescene->setGeometry(this->geometry());
            ///////////////////////////////////////
            choosescene->show();
        });
    });

    //监听选择关卡的返回信号  连接过程：返回按钮点击->返回信号->主窗口做出反应
    connect(choosescene,&ChooseLevelScene::backSignal,this,[=](){
        //主场景显示，选择关卡窗口隐藏
        choosescene->hide();
        ///////////优化场景位置/////////////////
        this->setGeometry(choosescene->geometry());
        ///////////////////////////////////////
        this->show();
    });



}

//重写绘图事件
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}

MainScene::~MainScene()
{
    delete ui;
}

