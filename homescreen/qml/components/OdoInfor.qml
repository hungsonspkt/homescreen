import QtQuick 2.0

Row {
    spacing: 95//145
    property int currentOdo: 0
    property int currentTripA: 0

    Text {
        id: odotext
        text: "ODO: 000000"
        font.pixelSize: 22
        color: "#979797"
        font.family: fontAvo.name
        width: 140
        horizontalAlignment: Text.AlignLeft
    }

    Text {
        id: tripAtext
        text: "TRIP A: 000"
        font.family: fontAvo.name
        font.pixelSize: 22
        color: "#979797"
        width: 120
        horizontalAlignment: Text.AlignLeft
    }

    onCurrentOdoChanged: {
        if(currentOdo < 10) odotext.text = "ODO: 00000" + currentOdo.toString()
        else if(currentOdo >= 10 && currentOdo < 100) odotext.text = "ODO: 0000" + currentOdo.toString()
        else if(currentOdo >= 100 && currentOdo < 1000) odotext.text = "ODO: 000" + currentOdo.toString()
        else if(currentOdo >= 1000 && currentOdo < 10000) odotext.text = "ODO: 00" + currentOdo.toString()
        else if(currentOdo >= 10000 && currentOdo < 100000) odotext.text = "ODO: 0" + currentOdo.toString()
        else if(currentOdo >= 100000 && currentOdo < 1000000) odotext.text = "ODO: " + currentOdo.toString()

    }

    onCurrentTripAChanged: {
        if(currentTripA < 10) tripAtext.text = "TRIP A: 00" + currentTripA.toString()
        else if(currentTripA >= 10 && currentTripA < 100) tripAtext.text = "TRIP A: 0" + currentTripA.toString()
        else if(currentTripA >= 100 && currentTripA < 1000) tripAtext.text = "TRIP A: " + currentTripA.toString()
    }
}
