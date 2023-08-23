import QtQuick 2.9
import QtQuick.Controls 2.15
import com.welida.speedometer 1.0
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 1280
    height: 400
//    title: "CAN Data Viewer"
    color: "black"


    Speedometer
    {
        objectName: "speedoMeter"
        anchors.horizontalCenter:  parent.horizontalCenter
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        alignAngle: alignAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        battery: battery
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }


//     Column {
//        x: 20
//        y: 20

//        Text {
//            text: "Speed: " + canReceiver.speed + " km/h"
//            font.pixelSize: 24
//            color: "white"
//        }

//        Text {
//            text: "RPM: " + canReceiver.rpm
//            font.pixelSize: 24
//            color: "white"
//        }

//        Text {
//            text: "Battery: " + canReceiver.battery + "%"
//            font.pixelSize: 24
//            color: "white"
//        }
//    }
}



