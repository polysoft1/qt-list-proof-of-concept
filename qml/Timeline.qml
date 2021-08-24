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
    // interactive: false
    // Good example of how to setup scrolling to get rid of the annoying inertia.
    // https://github.com/Nheko-Reborn/nheko/blob/5b460861b126a49f1e186c8b59ffb0faf0109aab/resources/qml/ScrollHelper.qml

    // This is the item of the list
    delegate: Rectangle {
        anchors.right: if (model.self) { parent.right }
        height: childrenRect.height
        // Sometimes when scrolling, the parent is null.
        width: if (parent == null) {
                   childrenRect.width
        } else {
                   Math.min(childrenRect.width, parent.width)
        }

        Rectangle {
            id: profile_pic

            anchors.left: if (!model.self) { parent.left }
            anchors.bottom: msg_content.bottom
            anchors.right: if (model.self) { parent.right }
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

            anchors.left: if (!model.self) { profile_pic.right }
            anchors.right: if (model.self) { profile_pic.left }
            anchors.bottom: msg_content.bottom
            anchors.leftMargin: -5
            anchors.rightMargin: -5
            width: 20
            height: 20
            ShapePath {
                startX: 0
                startY: 20
                fillColor: "#DDD"
                PathLine { x: if (model.self) { 20 } else { 0 } y: 20 } // bottom left
                PathLine { x: if (model.self) { 0 } else { 20 } y: 0 } // top right
                PathLine { x: if (model.self) { 0} else { 20 } y: 20 } // bottom right
            }
        }

        Rectangle {
            id: msg_content

            anchors.left: if (!model.self) { bubble_triangle.right }
            anchors.right: if (model.self) { bubble_triangle.left }
            anchors.leftMargin: -10
            color: "#DDD"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            height: column.height + 15
            width: column.width + 20
            radius: 5
            anchors.rightMargin: -5

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
                TextEdit {
                    id: msg
                    text: model.msg
                    wrapMode: Text.Wrap
                    // Shrink if the message would not fill the entire width available.
                    width: Math.min(listView.width - (20 * 3) - 20, dummy_text.width)
                    readOnly: true
                    selectByMouse: true

                }
            }
        }
    }
}
