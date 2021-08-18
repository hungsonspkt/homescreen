import QtQuick 2.0

Rectangle {
    id: root
    width: 380//434
    height: 15
    color: colorPowerHandle
    radius: 3

    property int currentBattery: 20
    Rectangle{
        id: battery
        height: parent.height
        color: interfaceOptionColor
        radius:3
        Behavior on width{
            NumberAnimation { duration: 300 }
        }
    }
    onCurrentBatteryChanged: {
        battery.width = currentBattery * root.width / 100
    }

    Column{
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.left
        anchors.rightMargin: 20
        spacing: 0
        Image {
            source: "qrc:/images/Batterynotification.png"
            width: 45
            height: 19
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            width: 50
            Text {
                id: batterytext
                text: currentBattery.toString()
                font.pixelSize: 22
                font.family: fontAvo.name
                color: "#979797"
                horizontalAlignment: Text.AlignRight
                width: 30
            }
            Text {
                font.pixelSize: 22
                color: "#979797"
                font.family: fontAvo.name
                text: "%"
                horizontalAlignment: Text.AlignRight
                width: 20
            }
        }

    }


}
