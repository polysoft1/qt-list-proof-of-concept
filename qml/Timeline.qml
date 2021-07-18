import QtQuick 2.0
import QtQuick.Layouts 1.11

// TODO: Use https://doc.qt.io/qt-5/qml-qtquick-systempalette.html

ListView {
    id: listView
    model: MyModel
    onContentHeightChanged: {
        console.log("listView height: " + parent.height)
    }
    spacing: 5

    delegate: Rectangle {
        color: "#DDD"
        height: childrenRect.height
        width: childrenRect.width
        radius: 10
        anchors.margins: 20

//        id: msg_layout

        RowLayout {
            id: msg_layout
            height: column.paintedHeight
            Layout.margins: 20

            Rectangle {
                id: profile_pic
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                height: 40
                width: 40

                color: "#000"
            }

            Column {
                id: column
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                spacing: 4
                Layout.topMargin: 3
                Layout.bottomMargin: 3
                Layout.leftMargin: 4
                Layout.rightMargin: 8


                // Username
                Text {
                    id: user
                    text: model.user
                }
                // The message
                Text {
                    id: msg
                    text: model.msg
                }
            }

        }
    }
}
