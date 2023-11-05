#include "controlbeacon.h"



ControlBeacon::ControlBeacon(QObject *parent)
{
    hydro = new Hydroacoustics("COM8");
    connect(&timerCmd1,&QTimer::timeout,hydro,&Hydroacoustics::sendCmd1);
    connect(&timerCmd2,&QTimer::timeout,hydro,&Hydroacoustics::sendCmd2);
    connect(&timerIdle,&QTimer::timeout,hydro,&Hydroacoustics::modeIdle);
//    connect(this, &ControlBeacon::startDirectConnection, hydro, &Hydroacoustics::modeDirect);
    connect(&timerDirect,&QTimer::timeout, hydro, &Hydroacoustics::modeDirect);
//    connect(this,&ControlBeacon::startRoundR,hydro,&Hydroacoustics::modeRound);
    connect(&timerRound,&QTimer::timeout, hydro, &Hydroacoustics::modeRound);
    connect(hydro, &Hydroacoustics::updateData, &logger, &Logger::logTickIdle);
    connect(hydro, &Hydroacoustics::updateData, &logger, &Logger::logDirect);
    connect(hydro, &Hydroacoustics::updateData, &logger, &Logger::logTickRound);
    connect(hydro, &Hydroacoustics::updateData, this, &ControlBeacon::update);



    InitState = new QState();
    Idle = new QState();
    RoundR = new QState();
    DirectConnection = new QState();

    SendCmd1 = new QState(InitState); //состояние внутри InitState
    SendCmd2 = new QState(InitState);

    InitState->setInitialState(SendCmd1);//первое состоние, в котором будет InitState

//    InitState->addTransition(this, &ControlBeacon::initDone, Idle); //переход в Idle по сигналу initDone
    Idle->addTransition(this, &ControlBeacon::startRoundR, RoundR);
    Idle->addTransition(this, &ControlBeacon::startDirectConnection, DirectConnection);
    RoundR->addTransition(this, &ControlBeacon::finishExchange, Idle);
    DirectConnection->addTransition(this,&ControlBeacon::finishExchange,Idle);

    SendCmd1->addTransition(hydro, &Hydroacoustics::cmd1Received,SendCmd2);
    SendCmd2->addTransition(hydro, &Hydroacoustics::initCmd2Done,Idle);

    InitState->assignProperty(this,"m_state",statesMap.value(State::InitState));
    Idle->assignProperty(this,"m_state", "Idle");
    RoundR->assignProperty(this,"m_state","RoundR");
    DirectConnection->assignProperty(this, "m_state","DirectConnection");

    SendCmd1->assignProperty(this,"m_subState","SendCmd1");
    SendCmd2->assignProperty(this,"m_subState","SendCmd2");


    connect(InitState,&QState::entered,this, &ControlBeacon::initStateSlot); //при входе в InitState вызывается initStateSlot
    connect(SendCmd1,&QState::entered,this, [this](){ //входим в состояние SendCmd1 и запускаем таймер
        timerCmd1.start(2000);
    });
    connect(SendCmd1, &QState::exited,this, [this](){ //выходим из состояния SendCmd1 и выключаем таймер
        timerCmd1.stop();
        hydro->stopCounter();
    });
    connect(SendCmd2,&QState::entered,this, [this](){ //входим в состояние SendCmd1 и запускаем таймер
        timerCmd2.start(2000);
    });
    connect(SendCmd2, &QState::exited,this, [this](){ //выходим из состояния SendCmd1 и выключаем таймер
        timerCmd2.stop();
        hydro->stopCounter();
    });
    connect(Idle,&QState::entered,this, [this](){ //входим в состояние SendCmd1 и запускаем таймер
        logger.logStartIdle();
    });
    connect(Idle, &QState::exited,this, [this](){ //выходим из состояния SendCmd1 и выключаем таймер
        logger.logStopIdle();
        hydro->stopCounter();
    });
    connect(DirectConnection,&QState::entered,this, [this](){ //входим в состояние SendCmd1 и запускаем таймер
        logger.logStartDirect();
        timerDirect.start(2000);
    });
    connect(DirectConnection, &QState::exited,this, [this](){ //выходим из состояния SendCmd1 и выключаем таймер
        logger.logStopDirect();
        hydro->stopCounter();
        timerDirect.stop();
    });
    connect(RoundR,&QState::entered,this, [this](){ //входим в состояние SendCmd1 и запускаем таймер
        logger.logStartRoundR();
//        hydro->timerRound.start(2000);
        timerRound.start(3000);
    });
    connect(RoundR, &QState::exited,this, [this](){ //выходим из состояния SendCmd1 и выключаем таймер
        logger.logStopRoundR();
        hydro->stopCounter();
//        hydro->timerRound.stop();
        timerRound.stop();
    });

    machine.addState(InitState);
    machine.addState(Idle);
    machine.addState(RoundR);
    machine.addState(DirectConnection);
    machine.setInitialState(InitState);
    machine.start();


//    connect(InitState, &QState::entered, this, [this](){
//        qDebug()<<"Init state entred";
//        emit initDone();
//    });


    connect(&timer, &QTimer::timeout,this,&ControlBeacon::tick);
    timer.start(dt);

}


void ControlBeacon::tick()
{
    if (m_state == statesMap.value(State::Idle)){

    }
    else if (m_state == "InitState"){

    }
    else if (m_state == "RoundR") {
//    qDebug () <<"RoundR";
    }
    else if (m_state == "DirectConnection"){

    }
}

void ControlBeacon::initStateSlot()
{
    gps = new NMEA0183 ("COM12");
    connect(gps, &NMEA0183::newMessageDetected,
                     &logger, &Logger::logTickGPS);
    logger.logStartGPS();
}

void ControlBeacon::slotStartDirect()
{
    emit startDirectConnection();
}

void ControlBeacon::slotStartRound()
{
    emit startRoundR();
}

void ControlBeacon::slotStop()
{
    emit finishExchange();
}

void ControlBeacon::update(uWave uwave)
{
    emit updateUpdate(uwave);
}


