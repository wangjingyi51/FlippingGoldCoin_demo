#include "playscence.h"
#include "QDebug"
#include "QMenuBar"
#include "QPainter"
#include "mypushbutton.h"
#include "QTimer"
#include "QLabel"
#include "QString"
#include "QFont"
#include "mycoin.h"
#include "dataconfig.h"
#include "QPropertyAnimation"
#include "QMediaPlayer"

//PlayScence::PlayScence(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScence::PlayScence(int levenum)
{
    qDebug()<<"选择的是第"<<levenum<<"关";
    this->levenum = levenum;

    //配置游戏场景的信息
    this->setFixedSize(420,758);
    this->setWindowTitle("翻金币游戏");
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
    //点击返回按钮，回到选择关卡场景（使用自定义信号槽）
    connect(backbtn,&MyPushButton::clicked,[=](){
        //场景跳转延迟0.5s
        QTimer::singleShot(500,this,[=]()
        {
            emit this->PlayScenceBack();
        });
    });
    //显示当前关卡数
    //显示按钮关卡文本可以使用QLabel,会具有更好的显示效果
    //显示按钮关卡文本可以使用QLabel,会具有更好的显示效果
    QLabel *label = new QLabel;
    label->setParent(this);

    //设置字体（有问题）
    QFont font;
    font.setPointSize(20);
    label->setFixedSize(100,100);
   QString str = QString("Leavel:%1").arg(this->levenum);
    label->setFont(font);
    label->setText(str);
    label->move(10,this->height()-100);
//    //设置文字对齐:水平居中
//    label->setAlignment(Qt::AlignCenter);

    //初始化每个关卡的二维数组
    dataConfig config;
    for (int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArry[i][j] = config.mData[this->levenum][i][j];
        }
    }

    //胜利图片的显示
    QLabel *winlabel = new QLabel;
    QPixmap tmpix;
    tmpix.load(":/picture&music/LevelCompletedDialogBg.png");
    winlabel->setParent(this);
    winlabel->setPixmap(tmpix);
    winlabel->setGeometry(0,0,tmpix.width(),tmpix.height());
    winlabel->move(90,-tmpix.height());


    //显示金币背景图案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //绘制背景图片
            QPixmap pix= QPixmap(":/picture&music/BoardNode.png");
            QLabel *label = new QLabel;
            label->setParent(this);
            label->setPixmap(pix);
            label->setGeometry(0,0,pix.width(),pix.height());
            label->move(107+i*50,250+j*50);

            //创建金币
            QString str;
            if(this->gameArry[i][j]==1)
            {
                str=":/picture&music/Coin0001.png";
            }
            else {
                str=":/picture&music/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(109+i*50,254+j*50);
            //给金币赋值
            coin->posX = i;
            coin->posY = j;
            coin->isWin = false;
            coin->flag = gameArry[i][j]==1;
            //将金币放入金币二维数组，便于记录与维护
            this->coinBtn[i][j]=coin;
            //金币翻转
            connect(coin,&QPushButton::clicked,[=]()
            {
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        //防止瞬间点击其他出现误触，等到周围按钮全部翻转完毕再还原
                        this->coinBtn[i][j]->isWin=true;
                    }
                }
                coin->ChangeFlage();
                //翻转之后维护数组
                this->gameArry[i][j]=this->gameArry[i][j]==0?1:0;
                //金币周围实现翻转,且具有延时效果,且翻转一次就要判断一次，如果胜利判断写在翻转之外，判断设胜利的就是上一次翻转储存的结果
                QTimer::singleShot(300,[=]()
                {
                    //右侧金币翻转
                if(coin->posX+1<=3)
                {
                    coinBtn[coin->posX+1][coin->posY]->ChangeFlage();
                    this->gameArry[coin->posX+1][coin->posY]=this->gameArry[coin->posX+1][coin->posY]==0?1:0;

                }
                    //左侧金币翻转
                if(coin->posX-1>=0)
                {
                    coinBtn[coin->posX-1][coin->posY]->ChangeFlage();
                    this->gameArry[coin->posX-1][coin->posY]=this->gameArry[coin->posX-1][coin->posY]==0?1:0;
                }
                    //上侧金币翻转
                if(coin->posY-1>=0)
                {
                    coinBtn[coin->posX][coin->posY-1]->ChangeFlage();
                    this->gameArry[coin->posX][coin->posY-1]=this->gameArry[coin->posX][coin->posY-1]==0?1:0;
                }
                    //下侧金币翻转
                if(coin->posY+1<=3)
                {
                    coinBtn[coin->posX][coin->posY+1]->ChangeFlage();
                     this->gameArry[coin->posX][coin->posY+1]=this->gameArry[coin->posX][coin->posY+1]==0?1:0;
                }
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        //防止瞬间点击其他出现误触，等到周围按钮全部翻转完毕再还原
                        this->coinBtn[i][j]->isWin=false;
                    }
                }
                //判断是否胜利
                this->isWin = true;
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        //如果有一个是反面，就算失败
                        if(coinBtn[i][j]->flag==false)
                        {
                            this->isWin = false;
                            break;
                        }
                    }
                }
                if(this->isWin == true)
                {
                    //将所有按钮胜利标志改为true
                    for(int h=0;h<4;h++)
                    {
                        for(int t=0;t<4;t++)
                        {
                                coinBtn[h][t]->isWin = true;
                        }
                    }
                    //显示胜利后图片
                    QPropertyAnimation * animation = new QPropertyAnimation(winlabel, "geometry");
                    //设置时间间隔
                    animation->setDuration(1000);
                    //设置动画开始位置与结束位置
                    animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                    animation->setEndValue(QRect(winlabel->x(),winlabel->y()+114,winlabel->width(),winlabel->height()));
                    //设置跳动方式
                    animation->setEasingCurve(QEasingCurve::OutBounce);
                    //开始播放
                    animation->start();
                    QMediaPlayer *player = new QMediaPlayer(this);//设置背景音乐
                    player->setMedia(QUrl("qrc:/picture&music/victory.mp3"));
                    player->setVolume(50);//音量
                    player->play();
                }
                });

            });
        }
    }
}
void PlayScence::paintEvent(QPaintEvent *)
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
