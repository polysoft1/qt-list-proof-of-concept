#include "MessageModel.h"

#include <QDebug>
#include <stdlib.h>

MessageModel::MessageModel() {
    for (int i = 0; i < rand() % 4 + 1; i++) {
        int msgSize = rand() % 30 + 1;
        std::string msg = "Message size " +  std::to_string(msgSize);
        for (int j = 0; j < msgSize; j++) {
            msg.append(std::string(" word"));
        }
        m_list.append(Message{ 0, QString::fromStdString(msg) });
    }
}

// Copy constructor needed for Q_DECLARE_METATYPE for QVariant
MessageModel::MessageModel(const MessageModel &other) {
    this->m_list = other.m_list;
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
    qDebug() << "msg rowcount called " << m_list.size();
    return m_list.size();
}

bool MessageModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;
    qDebug() << "msg setdata called";

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
    qDebug() << "msg data called";

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};

    const Message &item = m_list.at(index.row());
    if (role == MsgRole) return item.getMsg();
    if (role == TimestampRole) return QVariant::fromValue(item.getTimestamp());

    return {};
}
