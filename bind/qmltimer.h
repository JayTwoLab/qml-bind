#ifndef QMLTIMER_H
#define QMLTIMER_H

#include <QObject>
#include <QTimer>

class QMLTimer : public QObject
{
    Q_OBJECT
public:
    explicit QMLTimer(QObject *parent = nullptr);
    QTimer* timer;
    QObject* objText;
signals:

public slots:
    void processThing();

};

#endif // QMLTIMER_H
