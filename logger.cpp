#include "logger.h"

Logger::Logger(QObject *parent) : QObject{parent}
{

}

void Logger::logTickGPS(GPS gps)
{
    if (writeLogGPS)
    {
        gpsS = gps;
        QTextStream stream (&fileGPS);
//        stream << gps.gll.lat << ", " << gps.gll.NS << ", " << gps.gll.long_ << ", " << gps.gll.EW << ", " << \
//                  gps.gll.time.toString("hh:mm:ss.z") << ", " << gps.gll.status << ", " << gps.gll.posMode << "\n";
        stream << gps.rms.time.toString("hh:mm:ss.z") << ", " << gps.rms.status << ", " << gps.rms.lat << ", " << gps.rms.NS << ", " << \
                  gps.rms.long_ << ", " << gps.rms.EW << ", " << gps.rms.spd << ", " << gps.rms.cog << ", " <<\
                  gps.rms.date.toString("dd.MM.yy") << ", " << gps.rms.mv << ", " << gps.rms.mvEW << ", " << gps.rms.posMode << ", " << gps.rms.counter <<  "\n";
    }
}

void Logger::logTickIdle(uWave uwave)
{
    if(writeLogIdle)
    {

        QTextStream stream (&fileIdle);
        stream << gpsS.rms.time.toString("hh:mm:ss.z") << ", " << gpsS.rms.lat << ", "  << gpsS.rms.NS << ", " << \
                  gpsS.rms.long_ << ", " << gpsS.rms.EW << ", " <<  gpsS.rms.counter << ", "  << uwave.puwv7.Pressure_mBar << ", " << \
                  uwave.puwv7.Temperature_C << ", " << uwave.puwv7.Depth_m << ", "  << uwave.puwv7.VCC_V << ", "  << uwave.puwv0.errCode << ", " <<\
                  uwave.counterACKIdle << "\n";
    }
}

void Logger::logTickRound(uWave uwave)
{
    if(writelogRoundR)
    {

        QTextStream stream (&fileRound);
        stream << gpsS.rms.time.toString("hh:mm:ss.z") << ", " << gpsS.rms.lat << ", "  << gpsS.rms.NS << ", " << \
                  gpsS.rms.long_ << ", " << gpsS.rms.EW << ", " <<  gpsS.rms.counter << ", "  << uwave.puwv7.Pressure_mBar << ", " << \
                  uwave.puwv7.Temperature_C << ", " << uwave.puwv7.Depth_m << ", "  << uwave.puwv7.VCC_V << ", "  << uwave.puwv0.errCode << ", " <<\
                  uwave.counterACKIdle << ", " << uwave.puwv3.txChID <<", " << uwave.puwv3.propTime << ", " << uwave.puwv3.distance << ", " << uwave.puwv3.MSR << "\n";
    }
}

void Logger::logDirect(uWave uwave)
{
    if(writelogDirect)
    {

        QTextStream stream (&fileDirect);
        stream << gpsS.rms.time.toString("hh:mm:ss.z") << ", " << gpsS.rms.lat << ", "  << gpsS.rms.NS << ", " << \
                  gpsS.rms.long_ << ", " << gpsS.rms.EW << ", " <<  gpsS.rms.counter << ", "  << uwave.puwv7.Pressure_mBar << ", " << \
                  uwave.puwv7.Temperature_C << ", " << uwave.puwv7.Depth_m << ", "  << uwave.puwv7.VCC_V << ", "  << uwave.puwv0.errCode << ", " <<\
                  uwave.puwv3.counter << ", " << uwave.puwv3.txChID <<", " << uwave.puwv3.propTime << ", " << uwave.puwv3.distance << ", " << uwave.puwv3.MSR << ", " << uwave.puwv4.counter <<"\n";
    }
}

void Logger::logStartGPS()
{
    if (writeLogGPS == false)
    {
        QString fileGPSName = QString("logGPS-")+QSysInfo::machineHostName()+QString("-")+QDate::currentDate().toString("yy-MM-dd")+QString("-") \
                +QTime::currentTime().toString("hh-mm-ss")+".txt";
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
//        stream << "lat, NS, long, EW, time, status, posMode\n";
        stream << "time, status, lat, NS, long, EW, spd, cog, date, mv, mvEW, posMode, counter\n";

    }
}

void Logger::logStartIdle()
{
    if (writeLogIdle == false)
    {
        QString fileIdleName =QString("logIdle-")+ QSysInfo::machineHostName()+QString("-")+QDate::currentDate().toString("yy-MM-dd")+QString("-") \
                +QTime::currentTime().toString("hh-mm-ss")+".txt";
        qDebug()<<fileIdleName;
        fileIdle.setFileName(fileIdleName);
        if (fileIdle.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug()<<"fileIdle is opened";
            writeLogIdle = true;
        }
        else
        {
            qDebug()<< fileIdle.errorString() << " " << fileIdle.error();
        }
        QTextStream stream(&fileIdle);
         stream << "time, lat, NS, long, EW, counter, Pressure_mBar, Temperature_C, Depth_m, VCC_V, ErrorCode, counterACK\n";
    }
}

void Logger::logStartRoundR()
{
    if (writelogRoundR == false)
    {
        QString fileRoundName =QString("logRoundR-")+ QSysInfo::machineHostName()+QString("-")+QDate::currentDate().toString("yy-MM-dd")+QString("-") \
                +QTime::currentTime().toString("hh-mm-ss")+".txt";
        qDebug()<<fileRoundName;
        fileRound.setFileName(fileRoundName);
        if (fileRound.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug()<<"fileRound is opened";
            writelogRoundR = true;
        }
        else
        {
            qDebug()<< fileRound.errorString() << " " << fileRound.error();
        }
        QTextStream stream(&fileRound);
         stream << "time, lat, NS, long, EW, counter, Pressure_mBar, Temperature_C, Depth_m, VCC_V, ErrorCode, counterACK, txChID, propTime, distance, MSR\n";
    }
}


void Logger::logStartDirect()
{
    if (writelogDirect == false)
    {
        QString fileDirectName =QString("logDirect-")+ QSysInfo::machineHostName()+QString("-")+QDate::currentDate().toString("yy-MM-dd")+QString("-") \
                +QTime::currentTime().toString("hh-mm-ss")+".txt";
        qDebug()<<fileDirectName;
        fileDirect.setFileName(fileDirectName);
        if (fileDirect.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug()<<"fileDirect is opened";
            writelogDirect = true;
        }
        else
        {
            qDebug()<< fileDirect.errorString() << " " << fileDirect.error();
        }
        QTextStream stream(&fileDirect);
         stream << "time, lat, NS, long, EW, counter, Pressure_mBar, Temperature_C, Depth_m, VCC_V, ErrorCode, counterACK, txChID, propTime, distance, MSR, TIMEOUT_counter\n";
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

void Logger::logStopIdle()
{
    if (writeLogIdle == true)
    {
        writeLogIdle = false;
        fileIdle.close();
        qDebug() << "fileIdle.close";
    }
}

void Logger::logStopRoundR()
{
    if (writelogRoundR == true)
    {
        writelogRoundR = false;
        fileRound.close();
    }
}

void Logger::logStopDirect()
{
    if (writelogDirect == true)
    {
        writelogDirect = false;
        fileDirect.close();
    }
}
