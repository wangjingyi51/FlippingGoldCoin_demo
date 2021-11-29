#ifndef CHOOSESCENCE_H
#define CHOOSESCENCE_H

#include <QMainWindow>
#include <playscence.h>

class ChooseScence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseScence(QWidget *parent = nullptr);
    //重新实现绘图
    void paintEvent(QPaintEvent *);
    //游戏场景
    PlayScence *playscence = NULL;

signals:
    //自定义信号，返回主场景(不需要实现)
    void ChooseScenceBack();
};

#endif // CHOOSESCENCE_H
