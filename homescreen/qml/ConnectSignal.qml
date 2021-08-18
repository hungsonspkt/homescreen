import QtQuick 2.0
import "components"

Row {
    spacing: 95
    property bool bluetoothStatus: true
    property bool gpsStatus: true

    NetworkSignal{

    }

    Image {
        id: bluetoothImg
        width: 23
        height: 30
        source: bluetoothStatus? "qrc:/images/Bluetooth_hover.png" : "qrc:/images/Bluetooth.png"
    }

    Image {
        id: gpsImg
        width: 23
        height: 30
        source: bluetoothStatus? "qrc:/images/location_hover.png" : "qrc:/images/location.png"
    }
}
