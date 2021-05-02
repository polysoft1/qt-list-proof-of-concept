import QtQuick 2.0
import QtQuick.Layouts 1.11

// TODO: Use https://doc.qt.io/qt-5/qml-qtquick-systempalette.html

ListView {
    id: listView
    model: MyModel
    onContentHeightChanged: {
        console.log("listView height: " + parent.height)
    }

    delegate: RowLayout {
        id: msg_layout
        height: user.paintedHeight

        Text {
            id: user
            text: model.user
        }
        Text {
            id: msg
            text: model.msg
        }
    }
}
