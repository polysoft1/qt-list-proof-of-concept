import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Shapes 1.0

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
        height: childrenRect.height
        // Sometimes when scrolling, the parent is null.
        width: if (parent == null) {
                   childrenRect.width
        } else {
                   Math.min(childrenRect.width, parent.width)
        }

        Rectangle {
            id: profile_pic

            anchors.bottom: msg_content.bottom
            Layout.preferredHeight: 40
            Layout.preferredWidth: 40
            Layout.alignment: Qt.AlignBottom
            height: 40
            width: 40
            radius: 20

            color: "#6F6"
        }

        Shape {
            id: bubble_triangle
            anchors.left: profile_pic.right
            anchors.bottom: msg_content.bottom
            anchors.leftMargin: -5
            width: 20
            height: 20
            ShapePath {
                startX: 0
                startY: 20
                fillColor: "#DDD"
                PathLine { x: 0; y: 20 }
                PathLine { x: 20; y: 0 }
                PathLine { x: 20; y: 20 }
            }
        }

        Rectangle {
            anchors.left: bubble_triangle.right
            anchors.leftMargin: -10
            id: msg_content
            color: "#DDD"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            height: column.height + 15
            width: column.width + 20
            radius: 5

            // The column includes the name and message.
            Column {
                id: column
                spacing: 4
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

                // Username
                Text {
                    id: user
                    text: model.user
                    font.weight: Font.Bold
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
                    width: Math.min(listView.width - (20 * 3) - 20, dummy_text.width)
                }
            }
        }
    }
}
