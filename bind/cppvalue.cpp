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
    ret = QString("tc: %1, %2").arg( param ).arg( rand() );
    return ret;
}

