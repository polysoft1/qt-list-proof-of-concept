import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Shapes 1.0
import QtQuick.Controls 2.12

import '.'

// TODO: Use https://doc.qt.io/qt-5/qml-qtquick-systempalette.html


// This is the component that allows multiple items stacked on top of each other as a list.
Rectangle {
    id: background
    color: "#eceff1"

    // Settings
    property var profilePicSize: 50
    property var profilePicTopAlign: true
    property var showSelfProfilePic: true
    property var msgBackgroundColor: "#FFF"
    property var selfMsgBackgroundColor: "#cfd8dc"

    ListView {
        id: listView
        model: MyModel
        spacing: 13 // Spacing between messages
        width: if (parent != null) parent.width
        height: if (parent != null) parent.height
        interactive: false

        // This is the item of the list
        delegate: Rectangle {
            id: list_row
            anchors.right: if (model.self && parent != null) { parent.right }
            height: childrenRect.height

            // Calculated values
            property var showingProfilePic: showSelfProfilePic || !model.self
            property var actualProfilePicSize: if (showingProfilePic) { profilePicSize } else { 10 }
            property var selfBackgroundColor: if (model.self) { selfMsgBackgroundColor } else { msgBackgroundColor }

            Rectangle {
                id: profile_pic

                anchors.left: if (!model.self) { parent.left }
                anchors.bottom: if (!profilePicTopAlign) msg_content.bottom
                anchors.top: if (profilePicTopAlign) msg_content.top
                anchors.right: if (model.self) { parent.right }
                Layout.preferredHeight: 40
                Layout.preferredWidth: 40
                Layout.alignment: if (profilePicTopAlign) { Qt.AlignBottom } else {Qt.AlignTop}
                height: profilePicSize
                width: actualProfilePicSize
                radius: profilePicSize / 2 + 1
                visible: showingProfilePic

                color: "#6F6"
            }

            Shape {
                id: bubble_triangle

                anchors.left: if (!model.self) { profile_pic.right }
                anchors.right: if (model.self) { profile_pic.left }
                anchors.bottom: if (!profilePicTopAlign) { msg_content.bottom }
                anchors.top: if (profilePicTopAlign) { msg_content.top }
                anchors.leftMargin: -5
                anchors.rightMargin: -5
                width: 20
                height: 20
                ShapePath {
                    startX: if (model.self) {20} else { 0 }
                    startY: if (profilePicTopAlign) { 0 } else { 20}
                    fillColor: selfBackgroundColor
                    strokeColor: selfBackgroundColor
                    strokeWidth: 0
                    PathLine { x: if (model.self) { 20 } else { 0 } y: if (profilePicTopAlign) { 0 } else { 20}  } // bottom left
                    PathLine { x: if (model.self) { 0 } else { 20 } y: if (profilePicTopAlign) { 20 } else { 0}  } // top right
                    PathLine { x: if (model.self) { 0} else { 20 } y: if (profilePicTopAlign) { 0 } else { 20}  } // bottom right
                }
            }

            Rectangle {
                id: msg_content

                anchors.left: if (!model.self) { bubble_triangle.right }
                anchors.right: if (model.self) { bubble_triangle.left }
                anchors.leftMargin: -10
                color: selfBackgroundColor
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                height: column.height + 15
                width: column.width + 20
                radius: 5
                anchors.rightMargin: -10

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
                        color: Palette.text
                    }
                    // Dummy text to get the size
                    Text {
                        id: dummy_text
                        text: model.msg
                        visible: false
                        color: Palette.text
                    }
                    // The message
                    TextEdit {
                        id: msg
                        text: model.msg
                        color: Palette.text
                        wrapMode: Text.Wrap
                        // Shrink if the message would not fill the entire width available.
                        width: Math.min(listView.width - (actualProfilePicSize) - 40, dummy_text.width)
                        readOnly: true
                        selectByMouse: true

                    }
                }
            }
        }

        ScrollBar.vertical: ScrollBar {
            minimumSize: 0.03
            //policy: ScrollBar.AlwaysOn
        }
        ScrollHelper {
            id: scrollHelper
            flickable: listView
            anchors.fill: listView
        }

    }

}
