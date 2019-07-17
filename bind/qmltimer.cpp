// qmltimer.cpp

#include "qmltimer.h"

#include <QtGlobal>
#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QDate>
#include <QTime>

QMLTimer::QMLTimer(QObject *parent) : QObject(parent)
{
    objText = nullptr;

    // create and start timer(1 sec. span)
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(processThing()));
    timer->start(1000);
}

void QMLTimer::processThing()
{
    if ( objText != nullptr )
    {
        // set random number string
        objText->setProperty( "text", QVariant(QString("%1").arg(rand())) );
    }
}

