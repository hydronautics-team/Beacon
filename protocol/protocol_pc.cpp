#include "protocol_pc.h"
#include <QTimer>
#include <QDebug>

const QString ConfigFile = "protocols.conf";
const QString agent = "pult";

protocolPC::protocolPC (QObject *parent)
{
    pcProtocol = new Pult::PC_Protocol();
    pcProtocol->startExchange();
    connect(&timer, &QTimer::timeout, this, &protocolPC::tick);
    timer.start(10);
}

void protocolPC:: tick()
{
    readDataFromAUV();
    writeDataToAUV();
    qDebug() << "AUV работает";
}

void protocolPC:: readDataFromAUV()
{

}

void protocolPC:: writeDataToAUV()
{

}
