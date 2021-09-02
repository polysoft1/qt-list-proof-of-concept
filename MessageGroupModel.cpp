#include "MessageGroupModel.h"

#include <QDebug>
#include <stdlib.h>

MessageGroupModel::MessageGroupModel() {
    for (int i = 1; i < 50; i++) {
        addItem(i, rand() % 3 == 0);
    }
}


void MessageGroupModel::addItem(int user, bool self) {
    QString userStr = self ? "Myself" : "User" +QString::number(user);
    m_list.append(MessageGroup{ userStr, new MessageModel, self });
}

// Copy constructor needed for Q_DECLARE_METATYPE for QVariant
MessageGroupModel::MessageGroupModel(const MessageGroupModel &other) {
    this->m_list = other.m_list;
}

// The way that you need to move data to and from this QML is
// to have every bit of data be a role.
QHash<int, QByteArray> MessageGroupModel::roleNames() const {
    QHash<int, QByteArray> hash;
    hash[UsernameRole] = "user";
    hash[MessagesModelRole] = "msg_model";
    hash[SelfRole] = "self";
    return hash;
}

int MessageGroupModel::rowCount(const QModelIndex & parent = QModelIndex()) const {
    if (parent.isValid())
        return 0;
    qDebug() << "rowcount called " << m_list.size();
    return m_list.size();
}

bool MessageGroupModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
        return false;
    qDebug() << "setdata called";

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

QVariant MessageGroupModel::data(const QModelIndex & index, int role = Qt::DisplayRole) const {
    qDebug() << "data called";

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};

    const MessageGroup &item = m_list.at(index.row());
    if (role == UsernameRole) return item.getUser();
    if (role == MessagesModelRole) {
        qDebug() << "Returning model";
        return QVariant::fromValue(item.getModel());
    }
    if (role == SelfRole) return item.getSelf();

    qDebug() << "Unknown role in group data " << roleNames()[role];

    return {};
}
