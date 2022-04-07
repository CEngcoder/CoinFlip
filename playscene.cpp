#include "playscene.h"

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

//构造函数
PlayScene::PlayScene(int level)
{
    QString str=QString("您选择了第%1关").arg(level);
    //qDebug()<<str;
    this->levelIndex=level;

    //设置窗口大小
    this->setFixedSize(390,570);

    //设置标题
    str = QString("第%1关").arg(level);
    this->setWindowTitle(str.toUtf8().data());

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));


    //////////////////////////初始化胜利标签//////////////////////////////////////////
    QPixmap winpix;
    winpix.load(":/res/LevelCompletedDialogBg.png");
    this->winlabel = new QLabel(this);
    this->winlabel->setGeometry(0,0,winpix.width(),winpix.height());
    this->winlabel->setPixmap(winpix);
    this->winlabel->move(this->width()/2-this->winlabel->width()/2,-this->winlabel->height());
    //////////////////////////////////////////////////////////////////////////////////


    //菜单栏和退出按钮的实现
    QMenuBar* bar = menuBar();//创建菜单栏，这是内部的函数，也可以自己new
    setMenuBar(bar);//将bar固定在当前按钮上
    QMenu* startMenu = new QMenu("开始");//创建开始菜单
    bar->addMenu(startMenu);//将开始菜单添加到菜单栏上
    QAction* quitAction = new QAction("退出");//创建退出功能
    startMenu->addAction(quitAction);//将退出功能添加到开始菜单上
    connect(quitAction,&QAction::triggered,this,[=](){this->close();});

    //音效
    QSound* backSound = new QSound(":/res/BackButtonSound.wav",this);//返回
    QSound* flipSound = new QSound(":/res/ConFlipSound.wav",this);//翻金币

    //创建返回按钮
    MyPushButton* backbtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    //点击返回按钮，翻金币场景发送返回信号
    connect(backbtn,&QPushButton::clicked,this,[=](){
        //播放返回按钮音效
        backSound->play();
        QTimer::singleShot(200,this,[=](){
            emit this->backSignal();
        });
    });

    //显示第几关的label
    QLabel* label = new QLabel(this);
    str = QString("Level:%1").arg(level);
    label->setText(str.toUtf8().data());
    QFont font;
    font.setPointSize(20);
    font.setFamily("华为新魏");
    label->setFont(font);
    label->setGeometry(30,this->height()-50, 140,50);

    //初始化关卡数据
    dataConfig data;
    for (int i=0 ;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            this->gameArray[i][j]=data.mData[this->levelIndex][i][j];
            //qDebug()<<gameArray[i][j];
        }
        //qDebug()<<"";
    }


    //设置金币背景图
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            QLabel* label = new QLabel(this);
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->move(j*50+95,i*50+170);//注意j和i

            //关卡金币银币默认显示
            QString path;
            if (this->gameArray[i][j]==1)//显示金币
            {
                path=":/res/Coin0001.png";
            }
            else//显示银币
            {
                path=":/res/Coin0008.png";
            }
            MyCoin* coin = new MyCoin(path);
            coin->setParent(this);
            coin->move(j*50+97,i*50+172);//注意j和i

            //金币按钮数组初始化
            this->coinbtn[i][j]=coin;

            //初始化金币属性
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];

            //点击按钮触发翻转效果
            connect(coin,&QPushButton::clicked,this,[=](){
                //播放翻金币音效
                flipSound->play();

                ////屏蔽所有硬币解决Bug1////
                this->shieldAllCoin();
                ///////////////////////////

                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;

                //延时翻转周围的硬币，单独封装成一个函数
                QTimer::singleShot(200,this,[=](){
                    this->flipAroundCoin(i,j);

                    /////////////Bug1//////////
                    this->freeshielAllCoin();
                    ///////////////////////////

                    //判断是否胜利并且执行操作
                    this->IsWin();
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

//延时翻转周围的硬币，单独封装成一个函数
void PlayScene::flipAroundCoin(int i,int j)
{
    //翻转右边硬币的条件
    if (i+1<=3)
    {
        this->coinbtn[i+1][j]->changeFlag();
        this->gameArray[i+1][j]=this->gameArray[i+1][j]==0?1:0;
    }
    //翻转左边硬币的条件
    if (i-1>=0)
    {
        this->coinbtn[i-1][j]->changeFlag();
        this->gameArray[i-1][j]=this->gameArray[i-1][j]==0?1:0;
    }
    //翻转上面硬币的条件
    if (j-1>=0)
    {
        this->coinbtn[i][j-1]->changeFlag();
        this->gameArray[i][j-1]=this->gameArray[i][j-1]==0?1:0;
    }
    //翻转下面硬币的条件
    if (j+1<=3)
    {
        this->coinbtn[i][j+1]->changeFlag();
        this->gameArray[i][j+1]=this->gameArray[i][j+1]==0?1:0;
    }
}

//判断是否胜利的函数，并且执行操作
void PlayScene::IsWin()
{
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            if (this->coinbtn[i][j]->flag == false)//只要有一个是银币，返回false
            {
                return;
            }
        }
    }
    //如果走到这里，说明胜利了
    //播放成功音效
    this->successSound->play();
    //qDebug()<<"胜利";
    //将每个硬币的isWin设为真，并设置mycoin类屏蔽鼠标按下事件
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            this->coinbtn[i][j]->isWin=true;
        }
    }

    //创建动画
    QPropertyAnimation* winAn = new QPropertyAnimation(this->winlabel,"geometry");
    //设置时间
    winAn->setDuration(1000);
    //设置开始位置和结束位置
    winAn->setStartValue(QRect(this->winlabel->x(),this->winlabel->y(),this->winlabel->width(),this->winlabel->height()));
    winAn->setEndValue(QRect(this->winlabel->x(),this->winlabel->y()+140,this->winlabel->width(),this->winlabel->height()));
    //设置弹跳效果
    winAn->setEasingCurve(QEasingCurve::OutBounce);
    //开始动画
    winAn->start();
}

///////////////解决Bug1////////////////////
//屏蔽所有硬币
void PlayScene::shieldAllCoin()
{
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            this->coinbtn[i][j]->isWin=true;
        }
    }
}
//解除屏蔽所有银币
void PlayScene::freeshielAllCoin()
{
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            this->coinbtn[i][j]->isWin=false;
        }
    }
}
//////////////////////////////////////////

//////////////////Bug1:翻一个金币时，其他金币能同时翻（不包括周围的金币）/////////////////
