#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include "nmea0183.h"
#include "hydroacoustics.h"
#include "json_parser.h"

class Logger : public QObject
{
    Q_OBJECT
public:
    Logger(QObject *parent = nullptr);
    NMEA::GPS gpsS;

    quint16 countGLL = 0;
    quint16 countRMC = 0;
    quint16 countGGA = 0;
public slots:
    void logTickGPS(NMEA::GPS &gps_);
    void logTickAll(const QByteArray &gps_data);
    void logStartGPS();
    void logStopGPS();
    void logStartAll();
    void logStopAll();
protected:
    bool writeLogGPS = false;
    bool writeLogAll = false;
    bool updateGPS = false;
    QFile fileGPS;
    QFile fileAll;
};

#endif // LOGGER_H
