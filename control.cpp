#include "control.h"

Control::Control(QObject *parent) : QObject(parent)
{
    Json_parser js;
//    hydro = new Hydroacoustics(js.set.comHydro);
    qDebug() << "js.set.comGPS" << js.set.comGPS;

    if (js.set.comGPS.isEmpty()) {
            qCritical() << "GPS port name is empty!";
            return;
        }
    gps = new NMEA::NMEA0183(js.set.comGPS);
    logger = new Logger();
    connect(gps, &NMEA::NMEA0183::updateAll, logger, &Logger::logTickAll);
    connect(gps, &NMEA::NMEA0183::updateGPS, logger, &Logger::logTickGPS);
}

void Control::readConfig(QString pwd)
{

}

void Control::main_tick()
{

}
