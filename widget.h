#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "controlbeacon.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
protected:
//    ControlBeacon *cb = nullptr;
signals:
    void startDirect();
    void startRoundR();
    void stop();

};

#endif // WIDGET_H
