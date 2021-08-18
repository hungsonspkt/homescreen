import QtQuick 2.0

Row {
    spacing: 415
    property bool signalLeft: false
    property bool signalRight: false

    Image {
        id: sigleft
        width: 55
        height: 34
        source: signalLeft? "qrc:/images/signal-left.png" : ""
    }
    Image {
        id: sigright
        width: 55
        height: 34
        source: signalRight? "qrc:/images/signal-right.png" : ""
    }

    Timer{
        id: timerleft
        running: false
        interval: 500
        repeat: true
        onTriggered: {
            if(signalLeft){
                if(sigleft.source == "qrc:/images/signal-left.png") sigleft.source = ""
                else sigleft.source = "qrc:/images/signal-left.png"
            }
            else{
                sigleft.source = ""
                timerleft.stop()
            }
        }
    }

    Timer{
        id: timerright
        running: false
        interval: 500
        repeat: true
        onTriggered: {
            if(signalRight){
                if(sigright.source == "qrc:/images/signal-right.png") sigright.source = ""
                else sigright.source = "qrc:/images/signal-right.png"
            }
            else{
                sigright.source = ""
                timerright.stop()
            }
        }
    }

    onSignalLeftChanged: timerleft.start()
    onSignalRightChanged: timerright.start()

}
