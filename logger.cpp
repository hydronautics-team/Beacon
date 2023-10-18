#include "logger.h"

Logger::Logger(QObject *parent) : QObject{parent}
{

}

void Logger::logTick(GPS gps)
{
    if (writeLog)
    {
        QTextStream stream (&file);
//        stream << gps.gll.lat << ", " << gps.gll.NS << ", " << gps.gll.long_ << ", " << gps.gll.EW << ", " << \
//                  gps.gll.time.toString("hh:mm:ss.z") << ", " << gps.gll.status << ", " << gps.gll.posMode << "\n";
        stream << gps.rms.time.toString("hh:mm:ss.z") << ", " << gps.rms.status << ", " << gps.rms.lat << ", " << gps.rms.NS << ", " << \
                  gps.rms.long_ << ", " << gps.rms.EW << ", " << gps.rms.spd << ", " << gps.rms.cog << ", " <<\
                  gps.rms.date.toString("dd.MM.yy") << ", " << gps.rms.mv << ", " << gps.rms.mvEW << ", " << gps.rms.posMode << ", " << gps.rms.counter <<  "\n";
    }
}

void Logger::logStart()
{
    if (writeLog == false)
    {
        QString fileName = "Beacon"+QString(" ")+QDate::currentDate().toString("yy-MM-dd")+QString(" ") \
                +QTime::currentTime().toString("hh-mm-ss")+".txt";
        qDebug()<<fileName;
        file.setFileName(fileName);

        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug()<<"file is opened";
            writeLog = true;
        }
        else
        {
            qDebug()<< file.errorString() << " " << file.error();
        }
        QTextStream stream(&file);
//        stream << "lat, NS, long, EW, time, status, posMode\n";
        stream << "time, status, lat, NS, long, EW, spd, cog, date, mv, mvEW, posMode, counter\n";

    }
}


void Logger::logStop()
{
    if (writeLog == true)
    {
        writeLog = false;
        file.close();
    }
}
