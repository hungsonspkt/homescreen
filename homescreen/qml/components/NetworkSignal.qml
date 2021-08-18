import QtQuick 2.0

Row {
    height: 30
    width: 30
    spacing: 6
    property int valueNetWork: 100

    Rectangle{
        width: 4
        height: 10
        color: valueNetWork > 0 ? "#f6921e" : "#bbbdbf"
        anchors.bottom: parent.bottom
    }
    Rectangle{
        width: 4
        height: 20
        color: valueNetWork > 30 ? "#f6921e" : "#bbbdbf"
        anchors.bottom: parent.bottom
    }
    Rectangle{
        width: 4
        height: 30
        color: valueNetWork > 60 ? "#f6921e" : "#bbbdbf"
        anchors.bottom: parent.bottom
    }

}
