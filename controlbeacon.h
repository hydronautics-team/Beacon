#ifndef CONTROLBEACON_H
#define CONTROLBEACON_H
#include "nmea0183.h"
#include "logger.h"


class ControlBeacon : public QObject
{
    Q_OBJECT
public:
    ControlBeacon(QObject *parent = nullptr);
    NMEA0183 *gps = nullptr;
protected:
    Logger logger;
};

#endif // CONTROLBEACON_H
