import QtQuick 2.0

Item {
    property int distance: 0
    Row{
        anchors.centerIn: parent
        spacing: 0
        Image {
            width: 350
            height: 50
            source: "qrc:/images/Rangeicon.png"
            anchors.verticalCenter: parent.verticalCenter
        }
//        Image {
//            width: 200
//            height: 30
//            source: "qrc:/images/arrow.png"
////            anchors.verticalCenter: parent.verticalCenter
//            anchors.bottom: parent.bottom
//        }
//        Image {
//            width: 50
//            height: 50
//            source: "qrc:/images/evstation.png"
//            anchors.verticalCenter: parent.verticalCenter
//        }
    }

    Row{
        spacing: 5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 10
        anchors.top: parent.top
        anchors.topMargin: -30
        Text {
            id: distancetext
            font.pixelSize: 23
            font.family: fontAvoBold.name
            font.bold: true
            color: "#979797"
            text: distance.toString()
        }
        Text {
            font.pixelSize: 23
            font.family: fontAvo.name
            text: "Km"
            color: "#979797"
            font.bold: true

        }
    }

}
