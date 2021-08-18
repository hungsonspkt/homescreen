import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
//import QtQuick.Extras 1.4
import QtGraphicalEffects 1.12
import "components"

Item {
    id: dashboard
    width: mainwindow.width
    height: mainwindow.height

    PowerDashboard{
        width: 707
        height: width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30

//        anchors.centerIn: parent
    }

    Rectangle{
        id: bottomcontainer
        width: parent.width
        height: 73.5
        color: "transparent"
        anchors.bottom: parent.bottom
        Rectangle{
            id: linespace
            width: 1850
            height: 1
            color: "#a6a8ab"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Rectangle{
            width: 1
            height: 38
            color: "#a6a8ab"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 600
        }
        Rectangle{
            width: 1
            height: 38
            color: "#a6a8ab"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 600
        }

        CarModeOption{
            id: carmode
            anchors.centerIn: parent
            currentCarMode: 1
        }
    }

    Item{
        id: systemContainer
        width: 600
        height: 73.5
        anchors.bottom: parent.bottom

        SystemAlert{
            anchors.centerIn: parent
        }
    }

    Item{
        id: appnotiContainer
        width: 600
        height: 73.5
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        AppNotification{
            anchors.centerIn: parent
        }
    }

    CarNotification{
        id: carnoti
        width: 510
        height: 510
        anchors.top: parent.top
        anchors.topMargin: 89
        anchors.left: parent.left
        anchors.leftMargin: 30
    }

    EmojiNotifiaction{
        id: emojinoti
        width: 510
        height: 510
        anchors.top: parent.top
        anchors.topMargin: 89
        anchors.right: parent.right
        anchors.rightMargin: 30
    }

    InforTimeAndTemp{
        id: infortimetemp
        anchors.left: parent.left
        anchors.leftMargin: 42
        anchors.bottom: bottomcontainer.top
        anchors.bottomMargin: 10
        temperature: "25"
    }

    ConnectSignal{
        id: connectsignal
        anchors.left: parent.left
        anchors.leftMargin: 37
        anchors.top: parent.top
        anchors.topMargin: 25
    }

    LightMode{
        id: light
        anchors.verticalCenter: connectsignal.verticalCenter
        anchors.left: connectsignal.right
        anchors.leftMargin: 274
        lightMode: 1
    }

    SignalTurn{
        id: signalturn
        anchors.verticalCenter: connectsignal.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        signalLeft: true
        signalRight: true
    }


}
