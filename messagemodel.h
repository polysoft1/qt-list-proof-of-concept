#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include "message.h"

class MessageModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(MyRoles)
public:
    MessageModel();
    // Copy constructor needed for Q_DECLARE_METATYPE for QVariant
    MessageModel(const MessageModel &other);

    enum MyRoles {
        MsgRole = Qt::UserRole + 1,
        TimestampRole
    };

    // The way that you need to move data to and from this QML is
    // to have every bit of data be a role.
    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex & parent) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QVariant data(const QModelIndex & index, int role) const override;

    Q_INVOKABLE QVariant getFirstTimestamp();

    QVector<Message> msgList;
};


#endif // MESSAGEMODEL_H
