#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //自定义封装按钮，重载mypushbutton函数，参数一为图片路径，参数二为判断按钮是否需要有点击的效果（即需要前后显示不同的图片），具有默认值
    MyPushButton(QString normalImg,QString pressImg ="");
    QString normalImgPath;  //图片路径
    QString pressTmgPath;   //按下按钮后显示图片的路径
    //弹跳特效函数
    void zoom1();   //向下跳
    void zoom2();   //向上跳
    //重写按钮按下与释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


signals:

};

#endif // MYPUSHBUTTON_H
