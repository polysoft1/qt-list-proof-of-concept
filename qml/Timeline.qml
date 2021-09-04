import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Shapes 1.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

import '.'

// TODO: Use https://doc.qt.io/qt-5/qml-qtquick-systempalette.html


// This is the component that allows multiple items stacked on top of each other as a list.
Rectangle {
    id: background
    color: "#eceff1"
    width: if (parent != null) parent.width
    height: if (parent != null) parent.height

    // Settings
    property var groupSpacing: 13
    property var messageSpacing: 4
    property var profilePicSize: 50
    property var bubbleRadius: 5
    property var profilePicTopAlign: true
    property var showSelfProfilePic: true
    property var msgBackgroundColor: "#FFF"
    property var selfMsgBackgroundColor: "#cfd8dc"

    ListView {
        id: groupListView
        model: MyModel
        spacing: background.groupSpacing // Spacing between messages
        width: background.width
        height: background.height
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
                radius: background.bubbleRadius
                anchors.rightMargin: -10

                // The column includes the name and message.
                Column {
                    id: column
                    spacing: background.messageSpacing
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    Row {
                        spacing: 10
                        // Username
                        Text {
                            id: user
                            text: model.user
                            font.weight: Font.Bold
                            color: Palette.text
                        }
                        Text {
                            anchors.verticalCenter: parent.verticalCente
                            id: group_timestamp
                            text: "Timestamp"
                            color: Palette.text
                            opacity: 0.7
                            font.pointSize: 7
                        }
                    }
                    // The messages
                    Repeater/*ListView*/ {
                        id: msgListView
                        model: msg_model
                        height: childrenRect.height
                        width: childrenRect.width

                        delegate: Rectangle {
                            height: msg_mousearea.childrenRect.height + 3 - msg_options_and_info.height
                            implicitWidth: msg.width
                            color: selfBackgroundColor

                            function checkOptionsVisibility() {
                                var shouldBeVisible = msg_mousearea.containsMouse || msg_options_mousearea.containsMouse;
                                msg_options_and_info.visible = shouldBeVisible;
                                options_dropshadow.visible = shouldBeVisible;
                                msg_options_and_info_row.visible = shouldBeVisible;
                            }

                            MouseArea {
                                anchors.fill: parent
                                id: msg_mousearea
                                hoverEnabled: true
                                onHoveredChanged: {
                                    checkOptionsVisibility();
                                }
                                height: childrenRect.height

                                // Dummy text to get the size
                                Text {
                                    id: dummy_text
                                    text: model.msg
                                    visible: false
                                    color: Palette.text
                                }

                                TextEdit {
                                    id: msg
                                    text: model.msg
                                    color: Palette.text
                                    wrapMode: Text.Wrap
                                    // Shrink if the message would not fill the entire width available.
                                    width: Math.min(background.width - (actualProfilePicSize) - 40, dummy_text.width)
                                    readOnly: true
                                    selectByMouse: true

                                }

                                Rectangle {
                                    id: msg_options_and_info
                                    color: selfBackgroundColor
                                    anchors.right: msg.right
                                    anchors.bottom: msg.top
                                    width: msg_options_and_info_row.width + 8
                                    height: msg_options_and_info_row.height + 8
                                    radius: 4
                                    visible: false

                                    MouseArea {
                                        anchors.fill: parent
                                        id: msg_options_mousearea
                                        hoverEnabled: true
                                        onHoveredChanged: {
                                            checkOptionsVisibility();
                                        }

                                    // These could help with the icons:
                                    // - https://icons8.com/icons/set/edit
                                    // - https://www.iconfinder.com/search?q=reply
                                    // - https://forum.qt.io/topic/75115/qml-svg-change-color

                                        Row {
                                            id: msg_options_and_info_row
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                            spacing: 6
                                            visible: false

                                            Text {
                                                id: msg_timestamp
                                                anchors.verticalCenter: parent.verticalCenter
                                                text: "Timestamp"
                                                color: Palette.text
                                                opacity: 0.7
                                                font.pointSize: 7
                                                visible: index != 0
                                            }

                                            Image {
                                                id: reply_button
                                                source: "qrc:/timeline/images/reply.svg"
                                                height: 30
                                                fillMode: Image.PreserveAspectFit
                                            }
                                            Image {
                                                id: edit_button
                                                source: "qrc:/timeline/images/edit.svg"
                                                height: 30
                                                fillMode: Image.PreserveAspectFit
                                            }
                                            Image {
                                                id: menu_button
                                                source: "qrc:/timeline/images/dot_menu_vertical.svg"
                                                height: 30
                                                fillMode: Image.PreserveAspectFit
                                            }
                                        }
                                    }
                                }
                                DropShadow {
                                    id: options_dropshadow
                                    anchors.fill: msg_options_and_info
                                    horizontalOffset: 2
                                    verticalOffset: 1
                                    radius: 4.0
                                    samples: 5
                                    color: "#80000000"
                                    source: msg_options_and_info
                                    visible: false
                                }
                            }

                        }
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
            flickable: groupListView
            anchors.fill: groupListView
        }

    }

}
