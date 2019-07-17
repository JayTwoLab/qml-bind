// main.cpp

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QtGlobal>
#include <QDebug>

#include "qmltimer.h"
#include "cppvalue.h"

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

    // [1] set context
    CppValue* cppValue1 = new CppValue( &app );
    engine.rootContext()->setContextProperty( "cppValue1", cppValue1 );

    // [2] create timer object (for testing)
    QMLTimer* qmlTimer = new QMLTimer( &app );

    int rootObjSize = engine.rootObjects().size();
    for ( int ic = 0; ic < rootObjSize ; ic++ )
    {
        QObject* obj = engine.rootObjects().at( ic );
        if ( obj == nullptr )
            continue;

        // [3] find the root object that has 'objectName'. 'objectName' is 'mainWindow'.
        QVariant val = obj->property( "objectName" );
        if ( false == val.isNull() &&
             val.toString() == QString("mainWindow") )
        {
            // [4] success to find 'mainWindow'
            QObject* mainWindowObj = obj;
            mainWindowObj->setProperty( "title", QVariant(QString("HELLO WORLD")) ); // change 'title' of 'mainWindow'

            // [5] find child object. which objectName is 'mainText'.
            QObject *textObj = mainWindowObj->findChild<QObject*>( "mainText" );
            if ( textObj != nullptr )
            {
                qmlTimer->objText = textObj;

                // [6] get 'x' from 'mainText'
                QVariant valX = textObj->property( "x" );
                qDebug() << "x : " << valX;
            }
        }
    }

    return app.exec();
}
