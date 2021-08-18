import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
//import QtQuick.Extras 1.4
import QtGraphicalEffects 1.12
import "components"

Item {
    id: root
    property int speedValue: 0
    property int modeIndex: 1
    property bool testdata: true
    PowerDial{
        id: powerdial
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        currentPower: 0
    }

    Timer{
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            if(powerdial.currentPower < 50 && testdata ){
                powerdial.currentPower = powerdial.currentPower  + 5
                battery.currentBattery = battery.currentBattery + 10
                odorow.speed = odorow.speed + 20
                distancerow.distance = distancerow.distance + 15
                odoinforrow.currentOdo = odoinforrow.currentOdo *5
                odoinforrow.currentTripA = odoinforrow.currentTripA *2
                if(powerdial.currentPower >= 50 ){
                    interfaceMode = 2;
                    testdata = false
                    systemMode = 2
                }
            }
            else{
                powerdial.currentPower = powerdial.currentPower  - 5
                battery.currentBattery = battery.currentBattery - 10
                odorow.speed = odorow.speed - 20
                distancerow.distance = distancerow.distance - 15
                odoinforrow.currentOdo = odoinforrow.currentOdo /5
                odoinforrow.currentTripA = odoinforrow.currentTripA /2
                if(powerdial.currentPower <= 0 ){
                    interfaceMode = 1;
                    if(interfaceOption < 5) interfaceOption ++;
                    else interfaceOption = 1;

                    if(carmode.currentCarMode < 4) carmode.currentCarMode = carmode.currentCarMode + 1
                    else carmode.currentCarMode = 0
                    systemMode = 1
                    testdata = true
                }
            }

        }
    }

    OdoRow{
        id: odorow
        height: 190
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 50
        speed: speedValue
//        mode: "ECO"
    }

    DistanceRow{
        id: distancerow
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: odorow.bottom
        anchors.topMargin: 170
        distance: 0
    }

    BatterySlider{
       id: battery
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.top: distancerow.bottom
       anchors.topMargin: 50
       currentBattery: 0

    }

    OdoInfor{
        id: odoinforrow
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: battery.bottom
        anchors.topMargin: 40
        currentOdo: 1
        currentTripA: 1
    }

}
