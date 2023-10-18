#include <QCoreApplication>
#include "controlbeacon.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

           ControlBeacon cb;

    return a.exec();
}
