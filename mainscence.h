#ifndef MAINSCENCE_H
#define MAINSCENCE_H

#include <QMainWindow>
#include <choosescence.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScence; }
QT_END_NAMESPACE

class MainScence : public QMainWindow
{
    Q_OBJECT

public:
    MainScence(QWidget *parent = nullptr);
    ~MainScence();
    //重新实现绘图
    void paintEvent(QPaintEvent *);
    //选择关卡场景对象
    ChooseScence *cs = NULL;


private:
    Ui::MainScence *ui;
};
#endif // MAINSCENCE_H
