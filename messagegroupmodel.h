#ifndef MESSAGEGROUPMODEL_H
#define MESSAGEGROUPMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include "messagegroup.h"

class MessageGroupModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(MyRoles)
public:
    MessageGroupModel();
    // Copy constructor needed for Q_DECLARE_METATYPE for QVariant
    MessageGroupModel(const MessageGroupModel &other);

    enum MyRoles {
        UsernameRole = Qt::UserRole + 1,
        MessagesModelRole,
        SelfRole
    };

    using QAbstractListModel::QAbstractListModel;

    // The way that you need to move data to and from this QML is
    // to have every bit of data be a role.
    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex & parent) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QVariant data(const QModelIndex & index, int role) const override;

private:
    QVector<MessageGroup> m_list;
    void addItem(int user, bool self);
};

Q_DECLARE_METATYPE(MessageGroupModel*)

#endif // MESSAGEGROUPMODEL_H
