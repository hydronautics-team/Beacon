#include <QCoreApplication>
#include "controlbeacon.h"
#include <QObject>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ControlBeacon cb;
//    qDebug() << "error";

    return a.exec();
}
