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

    Image {
        id: carnotiimg
        source: "qrc:/images/Emoji.png"
        anchors.centerIn: parent
    }


//    Rectangle {
//           anchors.fill: parent
//           color: "transparent"
//           Row {
//               anchors.fill: parent

//               Canvas {
//                   id: canvas
//                   width: root.width
//                   height: root.height
//                   onPaint: {
//                       var context = getContext('2d');
//                       context.rect(0, 0, canvas.width, canvas.height);
//                       var grd = context.createRadialGradient(root.width/2,root.width/2, 100, root.width/2, root.width/2, root.width/2);
//                       grd.addColorStop(0.25, 'transparent');
//                       grd.addColorStop(0.499, 'red');
//                       grd.addColorStop(0.5, 'transparent');
//                       context.fillStyle = grd;
//                       context.fill();
//                   }
//               }
//           }
//       }

}
