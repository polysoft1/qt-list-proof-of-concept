#include "MyListModel.h"

#include <QDebug>
#include <stdlib.h>

MyListModel::MyListModel() {
    for (int i = 1; i < 100; i++) {
        addItem(i, i, rand() % 3 == 0);
        addItem(i, rand() % 100, rand() % 3 == 0);
    }
}


void MyListModel::addItem(int user, int num, bool self) {
    std::string msg = "Message " +  std::to_string(num);
    for (int j = 0; j < num; j++) {
        msg.append(std::string(" word"));
    }
    QString userStr = self ? "Myself" : "User" +QString::number(user);
    m_list.append(Message{ userStr, QString::fromStdString(msg), self });
}

// Copy constructor needed for Q_DECLARE_METATYPE for QVariant
MyListModel::MyListModel(const MyListModel &other) {
    this->m_list = other.m_list;
}

// The way that you need to move data to and from this QML is
// to have every bit of data be a role.
QHash<int, QByteArray> MyListModel::roleNames() const {
    QHash<int, QByteArray> hash;
    hash[UsernameRole] = "user";
    hash[MessageRole] = "msg";
    hash[SelfRole] = "self";
    return hash;
}

int MyListModel::rowCount(const QModelIndex & parent = QModelIndex()) const {
    if (parent.isValid())
        return 0;
    qDebug() << "rowcount called " << m_list.size();
    return m_list.size();
}

bool MyListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
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

QVariant MyListModel::data(const QModelIndex & index, int role = Qt::DisplayRole) const {
    qDebug() << "data called";

    if (!hasIndex(index.row(), index.column(), index.parent()))
        return {};

    const Message &item = m_list.at(index.row());
    if (role == UsernameRole) return item.getUser();
    if (role == MessageRole) return item.getMsg();
    if (role == SelfRole) return item.getSelf();

    return {};
}
