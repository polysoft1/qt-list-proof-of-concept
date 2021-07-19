import QtQuick 2.0
import QtQuick.Layouts 1.11

// TODO: Use https://doc.qt.io/qt-5/qml-qtquick-systempalette.html

// This is the component that allows multiple items stacked on top of each other as a list.
ListView {
    id: listView
    model: MyModel
    onContentHeightChanged: {
        console.log("listView height: " + parent.height)
    }
    spacing: 5 // Spacing between messages
    width: parent.width

    // This is the item of the list
    delegate: Rectangle {
        color: "#DDD"
        height: childrenRect.height
        // Sometimes when scrolling, the parent is null.
        width: if (parent == null) {
                   childrenRect.width
        } else {
                   Math.min(childrenRect.width, parent.width)
        }

        radius: 10
        anchors.margins: 20

        // The row layout is to put the profile pic to the left of the message
        RowLayout {
            id: msg_layout
            height: column.paintedHeight
            Layout.margins: 20

            Rectangle {
                id: profile_pic
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50
                Layout.alignment: Qt.AlignTop
                height: 50
                width: 50

                color: "#6F6"
            }

            // The column includes the name and message.
            Column {
                id: column
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                spacing: 4
                Layout.topMargin: 2
                Layout.bottomMargin: 3
                Layout.leftMargin: 4
                Layout.rightMargin: 8


                // Username
                Text {
                    id: user
                    text: model.user
                }
                // Dummy text to get the size
                Text {
                    id: dummy_text
                    text: model.msg
                    visible: false
                }
                // The message
                Text {
                    id: msg
                    text: model.msg
                    wrapMode: Text.Wrap
                    // Shrink if the message would not fill the entire width available.
                    width: Math.min(listView.width - (msg_layout.Layout.margins * 3), dummy_text.width)
                }
            }

        }
    }
}
