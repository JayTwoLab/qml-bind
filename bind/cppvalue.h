#ifndef CPPVALUE_H
#define CPPVALUE_H

#include <QtGlobal>
#include <QObject>

class CppValue : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString strCppValue READ getStrCppValue )
public:
    explicit CppValue(QObject *parent = nullptr);
    QString getStrCppValue();
    Q_INVOKABLE QString testCalling(QString param) const;
protected:
    QString m_strCppValue;
signals:
public slots:
};

#endif // CPPVALUE_H
