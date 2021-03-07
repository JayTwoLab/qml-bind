
#include <QtCore>

#include "cppvalue.h"

CppValue::CppValue(QObject *parent) : QObject(parent)
{
    m_strCppValue = QString("CppValue : %1").arg( rand() );
}

QString CppValue::getStrCppValue()
{
    return m_strCppValue;
}

Q_INVOKABLE QString CppValue::testCalling(QString param) const
{
    QString ret;
    QTime ct = QTime::currentTime();

    ret = QString("[%2:%3:%4] testCalling( %1 )")
            .arg( param )
            .arg( ct.hour() )
            .arg( ct.minute() )
            .arg( ct.second() );

    return ret;
}

