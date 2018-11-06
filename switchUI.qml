import QtQuick 2.0
import QtQuick.Controls 2.3
Item {

    id:root
    width: 161
    height: 211
    z: -2147483647
    visible: true

    signal qmlSignaltoWidget()
    signal switch1open()
    signal switch1off()
    signal switch2open()
    signal switch2off()
    signal switch3open()
    signal switch3off()
    signal switch4open()
    signal switch4off()

    signal switchallOn()
    signal switchallOff()
    Button {
        id: button
        x: 2
        y: 1
        width: 79
        height: 37
        text: qsTr("ON")
        font.pointSize: 20
        spacing: 5
        onClicked: switchallOn()
    }

    Switch {
        id: switch1
        x: 24
        y: 53
        width: 114
        height: 40
        text: "开关1"
        anchors.horizontalCenter: parent.horizontalCenter
        checkable: true
        font.pointSize: 12

        onPressed: if (switch1.checked == false) switch1open()
                   else if (switch1.checked == true) switch1off()


    }

    Switch {
        id: switch2
        x: 24
        y: 93
        text: qsTr("开关2")
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        checkable: true
        font.pointSize: 12
        onPressed: if (switch2.checked == false) switch2open()
                   else if (switch2.checked == true) switch2off()


    }



    Switch {
        id: switch3
        x: 24
        y: 132
        text: qsTr("开关3")
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 12

        onPressed: if (switch3.checked == false) switch3open()
                   else if (switch3.checked == true) switch3off()

    }

    Switch {
        id: switch4
        x: 43
        y: 171
        text: qsTr("开关4")
        z: 1
        checkable: true
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        checked: false
        autoExclusive: false
        autoRepeat: false
        font.pointSize: 12
        onPressed: if (switch4.checked == false) switch4open()
                   else if (switch4.checked == true) switch4off()

    }

    Button {
        id: button1
        x: 86
        y: 1
        width: 74
        height: 36
        text: qsTr("OFF")
        font.pointSize: 20
        onClicked: switchallOff()

    }


}



/*##^## Designer {
    D{i:3;anchors_x:105;anchors_y:107}D{i:4;anchors_x:95}
}
 ##^##*/
