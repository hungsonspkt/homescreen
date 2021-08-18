import QtQuick 2.0

Item {
    width:  42
    height: 27
    property int lightMode: 0 // 0: off , 1: phase, 2: cos
    Image {
        id: lightmode
        anchors.centerIn: parent
        source: lightMode == 0? "": lightMode == 1? "qrc:/images/high_beam.png" : "qrc:/images/low_beam.png"
    }

}
