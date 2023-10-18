#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include "nmea0183.h"


class Logger : public QObject
{
    Q_OBJECT
public:
    Logger(QObject *parent = nullptr);
public slots:
    void logTick(GPS gps);
    void logStart();
    void logStop();
protected:
    bool writeLog = false;
    QFile file;
};

#endif // LOGGER_H
