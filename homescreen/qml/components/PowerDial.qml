import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
//import QtQuick.Extras 1.4
import QtGraphicalEffects 1.12

Item {
    id: root
    property alias anglePower: control.angle

    property int fromAngle: -125
    property int toAngle: 125
    property int currentPower: 0


    Dial{
        id: control
        value: (140+fromAngle)/280
        anchors.centerIn: parent
        onAngleChanged:{
//            console.log("value: ", angle, position)
            if(angle < fromAngle){
                value = (140+fromAngle)/280
            }
            if(angle > toAngle){
                value = (140+toAngle)/280
            }
            canvas.requestPaint()
        }
        width: root.width - 35
        height: width
        background: Rectangle {
            id: outerRing
            x: control.width / 2 - width / 2
            y: control.height / 2 - height / 2
            width: Math.max(64, Math.min(control.width, control.height))
            height: width
            color: "transparent"
            radius: width / 2
            border.color:  "transparent"
            opacity: control.enabled ? 1 : 0.3
        }

        handle: Rectangle {
            id: handleItem
            x: control.background.x + control.background.width / 2 - width
            y: control.background.y + control.background.height / 2 - height / 2
            width: 5
            height: 25
            color: interfaceOptionColor
//            radius: 8
            antialiasing: true
            opacity: control.enabled ? 1 : 0.3
            transform: [
                Translate {
                    y: -Math.min(control.background.width, control.background.height) * 0.5 + handleItem.height / 2
                },
                Rotation {
                    angle: control.angle
                    origin.x: handleItem.width
                    origin.y: handleItem.height / 2
                }
            ]
        }
    }

    Text {
        text: "50 Kw"
        font.pixelSize: 32
        font.family: fontAvo.name
        anchors.left: parent.right
        anchors.leftMargin: -50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 150
        color: "#a6a8ab"
    }

    Canvas {
        id: canvasSlider
        width: root.width
        height: width
        anchors.centerIn: parent
        rotation: -90 + fromAngle
        onPaint: {
            var c = getContext('2d')
            c.clearRect(0, 0, width, height)
            c.beginPath()
            c.lineWidth = 8
            c.strokeStyle = colorPowerHandle
            c.arc(canvas.width/2, canvas.height/2, canvas.width/2 - 15, 0, Math.PI * 2 * (toAngle*2)/360)
            c.stroke()
        }
    }

    Canvas {
        id: canvas
        width: root.width
        height: width
        anchors.centerIn: parent
        rotation: -90 + fromAngle
        onPaint: {
            var c = getContext('2d')
            c.clearRect(0, 0, width, height)
            c.beginPath()
            c.lineWidth = 8
            c.strokeStyle = interfaceOptionColor
            c.arc(canvas.width/2, canvas.height/2, canvas.width/2 - 15, 0, Math.PI * 2 * (toAngle+anglePower)/360)
            c.stroke()

        }
    }

    onCurrentPowerChanged: {
        powerChange.from = control.value
        powerChange.to =  currentPower*((1- (280 - toAngle*2)/280)/50) + (140+fromAngle)/280
        powerChange.running = true
    }

    PropertyAnimation {
        id: powerChange
        target: control
        property: "value"
        duration: 300
        easing.type: Easing.Linear
        running: false
    }
    Image {
        id: powerSport
        anchors.fill: parent
        scale: 0.92
        rotation: 0.2
        visible: systemMode == 2
        source: interfaceImageSport
    }
}
