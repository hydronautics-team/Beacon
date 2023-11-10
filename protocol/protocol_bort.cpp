#include <QTimer>
#include <QDebug>
#include "protocol_bort.h"

protocolAUV:: protocolAUV (QObject *parent)
{
    auvProtocol = new ControlSystem::PC_Protocol();
    auvProtocol->startExchange();
    connect(&timer, &QTimer::timeout, this, &protocolAUV::tick);
    timer.start(10);
//    auvProtocol->stopExhange();
}


void protocolAUV:: tick()
{
    readDataFromPult();
//    readDataFromSensors();
//    regulators();
//    BFS_DRK(X[101][0], X[102][0], X[103][0] , X[104][0], X[105][0], X[106][0]);
//    writeDataToVMA();
    writeDataToPult();
    qDebug() << "таймер работает";
}

void protocolAUV::readDataFromPult ()
{
   auvProtocol->rec_data.mode_data.direct;


   //когда появится обмен с системой питания внести переключатели

   }

void protocolAUV::writeDataToPult ()
{
    auvProtocol->send_data.depth;
}
