#include "controlbeacon.h"


ControlBeacon::ControlBeacon(QObject *parent)
{
    gps = new NMEA0183 ("COM9");
    logger.logStart();
    QObject::connect(gps, &NMEA0183::newMessageDetected,
                     &logger, &Logger::logTick);
}
