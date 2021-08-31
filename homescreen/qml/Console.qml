import QtQuick 2.0

Rectangle{
    id: root
    width: 600; height: 400
    border.color: "transparent"
    radius: 10
    color: "#2962ff"
    border.width: 1
    property int valuetest: 0

    MouseArea{
        anchors.fill: parent
        id: dragConsolWindowArea
        drag.target: parent
        drag.maximumX: mainwindow.width - width
        drag.maximumY: mainwindow.height - height
        drag.minimumX: 0
        drag.minimumY: 0

    }
    Item {
        width: parent.width
        height: 45
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Console logs")
            font.pixelSize: 20
            anchors.left: parent.left
            anchors.leftMargin: 20
            color: "white"
        }
    }

    Rectangle{
        width: parent.width-40
        height: parent.height -50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        ListView{
            id: listviewscroll
            clip: true
            anchors.fill: parent
            model: listConsoleMsg
            delegate: Item{
                width: listviewscroll.width
                height: 40
                Text {
                    id: textmsg
                    anchors.fill: parent
                    wrapMode: Text.WrapAnywhere
                    font.pixelSize: 18
                    text: msg
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                }
                Rectangle{
                    width: parent.width
                    height: 1
                    color: "#bdbdbd"
                    anchors.bottom: parent.bottom
                }
            }
        }
    }

    ListModel{
        id: listConsoleMsg
    }


    Timer{
        interval: 500
        running: false
        repeat: true
        onTriggered: {
            valuetest ++;
            listConsoleMsg.insert(0,{"msg": Qt.formatTime(new Date(),"hh:mm:ss")+": " + valuetest});
            if(listConsoleMsg.count > 50) listConsoleMsg.remove(listConsoleMsg.count -1)
        }
    }

    function add_console_log(msg){
        listConsoleMsg.insert(0,{"msg": Qt.formatTime(new Date(),"hh:mm:ss")+": " + msg});
        if(listConsoleMsg.count > 50) listConsoleMsg.remove(listConsoleMsg.count -1)
    }

    Connections{
        target: _mainkauto
        onAdd_log_to_console:{
            add_console_log(_msg);
        }
    }

}
