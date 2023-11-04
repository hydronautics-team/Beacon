#include "controlbeacon.h"



ControlBeacon::ControlBeacon(QObject *parent)
{
    hydro = new Hydroacoustics("COM3");
    connect(&timerCmd1,&QTimer::timeout,hydro,&Hydroacoustics::sendCmd1);
    connect(&timerCmd2,&QTimer::timeout,hydro,&Hydroacoustics::sendCmd2);
    connect(&timerIdle,&QTimer::timeout,hydro,&Hydroacoustics::modeIdle);
    connect(hydro, &Hydroacoustics::newMessageDetectedACKIdle, &logger, &Logger::logTickIdle);


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
        timerCmd1.start(1000);
    });
    connect(SendCmd1, &QState::exited,this, [this](){ //выходим из состояния SendCmd1 и выключаем таймер
        timerCmd1.stop();
    });
    connect(SendCmd2,&QState::entered,this, [this](){ //входим в состояние SendCmd1 и запускаем таймер
        timerCmd2.start(1000);
    });
    connect(SendCmd2, &QState::exited,this, [this](){ //выходим из состояния SendCmd1 и выключаем таймер
        timerCmd2.stop();
    });
    connect(Idle,&QState::entered,this, [this](){ //входим в состояние SendCmd1 и запускаем таймер
        logger.logStartIdle();
        timerIdle.start(1000);


    });
    connect(SendCmd2, &QState::exited,this, [this](){ //выходим из состояния SendCmd1 и выключаем таймер
        timerIdle.stop();
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

