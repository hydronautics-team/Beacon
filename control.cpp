#include "control.h"

Control::Control(QObject *parent) : QObject(parent)
{
    Json_parser js;
    qDebug() << "js.set.comHydro: " << js.set.comHydro;
    hydro = new Hydroacoustics(js.set.comHydro);
    gps = new NMEA::NMEA0183 (js.set.comGPS);
}

void Control::readConfig(QString pwd)
{

}

void Control::main_tick()
{

}
