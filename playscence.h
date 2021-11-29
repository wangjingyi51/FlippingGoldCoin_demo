#ifndef PLAYSCENCE_H
#define PLAYSCENCE_H

#include <QMainWindow>
#include <mycoin.h>

class PlayScence : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScence(QWidget *parent = nullptr);
    PlayScence(int levenum);
    //记录选择第levenum关
    int levenum;
    //重写绘图事件
    void paintEvent(QPaintEvent *);
    //创建二维数组,维护每一个关卡的数据
    int gameArry[4][4];
    //创建维护金币的二维数组，用于对金币的记录
    MyCoin *coinBtn[4][4];
    //是否胜利的标志
    bool isWin;


signals:
    void PlayScenceBack();

};

#endif // PLAYSCENCE_H
