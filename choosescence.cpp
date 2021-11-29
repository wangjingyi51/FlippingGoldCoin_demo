#include "choosescence.h"
#include "QMenuBar"
#include "QPainter"
#include "mypushbutton.h"
#include "QTimer"
#include "QLabel"
#include "QDebug"
#include "playscence.h"

ChooseScence::ChooseScence(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景的信息
    this->setFixedSize(420,758);
    this->setWindowTitle("关卡选择");
    this->setWindowIcon(QPixmap(":/picture&music/Coin0001.png"));
    //创建菜单栏
    QMenuBar *bar = new QMenuBar;
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu *startmenu = bar->addMenu("开始");
    //创建退出的菜单项
    QAction *quitmenu = startmenu->addAction("退出");
    //点击退出，退出游戏
    connect(quitmenu,&QAction::triggered,[=]()
    {
        this->close();
    });
    //返回按钮,点击返回按钮进行点击按钮图片切换，呈现点击效果
    MyPushButton *backbtn =new MyPushButton(":/picture&music/BackButton.png",":/picture&music/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());
    //点击返回按钮，回到主场景（使用自定义信号槽）
    connect(backbtn,&MyPushButton::clicked,[=](){
        //场景跳转延迟0.5s
        QTimer::singleShot(500,this,[=]()
        {
            emit this->ChooseScenceBack();
        });
    });
    //创建选择关卡的按钮:使用一个变量构建二维矩阵
    for(int i=0;i<20;i++)
    {
        MyPushButton *levelbtn = new MyPushButton(":/picture&music/LevelIcon.png");
        levelbtn->setParent(this);
        levelbtn->move(35+i%4*100,140+i/4*100);
        //监听每个按钮的点击事件
        connect(levelbtn,&MyPushButton::clicked,[=]()
        {
            qDebug()<<"选择关卡";
            this->hide();
            playscence = new PlayScence(i+1);
            playscence->show();
            //监听游戏场景的返回信号(一定要嵌套在监听按钮点击事件中，因为playscence->show()一直在运行)
            connect(playscence,&PlayScence::PlayScenceBack,[=]()
            {
                    //当返回选择关卡场景时，这个游戏场景不再需要
                    delete playscence;
                    this->show();
                    playscence = NULL;
            });
        });
        //显示按钮关卡文本可以使用QLabel,会具有更好的显示效果
        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(levelbtn->width(),levelbtn->height());
        label->setText(QString::number(i+1));
        label->move(35+i%4*100,140+i/4*100);
        //设置文字对齐:水平居中
        label->setAlignment(Qt::AlignCenter);
        //设置鼠标穿透（即当我点击时，点击到的是label，并没有点击到levelbtn,要对label做一个置于底层的操作）
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}
void ChooseScence::paintEvent(QPaintEvent *)
{
    //配置关卡选择场景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/picture&music/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加上标题
    pix.load(":/picture&music/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
