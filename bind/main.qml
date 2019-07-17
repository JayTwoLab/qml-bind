// main.qml

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

// root object(s)

Window {
    objectName: "mainWindow"
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello mainWindow")

    property string testprop: "juke";

    Text {

        objectName: "mainText"

         // (1) identifier
         id: thisLabel

         // (2) set x- and y-position
         x: 24
         y: 16

         // (3) bind height to 2 * width
         height: 2 * width

         // (4) custom property
         property int times: 24

         // (5) property alias
         property alias anotherTimes: thisLabel.times

         // (6) set text appended by value
         text: "Greetings " + times

         // (7) font is a grouped property
         font.family: "Ubuntu"
         font.pixelSize: 24

         // (8) KeyNavigation is an attached property
         KeyNavigation.tab: otherLabel

         // (9) signal handler for property changes
         onHeightChanged: {
             // console.log('height:', height)
         }

         // focus is need to receive key events
         focus: true

         // change color based on focus value
         color: focus?"red":"black"
     }

    Button { // our Button component
        id: button
        x: 250; y: 12
        text: "Push me"
        onClicked: {
            // [1] call function
            var testParam = "COOL";
            var tempResult = cppValue1.testCalling( testParam ); // call 'testCalling' of C++ 'cppValue1'
            console.log( tempResult ); //  tc: COOL, (random number)

            // [2] get property of C++ 'cppValue1'
            var tempValue = cppValue1.strCppValue;
            console.log( tempValue ); // CppValue : (random number that is made by constructor)
        }
    }

}
