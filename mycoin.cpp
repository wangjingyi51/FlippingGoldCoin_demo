#include "mycoin.h"
#include "QDebug"
#include "QTimer"

//MyCoin::MyCoin(QWidget *parent) :QPushButton(parent)
//{

//}
MyCoin:: MyCoin(QString btnImg)
{
    QPixmap pix;
    bool i=pix.load(btnImg);
    if(!i)
    {
        qDebug()<<"图片加载失败！";
        return ;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:Opx;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    time1 = new QTimer;
    time2 = new QTimer;
    //监听正面翻转反面的信号
    connect(time1,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        //实现图片的更新
        QString str = QString (":/picture&music/Coin000%1.png").arg(this->min++);
        pix.load(str);
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:Opx;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断翻完后，重置min,停止翻转发送信号
        if(this->min>this->max)
        {
            this->min = 1;
            time1->stop();
        }
    });
    //监听反面翻转成正面的信号
    connect(time2,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        //实现图片的更新
        QString str = QString (":/picture&music/Coin000%1.png").arg(this->max--);
        pix.load(str);
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:Opx;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断翻完后，重置min,停止翻转发送信号
        if(this->min>this->max)
        {
            this->max = 8;
            time2->stop();
        }

    });

}
//金币翻转
void MyCoin::ChangeFlage()
{
    //正面翻转成反面
    if(this->flag==1)
    {
        //开始正面翻转成反面的定时器,每间隔30ms发送一次信号
        time1->start(30);
        this->flag = 0;
    }
    else
    {
        time2->start(30);
        this->flag = 1;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isWin)
    {
        return ;
    }
    else
        QPushButton::mousePressEvent(e);
}
