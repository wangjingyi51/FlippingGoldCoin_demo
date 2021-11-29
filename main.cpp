#include "mainscence.h"
#include "dataconfig.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScence w;
    w.show();
    return a.exec();
}
