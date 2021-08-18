import QtQuick 2.0

Row {
    spacing: 60
    property int messageStatus: 0
    property int callStatus: 0
    property int facebookmessageStatus: 0
    property int zaloStatus: 0
    Image {
        id: messageImage
        source: "qrc:/images/battery.png"
        width: 38
        height: 26
        anchors.verticalCenter: parent.verticalCenter
    }
    Image {
        id: callImage
        source: "qrc:/images/battery.png"
        width: 38
        height: 26
        anchors.verticalCenter: parent.verticalCenter
    }
    Image {
        id: facebookImage
        source: "qrc:/images/battery.png"
        width: 38
        height: 26
        anchors.verticalCenter: parent.verticalCenter
    }
    Image {
        id: zaloImage
        source: "qrc:/images/battery.png"
        width: 38
        height: 26
        anchors.verticalCenter: parent.verticalCenter
    }

}
