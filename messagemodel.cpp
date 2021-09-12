#include "messagemodel.h"

#include <QDebug>
#include <stdlib.h>

MessageModel::MessageModel() {
    /*for (int i = 0; i < rand() % 4 + 1; i++) {

        m_list.append(Message{ 0, QString::fromStdString(msg) });
    }*/
}

// Copy constructor needed for Q_DECLARE_METATYPE for QVariant
MessageModel::MessageModel(const MessageModel &other) {
    this->msgList = other.msgList;
}

// The way that you need to move data to and from this QML is
// to have every bit of data be a role.
QHash<int, QByteArray> MessageModel::roleNames() const {
    QHash<int, QByteArray> hash;
    hash[MsgRole] = "msg";
    hash[TimestampRole] = "timestamp";
    return hash;
}

int MessageModel::rowCount(const QModelIndex & parent = QModelIndex()) const {
    if (parent.isValid())
        return 0;
    return msgList.size();
}

bool MessageModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;
    /*Message &item = m_list[index.row()];
    if (role == UsernameRole)
        item.user = value.toString();
    else if (role == MessageRole)
        item.msg = value.toString();
    else
        return false;*/

    emit dataChanged(index, index, { role } );

    return true ;

}

QVariant MessageModel::data(const QModelIndex & index, int role = Qt::DisplayRole) const {
    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};

    const Message &item = msgList.at(index.row());
    if (role == MsgRole) return item.getMsg();
    if (role == TimestampRole) return QVariant::fromValue(item.getTimestamp());

    return {};
}

QVariant MessageModel::getFirstTimestamp() {
    if (msgList.isEmpty()) {
        return 0;
    } else {
        return msgList.first().getTimestamp();
    }
}
