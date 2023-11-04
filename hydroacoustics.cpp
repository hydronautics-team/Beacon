#include "hydroacoustics.h"
#include <QDebug>

Hydroacoustics::Hydroacoustics(QString portName, int baudRate,
                               QObject *parent) : QObject(parent)
{
    ha.setBaudRate(baudRate);
    ha.setPortName(portName);
    ha.setDataBits(QSerialPort::Data8);
    ha.setStopBits(QSerialPort::OneStop);
    ha.setParity(QSerialPort::NoParity);
    ha.setFlowControl(QSerialPort::NoFlowControl);
    ha.open(QIODevice::ReadWrite);


}



void Hydroacoustics::readData()
{
    ha.waitForReadyRead(2000);
    ha_buffer.append(ha.readAll());
    qDebug() << ha_buffer;
    parseBuffer();
}

int Hydroacoustics::crc(QByteArray tmp)
{
    int crc_ = 0;
    for (int i = 0; i <= tmp.size(); i++)
        crc_^=tmp[i];
    return crc_;
}

int Hydroacoustics::crc_real(qint8 crc_in)
{
    int crc_real = 0;
    if ((int (ha_buffer[crc_in+1]))>57)
    crc_real += ((int (ha_buffer[crc_in+1]))-'0'-7)*16;
    else crc_real += ((int (ha_buffer[crc_in+1]))-'0')*16;
    if ((int (ha_buffer[crc_in+2]))>57)
    crc_real += ((int (ha_buffer[crc_in+2]))-'0') -7;
    else crc_real += ((int (ha_buffer[crc_in+2]))-'0');
    return crc_real;
}

void Hydroacoustics::sendCmd1()
{
    if (ha.isOpen())
    settings();
    else
    {
        qDebug() << "порт не открыт: " << ha.error();
        ha.close();
        ha.open(QIODevice::ReadWrite);
    }

    if ((uwave.puwv0.errCode == 0) and (uwave.puwv0.cmdID ==6))
    {
        qDebug()<<"cmd1 sended!";
        emit cmd1Received();
    }
}

void Hydroacoustics::settings()
{
    char PUWV6[24] = "$PUWV6,1,1,1,1,1,1*32\r\n"; // включаем передачу сообщений о состоянии модема
    qDebug()  <<"bytes written :"<< ha.write(PUWV6, 24);
    ha.waitForBytesWritten();
    readData();
}

void Hydroacoustics::sendCmd2()
{
    if (ha.isOpen())
    {
        qDebug() << "snsn";
     //   char PUWV6[18] = "$PUWVF,1,1,0*5E\r\n"; // Настройки пакетного режима 0 адрес
        char PUWV6[18] = "$PUWVF,1,1,5*5B\r\n"; // Настройки пакетного режима 5 адрес
        ha.write(PUWV6, 18);
        ha.waitForBytesWritten();
        readData();
    }
    else
    {
        qDebug() << "порт не открыт: " << ha.error();
        ha.close();
        ha.open(QIODevice::ReadWrite);
    }
    if (uwave.puwve.isPTMode == 1)
    {
        qDebug()<<"cmd2 sended!";
        emit initCmd2Done();

    }
}

void Hydroacoustics::modeIdle()
{
    if (ha.waitForReadyRead(10))
    {
        readData();
    }
    else
    {
        qDebug() << "Данных для чтения нет";
        emit newMessageDetectedACKIdle(uwave);
    }
}

void Hydroacoustics::parseBuffer()
{
    int count = ha_buffer.count(36);
    qDebug() << count;
    while (count !=0)
    {
        count = count-1;
        qint8 index = ha_buffer.indexOf(36); //поиск индекса $
        if (index == -1)
        {
            // Не найдено сообщение
            qDebug() << "Нет сообщения в буфере";
            return;
        }
        qint8 crc_in = ha_buffer.indexOf(42);
        uint end = crc_in + 5; //последний символ посылки
        QByteArray title = ha_buffer.mid (index+1, 5);
        if (title == "PUWV0")
        {
            QByteArray msg = ha_buffer.mid(index+1, crc_in-1);
            if (crc_real(crc_in) == crc(msg))
            {
                parsePUWV0(msg);
                ha_buffer.remove(0, end);
            }
            else
            {
                qDebug () << "PUWV0 crc не верна";
                ha_buffer.remove(0, end);
            }
        }
        if (title == "PUWVE")
        {
            QByteArray msg = ha_buffer.mid(index+1, crc_in-1);
            if (crc_real(crc_in) == crc(msg))
            {
                parsePUWVE(msg);
                ha_buffer.remove(0, end);
            }
            else
            {
                qDebug () << "PUWVE crc не верна";
                ha_buffer.remove(0, end);
            }
        }
        if (title == "PUWV7")
        {
            QByteArray msg = ha_buffer.mid(index+1, crc_in-1);
            if (crc_real(crc_in) == crc(msg))
            {
                parsePUWV7(msg);
                ha_buffer.remove(0, end);
            }
            else
            {
                qDebug () << "PUWV7 crc не верна";
                ha_buffer.remove(0, end);
            }
        }
    }
}

void Hydroacoustics::parsePUWV0(QByteArray msg)
{
    int index =msg.indexOf(44);//ищем первую запятую, перед ней идет не интересный заголовок
    msg.remove(0, index+1); // удаляем заголовок
    index =msg.indexOf(44);//ищем запятую
    uwave.puwv0.cmdID = atoi(msg.mid(0, 1));
    qDebug() << "puwv0.cmdID: "<< uwave.puwv0.cmdID;
    msg.remove(0, index+1);
    index =msg.indexOf(42);//ищем звездочку *
    uwave.puwv0.errCode = atoi(msg.mid(0, 1));
    qDebug() << "puwv0.errCode: "<< uwave.puwv0.errCode;
    msg.remove(0, index+1);
}

void Hydroacoustics::parsePUWVE(QByteArray msg)
{
    qDebug() << msg;
    int index =msg.indexOf(44);//ищем первую запятую, перед ней идет не интересный заголовок
    msg.remove(0, index+1); // удаляем заголовок
    index =msg.indexOf(44);//ищем запятую
    uwave.puwve.isPTMode = atoi(msg.mid(0, 1));
    qDebug() << "puwve.isPTMode: "<< uwave.puwve.isPTMode;
    msg.remove(0, index+1);
    index =msg.indexOf(42);//ищем звездочку *
    uwave.puwve.ptLocalAddress = atoi(msg.mid(0, 1));
    qDebug() << "puwve.ptLocalAddress: "<< uwave.puwve.ptLocalAddress;
    msg.remove(0, index+1);
}

void Hydroacoustics::parsePUWV7(QByteArray msg)
{
    qDebug() << msg;
    int index =msg.indexOf(44);//ищем первую запятую, перед ней идет не интересный заголовок
    msg.remove(0, index+1); // удаляем заголовок
    index =msg.indexOf(44);//ищем запятую
    uwave.puwv7.Pressure_mBar = atof(msg.mid(0, index));
    qDebug() << "puwv7.Pressure_mBar: " << uwave.puwv7.Pressure_mBar;
    msg.remove(0, index+1);
    qDebug() << msg;
    index =msg.indexOf(44);//ищем запятую
    uwave.puwv7.Temperature_C = atof(msg.mid(0, index));
    qDebug() << "puwv7.Temperature_C: " << uwave.puwv7.Temperature_C;
    msg.remove(0, index+1);
    qDebug() << msg;
    index =msg.indexOf(44);//ищем запятую
    uwave.puwv7.Depth_m = atof(msg.mid(0, index));
    qDebug() << "puwv7.Depth_m: " << uwave.puwv7.Depth_m;
    msg.remove(0, index+1);
    qDebug() << msg;
    index =msg.indexOf(44);//ищем запятую
    uwave.puwv7.VCC_V = atof(msg.mid(0, index));
    qDebug() << "puwv7.VCC_V: " << uwave.puwv7.VCC_V;
    msg.remove(0, index+1);
}


