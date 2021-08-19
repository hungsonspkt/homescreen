import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import "components"

ApplicationWindow {
    flags: Qt.FramelessWindowHint
    id: mainwindow
    width: 1920
    height: 720
    visible: true
    title: qsTr("HMI Auto")

    property string colorPowerSlider: "#f6921e"
    property string colorPowerHandle: "#d0d2d3"
    property int systemMode: 1 //1: eco; 2: sport
    property int interfaceMode: 1 // 1:sun, 2: dark
    property int interfaceOption: 1 // 1:cam, 2: xanh la, 3: xanh navi, 4: xanh ma, 5: nau
    property string interfaceImageSport: "qrc:/images/sportOrange.png"
    property string interfaceOptionColor: "#f6921e"
    property string odoColorDark: "#4d4e4e"
    property string odoColorSun: "#d0d2d3"
    property string backgroudColorDark: "black"
    property string backgroudColorSun: "white"
    property string batteryAlert: "qrc:/images/BatteryOrange.png"
    property string wipersAlert: "qrc:/images/WindshieldwasherOrange.png"
    property string brakeAlert: "qrc:/images/BrakeOrange.png"
    property string seatBeltAlert: "qrc:/images/SeatbeltOrange.png"


    Component.onCompleted: setColorOption()

    FontLoader {
        id: fontAvo;
        source: "qrc:/fonts/UTMAvo.ttf"
    }
    FontLoader {
        id: fontAvoBold;
        source: "qrc:/fonts/UTMAvoBold.ttf"
    }


    Rectangle{
        id: background
        anchors.fill: parent
        color: interfaceMode == 1 ? backgroudColorSun : backgroudColorDark

    }

    DashBoard{
//       anchors.fill: parent
        width: mainwindow.width
        height: 720

    }

    onInterfaceOptionChanged:  setColorOption()

    function setColorOption(){
        switch(interfaceOption){
        case 1:
            interfaceOptionColor = "#f6921e"; // cam
            interfaceImageSport = "qrc:/images/sportOrange.png"
            batteryAlert = "qrc:/images/BatteryOrange.png"
            wipersAlert = "qrc:/images/WindshieldwasherOrange.png"
            brakeAlert = "qrc:/images/BrakeOrange.png"
            seatBeltAlert = "qrc:/images/SeatbeltOrange.png"
          break;
        case 2:
            interfaceOptionColor = "#98c255"; //xanh la
            interfaceImageSport = "qrc:/images/sportGreen.png"
            batteryAlert = "qrc:/images/BatteryGreen.png"
            wipersAlert = "qrc:/images/WindshieldwasherGreen.png"
            brakeAlert = "qrc:/images/BrakeGreen.png"
            seatBeltAlert = "qrc:/images/SeatbeltGreen.png"
          break;
        case 3:
            interfaceOptionColor = "#48a39c"; //xanh navi
            interfaceImageSport = "qrc:/images/sportGreenNavi.png"
            batteryAlert = "qrc:/images/BatteryGreenNavi.png"
            wipersAlert = "qrc:/images/WindshieldwasherGreenNavi.png"
            brakeAlert = "qrc:/images/BrakeGreenNavi.png"
            seatBeltAlert = "qrc:/images/SeatbeltGreenNavi.png"
            break;
        case 4:
            interfaceOptionColor = "#d8dc50"; //xanh ma
            interfaceImageSport = "qrc:/images/sportGreenbanana.png"
            batteryAlert = "qrc:/images/BatteryGreenBanana.png"
            wipersAlert = "qrc:/images/WindshieldwasherGreenBanana.png"
            brakeAlert = "qrc:/images/BrakeGreenBanana.png"
            seatBeltAlert = "qrc:/images/SeatbeltGreenBanana.png"
            break;
        case 5:
           interfaceOptionColor = "#bd9a71"; //nau
            interfaceImageSport = "qrc:/images/sportBrow.png"
            batteryAlert = "qrc:/images/BatteryBrow.png"
            wipersAlert = "qrc:/images/WindshieldwasherBrow.png"
            brakeAlert = "qrc:/images/BrakeBrow.png"
            seatBeltAlert = "qrc:/images/SeatbeltBrow.png"
           break;
        default: break;
        }
    }
}
