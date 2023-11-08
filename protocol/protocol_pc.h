#ifndef PROTOCOL_PC_H
#define PROTOCOL_PC_H

#include <QDebug>
#include <QTime>
#include <QTimer>
#include "pc_protocol.h"

class protocolPC: public QObject
{
    Q_OBJECT
public:
    protocolPC(QObject * parent = nullptr);
    void start(int dt){
        timer.start(dt);
    }
public:
    void tick();
    void resetValues();
protected:
        QTimer timer;
        void readDataFromAUV();
        void writeDataToAUV();
    Pult::PC_Protocol *pcProtocol = nullptr;
};

#endif // PROTOCOL_PC_H
