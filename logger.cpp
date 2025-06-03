#include "logger.h"

//using namespace NMEA;

Logger::Logger(QObject *parent) : QObject{parent}
{
//    Json_parser js;
//    gpsS = new NMEA::NMEA0183 (js.set.comGPS);
    logStartAll();
    logStartGPS();
}

void Logger::logTickGPS(NMEA::GPS &gps_)
{
    if (writeLogGPS)
    {
        gpsS = gps_;

        if (countGGA != gpsS.gga.count)
        {
            countGGA = gpsS.gga.count;
            updateGPS = true;
        }
        if (countGLL != gpsS.gll.count)
        {
            countGLL = gpsS.gll.count;
            updateGPS = true;
        }
        if (countRMC != gpsS.rmc.count)
        {
            countRMC = gpsS.rmc.count;
            updateGPS = true;
        }
        if (updateGPS)
        {
            QTextStream stream (&fileGPS);
            stream << gpsS.gll.lat << ", " << gpsS.gll.NS << ", " << gpsS.gll.long_ << ", " << gpsS.gll.EW << ", " <<
                      gpsS.gll.time.toString("hh:mm:ss.z") << ", " << gpsS.gll.status << ", " << gpsS.gll.posMode << ", " << gpsS.gll.count << ", ";

            stream << gpsS.rmc.time.toString("hh:mm:ss.z") << ", " << gpsS.rmc.status << ", " << gpsS.rmc.lat << ", " << gpsS.rmc.NS << ", " <<
                      gpsS.rmc.lon << ", " << gpsS.rmc.EW << ", " << gpsS.rmc.speedKnots << ", " << gpsS.rmc.course << ", " <<
                      gpsS.rmc.date.toString("dd.MM.yy") << ", " << gpsS.rmc.magneticVariation << ", " << gpsS.rmc.magneticEW << ", " <<
                      gpsS.rmc.posMode << ", " << gpsS.rmc.count << ", ";

            stream << gpsS.gga.time.toString("hh:mm:ss.z") << ", " << gpsS.gga.latitude << ", " << gpsS.gga.latHemisphere << ", " <<
                      gpsS.gga.longitude << ", " << gpsS.gga.lonHemisphere << ", " << gpsS.gga.quality << ", " << gpsS.gga.satellitesUsed << ", " <<
                      gpsS.gga.hdop << ", " << gpsS.gga.altitude << ", " << gpsS.gga.altitudeUnit << ", " << gpsS.gga.geoidHeight << ", " <<
                      gpsS.gga.geoidUnit << ", " << gpsS.gga.dgpsAge << ", " << gpsS.gga.dgpsStationId << ", " << gpsS.gga.count << "\n";
            updateGPS = false;
        }


    }
}

void Logger::logTickAll(const QByteArray &gps_data)
{
    if (writeLogAll)
    {
        QTextStream stream (&fileAll);
        stream << gps_data << "\n";
    }
}

void Logger::logStartGPS()
{
    if (writeLogGPS == false)
    {
        QString fileGPSName = QString("logGPS-")+QSysInfo::machineHostName()+QString("-")+QDate::currentDate().toString("yy-MM-dd")+QString("-") \
                +QTime::currentTime().toString("hh-mm-ss")+".csv";
        qDebug()<<fileGPSName;
        fileGPS.setFileName(fileGPSName);

        if (fileGPS.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug()<<"fileGPS is opened";
            writeLogGPS = true;
        }
        else
        {
            qDebug()<< fileGPS.errorString() << " " << fileGPS.error();
        }
        QTextStream stream(&fileGPS);
        stream << "gll.lat, gll.NS, gll.long, gll.EW, gll.time, gll.status, gll.posMode, gll.count, ";
        stream << "rmc.time, rmc.status, rmc.lat, rmc.NS, rmc.lon, rmc.EW, rmc.speedKnots, rmc.course, rmc.date, rmc.magneticVariation, rmc.magneticEW, rmc.posMode, rmc.count, ";
        stream << "gga.time, gga.latitude, gga.latHemisphere, gga.longitude, gga.lonHemisphere, gga.quality, gga.satellitesUsed, gga.hdop, gga.altitude, gga.altitudeUnit, gga.geoidHeight, gga.geoidUnit, gga.dgpsAge, gga.dgpsStationId, gga.count\n";
    }
}

void Logger::logStartAll()
{
    if (writeLogAll == false)
    {
        QString fileAllName = QString("logAll-")+QSysInfo::machineHostName()+QString("-")+QDate::currentDate().toString("yy-MM-dd")+QString("-") \
                +QTime::currentTime().toString("hh-mm-ss")+".csv";
        qDebug()<<fileAllName;
        fileAll.setFileName(fileAllName);

        if (fileAll.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug()<<"fileAll is opened";
            writeLogAll = true;
        }
        else
        {
            qDebug()<< fileAll.errorString() << " " << fileAll.error();
        }
    }
}

void Logger::logStopGPS()
{
    if (writeLogGPS == true)
    {
        writeLogGPS = false;
        fileGPS.close();
    }
}

void Logger::logStopAll()
{
    if (writeLogAll == true)
    {
        writeLogAll = false;
        fileAll.close();
        qDebug() << "fileAll.close";
    }
}
