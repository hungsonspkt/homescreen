import QtQuick 2.0

Item {
    property int speed: 0
    property alias mode: modetext.text

    Text {
        id: speedtext
        width: 285//395
        font.pixelSize: 223
        font.family: fontAvo.name
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        color: interfaceMode == 1 ? backgroudColorDark : backgroudColorSun
        text: speed.toString()
//        font.bold: true
    }
    Text {
        text: "Km/h"
        font.pixelSize: 22
        font.family: fontAvo.name
        anchors.left: speedtext.right
        anchors.leftMargin: 40
        anchors.bottom: speedtext.bottom
        anchors.bottomMargin: 30
        color: "#808080"
    }

    Text {
        id: modetext
        text: systemMode == 1 ? "ECO" : "SPORT"
        font.family: fontAvo.name
        font.pixelSize: 32
        anchors.right: speedtext.left
        anchors.rightMargin:50
        anchors.bottom: speedtext.bottom
        anchors.bottomMargin: 30
        color: interfaceOptionColor

    }
}
