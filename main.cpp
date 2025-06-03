#include <QCoreApplication>
#include "control.h"
#include "nmea0183.h"
#include <QObject>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Control cb;
    return a.exec();
}
