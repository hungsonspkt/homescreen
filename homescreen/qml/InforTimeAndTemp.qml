import QtQuick 2.0
import QtQml 2.0

Item {
    height:  33

    property alias temperature: temptext.text
    property var locale: Qt.locale()


    Text {
        id: kgroup
        text: "K-AUTO EV Mini"
        font.pixelSize: 20
        font.family: fontAvo.name
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: parent.verticalCenter
        color: interfaceOptionColor
    }

    Rectangle{
        id: spacerec
        width: 1
        height: 33
        color: "#a6a8ab"
        anchors.left: kgroup.right
        anchors.leftMargin: 27
    }

    Text {
        id: temptext
        font.pixelSize: 20
        width: 25
        font.family: fontAvo.name
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "#808080"
        anchors.left: spacerec.right
        anchors.leftMargin: 27
    }

    Text {
        id: otext
        font.pixelSize: 10
        text: "o"
        font.family: fontAvo.name
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "#808080"
        anchors.left: temptext.right
        anchors.leftMargin: 2
        anchors.top: parent.top
        anchors.topMargin: 5
    }


    Text {
        id: ctext
        font.pixelSize: 20
        text: "C"
        font.family: fontAvo.name
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "#808080"
        anchors.left: otext.right
        anchors.leftMargin: 2
        anchors.verticalCenter: parent.verticalCenter
    }

    Text {
        id: timetext
        font.pixelSize: 20
        text: Qt.formatTime(new Date(),"hh:mm AP")
        font.family: fontAvo.name
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "#808080"
        anchors.left: ctext.right
        anchors.leftMargin: 40
        anchors.verticalCenter: parent.verticalCenter
    }

    Component.onCompleted: {
        timertime.start()
    }

    Timer{
        id: timertime
        interval: 60000
        running: false
        repeat: true
        onTriggered: {
            timetext.text = Qt.formatTime(new Date(),"hh:mm AP")
        }
    }

}
