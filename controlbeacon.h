#ifndef CONTROLBEACON_H
#define CONTROLBEACON_H
#include "nmea0183.h"
#include "logger.h"

#include <QStateMachine>
#include <QState>
#include <QTimer>
#include "hydroacoustics.h"

enum class  State : qint8 {
    InitState,
    Idle,
    RoundR,
    DirectConnection
};

static QMap<State,QString> statesMap = {
    {State::InitState,"InitState"},
    {State::Idle, "Idle"}
};


class ControlBeacon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_state READ state WRITE setState)
    Q_PROPERTY(QString m_subState READ subState WRITE setSubState)
signals:
    void initDone();
    void startRoundR();
    void finishExchange();
    void startDirectConnection();
    void initCmd2Done();
    void initCmd3Done();
public slots:
    void tick();
    void initStateSlot();

public:
    ControlBeacon(QObject *parent = nullptr);
    NMEA0183 *gps = nullptr;
    QString state(){
        return m_state;
    }
    QString subState(){
        return m_subState;
    }
protected:
    void setState(QString state){
        m_state = state;
        m_stateCode = statesMap.key(m_state);
        qDebug()<<"new state is :"<<m_state;
    }
    void setSubState(QString subState){
        m_subState = subState;
        qDebug()<<"new subState"<<m_subState;
    }

    Hydroacoustics *hydro = nullptr;
    Logger logger;
    QState *InitState = nullptr, *Idle = nullptr, *RoundR = nullptr, *DirectConnection = nullptr;
    QState *SendCmd1 = nullptr, *SendCmd2 = nullptr, *SendCmd3 = nullptr;
    QStateMachine machine;
    QString m_state, m_subState;
    QTimer timer;
    QTimer timerCmd1;
    QTimer timerCmd2;
    QTimer timerIdle;
    int dt = 100;
    State m_stateCode;
};

#endif // CONTROLBEACON_H
