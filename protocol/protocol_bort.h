#ifndef PROTOCOL_BORT_H
#define PROTOCOL_BORT_H

#include "stdint.h"
#include <QDebug>
#include <QTime>
#include <QTimer>
#include "pc_protocol.h"


class protocolAUV : public QObject
{
    Q_OBJECT
public:
    protocolAUV(QObject * parent = nullptr);
    void start(int dt){
        timer.start(dt);
    }
public:
    void tick();
    void resetValues();
protected:
        QTimer timer;
        void readDataFromPult();
        void writeDataToPult();
    ControlSystem::PC_Protocol *auvProtocol = nullptr;
};


#endif
