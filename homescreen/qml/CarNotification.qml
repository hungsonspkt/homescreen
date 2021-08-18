import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.12
import QtQuick.Shapes 1.0

Rectangle{
    id: root
    width: 510
    height: 510
    color: "transparent"
    radius: width/2


    Shape {
        width: root.width
        height: width
        anchors.centerIn: parent
        ShapePath {
            strokeWidth: 2
            strokeColor: "transparent"
            startX: root.width/2; startY: 0

            fillGradient: RadialGradient {
                id: gradient
                centerX: root.width/2;
                centerY: root.height/2
                centerRadius: root.width/2
                focalX: centerX;
                focalY: centerY;
                GradientStop { position: 0; color: interfaceOptionColor }
                GradientStop { position: 1.0; color: "transparent" }

            }
            PathArc {
                x: root.width/2
                y: root.height
                radiusX: root.width/2
                radiusY: root.height/2
                useLargeArc: true
            }
            PathArc {
                x: root.width/2
                y: 0
                radiusX: root.width/2
                radiusY: root.height/2
                useLargeArc: true
            }
        }
    }

    Rectangle{
        id: rec1
        width: 0
        height: width
        radius: width/2
        border.width: 2
        border.color: "#d0d2d3"
        color: "transparent"
        anchors.centerIn: parent
    }

    PropertyAnimation {
        target: rec1
        property: "width"
        from: 0
        to: root.width/3
        duration: 3000
        loops: Animation.Infinite
        easing.type: Easing.Linear
        running: true
    }

    Rectangle{
        id: rec2
        width: root.width/3
        height: width
        radius: width/2
        border.width: 2
        border.color: "#d0d2d3"
        color: "transparent"
        anchors.centerIn: parent
    }

    PropertyAnimation {
        target: rec2
        property: "width"
        from: root.width/3
        to: root.width*2/3
        duration: 3000
        loops: Animation.Infinite
        easing.type: Easing.Linear
        running: true
    }

    Rectangle{
        id: rec3
        width: root.width*2/3
        height: width
        radius: width/2
        border.width: 2
        border.color: "#d0d2d3"
        color: "transparent"
        anchors.centerIn: parent
    }

    PropertyAnimation {
        target: rec3
        property: "width"
        from: root.width*2/3
        to: root.width
        duration: 3000
        loops: Animation.Infinite
        easing.type: Easing.Linear
        running: true
    }

    Image {
        id: carnotiimg
        source: "qrc:/images/k-auto.png"
        anchors.centerIn: parent
    }

}

