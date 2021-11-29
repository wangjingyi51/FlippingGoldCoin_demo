#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);    //参数代表传入的是金币路劲还是银币路径
    //金币x坐标
    int posX;
    //金币y坐标
    int posY;
    //金币的正反
    bool flag;
    //金币反转
    void ChangeFlage();
    QTimer *time1;   //正面翻反面的定时器
    QTimer *time2;   //反面翻正面的定时器
    int min = 1;
    int max = 8;
    //胜利标志(用于胜利后不可以在点击金币)
    bool isWin = false;
    //重写鼠标事件
    void mousePressEvent(QMouseEvent *e);
signals:

};

#endif // MYCOIN_H
