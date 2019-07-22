# QML binding example

## Example

- See [bind](bind/) example.

1. set QML properties in C++.
	
```cpp
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
```	
	
2. get C++ properties in QML

```cpp
    // [1] set context
    CppValue* cppValue1 = new CppValue( &app );
    engine.rootContext()->setContextProperty( "cppValue1", cppValue1 );
```

```cpp
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
```
	
```qml
            // [2] get property of C++ 'cppValue1'
            var tempValue = cppValue1.strCppValue;
            console.log( tempValue ); // CppValue : (random number that is made by constructor)
```	
	
3. call C++ function in QML
	
```qml
    Button { // our Button component
        id: button
        x: 250; y: 12
        text: "Push me"
        onClicked: {
            // [1] call function
            var testParam = "COOL";
            var tempResult = cppValue1.testCalling( testParam ); // call 'testCalling' of C++ 'cppValue1'
            console.log( tempResult ); //  tc: COOL, (random number)
```

## License

- MIT License

