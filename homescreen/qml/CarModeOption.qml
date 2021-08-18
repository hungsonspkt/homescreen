import QtQuick 2.0

Row {
    id: root
    spacing: 140
    property int currentCarMode: 0

    Text {
        id: modeR
        text: "R"
        width: 30
        font.pixelSize: 42
        font.family: fontAvoBold.name
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        color: interfaceOptionColor

    }
    Text {
        id: modeN
        text: "N"
        width: 30
        font.pixelSize: 42
        font.family: fontAvoBold.name
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        color: interfaceOptionColor
        ColorAnimation {
            from: interfaceOptionColor
            to: "#f1f1f2"
            duration: 200
        }

    }
    Text {
        id: modeD
        text: "D"
        width: 30
        font.pixelSize: 42
        font.family: fontAvoBold.name
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        color: interfaceOptionColor

        ColorAnimation {
            from: interfaceOptionColor
            to: "#f1f1f2"
            duration: 200
        }

    }

    states: [
        State {
            name: "CHECK"
            PropertyChanges { target: modeR; color: interfaceOptionColor }
            PropertyChanges { target: modeN; color: interfaceOptionColor }
            PropertyChanges { target: modeD; color: interfaceOptionColor }
        },
        State {
            name: "MODER"
            PropertyChanges { target: modeR; color: interfaceOptionColor }
            PropertyChanges { target: modeN; color: interfaceMode == 1? "#f1f1f2" : "#221f20"}
            PropertyChanges { target: modeD; color: interfaceMode == 1? "#f1f1f2" : "#221f20"}
        },
        State {
            name: "MODEN"
            PropertyChanges { target: modeR; color: interfaceMode == 1? "#f1f1f2" : "#221f20"}
            PropertyChanges { target: modeN; color: interfaceOptionColor }
            PropertyChanges { target: modeD; color: interfaceMode == 1? "#f1f1f2" : "#221f20"}
        },
        State {
            name: "MODED"
            PropertyChanges { target: modeR; color: interfaceMode == 1? "#f1f1f2" : "#221f20"}
            PropertyChanges { target: modeN; color: interfaceMode == 1? "#f1f1f2" : "#221f20"}
            PropertyChanges { target: modeD; color: interfaceOptionColor }
        },
        State {
            name: "MODEOFF"
            PropertyChanges { target: modeR; color: interfaceMode == 1? "#f1f1f2" : "#221f20"}
            PropertyChanges { target: modeN; color: interfaceMode == 1? "#f1f1f2" : "#221f20"}
            PropertyChanges { target: modeD; color: interfaceMode == 1? "#f1f1f2" : "#221f20"}
        }
    ]

    onCurrentCarModeChanged: {

        switch(currentCarMode){
        case 0:
            root.state = "CHECK";
            break;
        case 1:
            root.state = "MODER";
            break;
        case 2:
            root.state = "MODEN";
            break;
        case 3:
            root.state = "MODED";
            break;
        case 4:
            root.state = "MODEOFF";
            break;
        default: break;
        }
    }
}
