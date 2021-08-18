import QtQuick 2.0

Row {
    spacing: 60
    property bool batteryStatus: true
    property bool wipersStatus: true
    property bool brakeStatus: true
    property bool seatBeltStatus: true
    Image {
        id: batteryImage
        source: batteryAlert//"qrc:/images/battery.png"
        width: 38
        height: 26
        anchors.verticalCenter: parent.verticalCenter
    }
    Image {
        id: wipersImage
        source: wipersAlert//"qrc:/images/Windshield.png"
        width: 38
        height: 26
        anchors.verticalCenter: parent.verticalCenter
    }
    Image {
        id: brakeImage
        source: brakeAlert//"qrc:/images/Brake.png"
        width: 38
        height: 26
        anchors.verticalCenter: parent.verticalCenter
    }
    Image {
        id: seatBeltImage
        source: seatBeltAlert//"qrc:/images/Seatbelt.png"
        width: 26
        height: 35
        anchors.verticalCenter: parent.verticalCenter
    }

}
