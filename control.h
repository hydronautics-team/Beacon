#ifndef CONTROL_H
#define CONTROL_H

#include "nmea0183.h"
#include "logger.h"
#include <QTimer>
#include <QDebug>
#include "hydroacoustics.h"
#include "json_parser.h"

#include <QObject>
#include <QTimer>

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = nullptr);
    void readConfig(QString pwd);
    void main_tick();

    NMEA::NMEA0183 *gps = nullptr;
    Hydroacoustics *hydro = nullptr;
    Logger logger;

signals:

};

#endif // CONTROL_H
