#include "widget.h"
#include "ui_widget.h"
#include <QObject>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->btnDirect, &QPushButton::clicked, this, &Widget::startDirect);
    connect(ui->btnRoundR, &QPushButton::clicked, this, &Widget::startRoundR);
    connect(ui->btnStop, &QPushButton::clicked, this, &Widget::stop);
//    connect(ui->btnDirect, &QPushButton::clicked, cb, &ControlBeacon::startRoundR);
//    connect(ui->btnRoundR, &QPushButton::clicked, cb, &ControlBeacon::startDirectConnection);
//    connect(ui->btnStop, &QPushButton::clicked, cb, &ControlBeacon::finishExchange);
}




Widget::~Widget()
{
    delete ui;
}

void Widget::update(uWave uwave)
{
    ui->good->setNum(uwave.puwv3.counter);
    ui->notGood->setNum(uwave.puwv4.counter);
}
