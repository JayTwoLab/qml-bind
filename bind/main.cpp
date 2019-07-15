// main.cpp

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtGlobal>
#include <QDebug>

int main(int argc, char *argv[])
{
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

    for ( int ic = 0; ic < engine.rootObjects().size(); ic++ )
    {
        QObject* obj = engine.rootObjects().at( ic );
        if (obj == nullptr)
            continue;

        // [1] find the root object that has 'objectName'. 'objectName' is 'mainWindow'.

        QVariant val = obj->property( "objectName" );
        if ( false == val.isNull() &&
             val.toString() == QString("mainWindow") )
        {
            // [2] find child object. 'objectName' is 'mainText'.

            QObject *text = obj->findChild<QObject*>( "mainText" );
            if ( text != nullptr )
            {
                QVariant valX = text->property( "x" );
                qDebug() << "x : " << valX;
            }
        }
    }


    return app.exec();
}
