import QtQuick 2.0

Button {
    id: item
    width: 100; height: 100
    text: "aaaaa"

    signal qmlSignal()

    MouseArea {
        anchors.fill: parent
        onClicked: item.qmlSignal()
    }
}
