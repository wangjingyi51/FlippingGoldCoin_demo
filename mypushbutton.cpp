#include "mypushbutton.h"
#include "QPushButton"
#include "QDebug"
#include "QSize"
#include "QPropertyAnimation"
#include "QMouseEvent"

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}
MyPushButton::MyPushButton(QString normalImg,QString pressImg )
{
    this->normalImgPath = normalImg;
    this->pressTmgPath = pressImg;
    QPixmap pix;
    bool i = pix.load(normalImg);
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

}
void MyPushButton::zoom1()
{
    //参数1：父亲 参数2：动画方式
    QPropertyAnimation *anim=new QPropertyAnimation(this,"geometry");
    //设置动画间隔时间（单位：毫秒）
    anim->setDuration(200);
    //起始位置
    anim->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    anim->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    anim->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    anim->start();
}
void MyPushButton::zoom2()
{
    //参数1：父亲 参数2：动画方式
    QPropertyAnimation *anim=new QPropertyAnimation(this,"geometry");
    //设置动画间隔时间（单位：毫秒）
    anim->setDuration(200);
    //起始位置
    anim->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    anim->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    anim->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    anim->start();
}
void MyPushButton:: mousePressEvent(QMouseEvent *e)
{
    //传入的摁下图片不为空，则切图
    if(this->pressTmgPath!="")
    {
        QPixmap pix;
        bool i = pix.load(this->pressTmgPath);
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
    }
    //上边相当于做了一个事件的拦截，所以剩下事件要让父类处理其他内容
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //传入的摁下图片不为空，则切图
    if(this->pressTmgPath!="")
    {
        QPixmap pix;
        bool i = pix.load(this->normalImgPath);
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
    }
    //上边相当于做了一个事件的拦截，所以剩下事件要让父类处理其他内容
    return QPushButton::mouseReleaseEvent(e);
}
