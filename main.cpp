#include "mainwinserver.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QThread::currentThreadId();
    MainWinServer w;
    w.show();
    //w.hide();
    return a.exec();
}
