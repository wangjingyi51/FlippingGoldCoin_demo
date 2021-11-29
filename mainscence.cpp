#include "mainscence.h"
#include "ui_mainscence.h"
#include "QMediaPlayer"
#include "QPainter"
#include "QPixmap"
#include "QDebug"
#include "mypushbutton.h"
#include "choosescence.h"
#include "QTimer"
#include "choosescence.h"

MainScence::MainScence(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScence)
{
    ui->setupUi(this);
    //配置主窗口
    this->setFixedSize(420,758);
    this->setWindowTitle("翻金币");
    this->setWindowIcon(QPixmap(":/picture&music/Coin0001.png"));
    //配置主场景
    //退出按钮
    connect(ui->actionquit,&QAction::triggered,[=]()
    {
        this->close();
    });
    //开始按钮
    MyPushButton * startbtn = new MyPushButton(":/picture&music/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);
    //创建选择关卡场景的对象
    cs = new ChooseScence(this);
    //监听选择关卡的返回信号
    connect(cs,&ChooseScence::ChooseScenceBack,[=]()
    {
        QTimer::singleShot(500,this,[=]()
        {
            cs->hide();
            this->show();
        });
    });
    connect(startbtn,&QPushButton::clicked,[=]()
    {
        qDebug()<<"点击了开始";
        //点击特效
        startbtn->zoom1();
        startbtn->zoom2();
        //场景跳转延迟0.5s
        QTimer::singleShot(500,this,[=]()
        {
            //进入选择关卡场景中
            this->hide();
            cs->show();
        });

    });
    QMediaPlayer *player = new QMediaPlayer(this);//设置背景音乐
    //D:/BaiduNetdiskDownload/picture&music/classicbackgroundmusic.mp3
    player->setMedia(QUrl("qrc:/picture&music/classicbackgroundmusic.mp3"));
    player->setVolume(50);//音量
//    connect(ui->pushButton,&QPushButton::clicked,[=](){
           player->play();
//        });//开始播放，也可以用按钮的方式，这里用的是菜单栏中的action
//    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
//          player->stop();
//        });//停止播放


}

MainScence::~MainScence()
{
    delete ui;
}
void MainScence::paintEvent(QPaintEvent *)
{
    //绘图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/picture&music/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //背景图上加图标
    pix.load(":/picture&music/Title.png");
    //缩小图片
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

