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
   auvProtocol->rec_data.controlData.yaw;
   auvProtocol->rec_data.controlData.pitch;
   auvProtocol->rec_data.controlData.roll;
   auvProtocol->rec_data.controlData.march;
   auvProtocol->rec_data.controlData.depth;
   auvProtocol->rec_data.controlData.lag;

   auvProtocol->rec_data.cSMode;

   auvProtocol->rec_data.controlContoursFlags.yaw;
   auvProtocol->rec_data.controlContoursFlags.pitch;
   auvProtocol->rec_data.controlContoursFlags.roll;
   auvProtocol->rec_data.controlContoursFlags.march;
   auvProtocol->rec_data.controlContoursFlags.depth;
   auvProtocol->rec_data.controlContoursFlags.lag;

   //когда появится обмен с системой питания внести переключатели

   auvProtocol->rec_data.checksum;
   }

void protocolAUV::writeDataToPult ()
{
    auvProtocol->send_data.headerSwap.senderID;
    auvProtocol->send_data.headerSwap.receiverID;
    auvProtocol->send_data.headerSwap.msgSize;

    auvProtocol->send_data.auvData.modeReal;
    auvProtocol->send_data.auvData.controlReal.yaw;
    auvProtocol->send_data.auvData.controlReal.pitch;
    auvProtocol->send_data.auvData.controlReal.roll;
    auvProtocol->send_data.auvData.controlReal.march;
    auvProtocol->send_data.auvData.controlReal.depth;
    auvProtocol->send_data.auvData.controlReal.lag;
    auvProtocol->send_data.auvData.modeAUV_Real;
    auvProtocol->send_data.auvData.ControlDataReal.yaw;
    auvProtocol->send_data.auvData.ControlDataReal.pitch;
    auvProtocol->send_data.auvData.ControlDataReal.roll;
    auvProtocol->send_data.auvData.ControlDataReal.march;
    auvProtocol->send_data.auvData.ControlDataReal.depth;
    auvProtocol->send_data.auvData.ControlDataReal.lag;
    auvProtocol->send_data.auvData.signalVMA_real;

    auvProtocol->send_data.dataAH127C.yaw;
    auvProtocol->send_data.dataAH127C.pitch;
    auvProtocol->send_data.dataAH127C.roll;
    auvProtocol->send_data.dataAH127C.X_accel;
    auvProtocol->send_data.dataAH127C.Y_accel;
    auvProtocol->send_data.dataAH127C.Z_accel;
    auvProtocol->send_data.dataAH127C.X_rate;
    auvProtocol->send_data.dataAH127C.Y_rate;
    auvProtocol->send_data.dataAH127C.Z_rate;
    auvProtocol->send_data.dataAH127C.X_magn;
    auvProtocol->send_data.dataAH127C.Y_magn;
    auvProtocol->send_data.dataAH127C.Z_magn;
    auvProtocol->send_data.dataAH127C.quat[0];
    auvProtocol->send_data.dataAH127C.quat[1];
    auvProtocol->send_data.dataAH127C.quat[2];
    auvProtocol->send_data.dataAH127C.quat[3];
}
