// main.cpp

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtGlobal>
#include <QDebug>

#include "qmltimer.h"

int main(int argc, char *argv[])
{
    //{{ [0] boiler plate code

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    //}} [0]

    // [1] create timer object
    QMLTimer* qmlTimer = new QMLTimer( &app );

    for ( int ic = 0; ic < engine.rootObjects().size(); ic++ )
    {
        QObject* obj = engine.rootObjects().at( ic );
        if (obj == nullptr)
            continue;

        // [2] find the root object that has 'objectName'. 'objectName' is 'mainWindow'.
        QVariant val = obj->property( "objectName" );
        if ( false == val.isNull() &&
             val.toString() == QString("mainWindow") )
        {
            // [3] find child object. 'objectName' is 'mainText'.
            QObject *text = obj->findChild<QObject*>( "mainText" );
            if ( text != nullptr )
            {
                qmlTimer->objText = text;

                QVariant valX = text->property( "x" );
                qDebug() << "x : " << valX;
            }
        }
    }

    return app.exec();
}
